#include <Wire.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "UART_ARDUINO.h"
#include <ESP8266HTTPClient.h>
UART Nhan;
UART Gui;
#define add_eeprom 0x51
#define UP D4
#define DW D5
#define GUI D6
#define WF D8
#define CB D3
void ICACHE_RAM_ATTR TANG();
void ICACHE_RAM_ATTR GIAM();
void ICACHE_RAM_ATTR GUI_DL();
LiquidCrystal_I2C lcd(0x27, 20, 4);
const byte DS1307 = 0x68;
const byte NumberOfFields = 7;
int second, minute, hour, day, wday, month, year;
float dien_ap, dong_dien, cong_suat, dien_nang,cosfi, caidat;
int tam1, ky, chi_so_moi;
const char* host = "management79.000webhostapp.com";
const char* ssid = "TĐ";
const char* password = "12345678";
String  send_dd, send_da, send_cs, send_dn, sendcosfi, postData;
WiFiClient client;
HTTPClient http;
void setup() {
  //Gui.begin(9600);
  Nhan.begin(9600);
  Wire.begin();
  caidat = 100;
  chi_so_moi = 0;
  ky = 0;
  pinMode(UP, INPUT);
  pinMode(DW, INPUT);
  pinMode(GUI, INPUT);
  pinMode(CB, OUTPUT);
  pinMode(WF, OUTPUT);
  attachInterrupt(UP, TANG, CHANGE);
  attachInterrupt(DW, GIAM, CHANGE);
  attachInterrupt(GUI, GUI_DL, CHANGE);
  setTime(15, 15, 00, 1, 22, 7, 18);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Amp: ");
  lcd.setCursor(0, 1);
  lcd.print("Vol: ");
  lcd.setCursor(0, 2);
  lcd.print("Power: ");
  lcd.setCursor(0, 3);
  lcd.print("Energy: ");
  lcd.setCursor(15, 0);
  lcd.print("Set: ");
   lcd.setCursor(11, 2);
   lcd.print("Cosf: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}
void loop()
{
  readDS1307();
  String gio = String(hour) + ":" + String(minute) + ":" + String(second);
  String ngay = String(year) + "/" + String(month) + "/" + String(day);
  lcd.setCursor(14, 1);
  lcd.print(caidat);
  //hienthi(caidat , 14, 1);
  if (nhan_du_lieu(&dien_ap, &dong_dien, &cong_suat, &dien_nang, &cosfi) == true)
  {
    hienthi(dong_dien , 6, 0);
    hienthi(dien_ap , 6, 1);
    //hienthi(cong_suat , 7, 2);
    //hienthi(dien_nang , 8, 3);
    lcd.setCursor(7, 2);
    lcd.print((int) (cong_suat));
    lcd.setCursor(8, 3);
    lcd.print((int) (dien_nang));
     lcd.setCursor(16, 2);
     lcd.print(cosfi);
    //hienthi(ky , 14, 3);
    ky = dien_nang - chi_so_moi;
    if (day == 28 and hour == 0 and minute == 0)
    {
      chi_so_moi = dien_nang;
    }
    if (cong_suat > caidat)
    {
      digitalWrite(CB, HIGH);
    }
    else
    {
      digitalWrite(CB, LOW);
    }
//    String url = "/dbwrite.php?send_dd=" + String(dong_dien) +
//                 "&send_da=" + String(dien_ap) + "&send_cs=" + String(cong_suat) + "&send_dn=" +
//                 String(dien_nang) + "&gio=" + String(gio) + "&ngay=" +
//                 String(ngay);
    WiFiClient client;
    const int httpPort = 80;
    if (WiFi.status() == WL_CONNECTED)
    {
//      if (client.connect(host, httpPort))
//      {
//        digitalWrite(WF, HIGH);
//        if (second == 30 or second == 59)
//        {
//          client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                       "Host: " + host + "\r\n" +
//                       "Connection: close\r\n\r\n");
//          String line = client.readStringUntil('\r');
//          //delay(500);
//        }
//      }
     send_dd = String(dong_dien);
    send_da = String(dien_ap);
    send_cs = String(cong_suat);
    send_dn = String(dien_nang);
    sendcosfi = String(cosfi);

    // http object of clas HTTPClient
    postData = "send_dd=" + send_dd + "&send_da=" + send_da +
               "&send_cs=" + send_cs + "&send_dn=" + send_dn
               + "&sendcosfi=" + sendcosfi;
    //Specify content-type header

     http.begin("http://management79.000webhostapp.com/dbwrite.php");              // Connect to host where MySQL databse is hosted
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
    Serial.println("Values are: dong_dien=" + String(dong_dien) + " dien_ap" + String(dien_ap) +
                   " cong_suat " + String(cong_suat) + " dien_nang " + String(dien_nang)
                   + " cosfi " + String(cosfi) );
    // // if connection eatablished then do this
    if (httpCode == 200) {
      Serial.println("Values uploaded successfully.");
      Serial.println(httpCode);
      String webpage = http.getString();    // Get html webpage output and store it in a string
      Serial.println(webpage + "\n");
    }
    //// if failed to connect then return and restart

//    else {
//      Serial.println(httpCode);
//      Serial.println("Failed to upload values. \n");
//      http.end();
//      return;
//    }
      else
      {
        ghidata(tam1, dong_dien, dien_ap, cong_suat, dien_nang, ky, hour,
                minute, second, day, month, year);
        tam1 = tam1 + 11;
      }
    }
    else
    {
      ghidata(tam1, dong_dien, dien_ap, cong_suat, dien_nang, ky, hour,
              minute, second, day, month, year);
      tam1 = tam1 + 11;
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
    }
  }
  delay(1000);
}
void TANG()
{
  caidat = caidat + 10;
}
void GIAM()
{
  caidat--;
}
void GUI_DL()
{
  gui_du_lieu(caidat);
}
//=============================================================== == == == == == == == == == == == == == == == == == == == == == == == ==
void gui_du_lieu(float e)
{
  Gui.write_float(e);
}
bool nhan_du_lieu(float* a, float* b, float* c, float* d,float* f)
{
  uint32_t kich_co_goi_tin = sizeof(*a) + sizeof(*b) + sizeof(*c) + sizeof(*d);
  if (Serial.available() >= kich_co_goi_tin)
  {
    (*a) = Nhan.read_float();
    (*b) = Nhan.read_float();
    (*c) = Nhan.read_float();
    (*d) = Nhan.read_float();
    (*f) = Nhan.read_float();
    Nhan.clear_buffer(); // reset lại bộ nhớ đệm
    return true; // cuối cùng trả về true báo đã nhận đủ và hoàn tất
  }
  else
  {
    return false; // báo chưa đủ
  }
}
//=============================================================
void ghidata(unsigned int tam, float dong_dien, float dien_ap, float cong_suat, float
             dien_nang, float ky, int gio, int phut, int giay, int ngay, int thang, int nam)
{
  int t = tam;
  int k = 0;
  int mang[11] = {dong_dien, dien_ap, cong_suat, dien_nang, ky, gio, phut, giay, ngay,
                  thang, nam
                 };
  //Serial.print("Data ghi:");
  for (unsigned int address = t; address < t + 11 ; address++)
  {
    writeEEPROM(add_eeprom, address, mang[k]);
    delay(5);//Serial.print(mang[k]);Serial.print(" ");
    k++;
  }
}
String docdata(unsigned int address)
{
  int dong_dien, dien_ap, cong_suat, dien_nang, ky, gio1, phut1, giay1, ngay1, thang1, nam1;
  String ngay, gio;
  dong_dien = readEEPROM(add_eeprom, address++);
  dien_ap = readEEPROM(add_eeprom, address++);
  cong_suat = readEEPROM(add_eeprom, address++);
  dien_nang = readEEPROM(add_eeprom, address++);
  ky = readEEPROM(add_eeprom, address++);
  gio1 = readEEPROM(add_eeprom, address++);
  phut1 = readEEPROM(add_eeprom, address++);
  giay1 = readEEPROM(add_eeprom, address++);
  ngay1 = readEEPROM(add_eeprom, address++);
  thang1 = readEEPROM(add_eeprom, address++);
  nam1 = readEEPROM(add_eeprom, address++);
  gio = String(gio1) + ":" + String(phut1) + ":" + String(giay1);
  ngay = String(ngay1) + "/" + String(thang1) + "/" + String(nam1);
  String url = "/dbwrite.php?send_dd=" + String(dong_dien) +
                 "&send_da=" + String(dien_ap) + "&send_cs=" + String(cong_suat) + "&send_dn=" +
                 String(dien_nang) + "&gio=" + String(gio) + "&ngay=" +
                 String(ngay);
  return url;
}
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data )
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}
byte readEEPROM(int deviceaddress, unsigned int eeaddress )
{
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}
void readDS1307()
{
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, NumberOfFields);
  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read() );
  hour = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
  wday = bcd2dec(Wire.read() );
  day = bcd2dec(Wire.read() );
  month = bcd2dec(Wire.read() );
  year = bcd2dec(Wire.read() );
  year += 2000;
}
int bcd2dec(byte num)
{
  return ((num / 16 * 10) + (num % 16));
}
int dec2bcd(byte num)
{
  return ((num / 10 * 16) + (num % 10));
}
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00)); // đặt lại pointer
  Wire.write(dec2bcd(sec));
  Wire.write(dec2bcd(min));
  Wire.write(dec2bcd(hr));
  Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
  Wire.write(dec2bcd(d));
  Wire.write(dec2bcd(mth));
  Wire.write(dec2bcd(yr));
  Wire.endTransmission();
}
void hienthi(float so, int cot, int hang)
{
  int ng1 = (int)(so);
  int tp1 = (so - (float)ng1) * 100;
  int tramnghin = ng1 / 100000;
  int chucnghin = ng1 / 10000;
  int nghin = ng1 / 1000;
  int tram = ng1 / 100;
  int chuc = ng1 % 100 / 10;
  int donvi = ng1 % 100 % 10;
  int chuc1 = tp1 / 10;
  int donvi1 = tp1 % 10;
  if (tramnghin == 0 && chucnghin == 0 && nghin == 0 && tram == 0 && chuc == 0)
  {
    lcd.setCursor(cot, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 1, hang);
    lcd.print(".");
    lcd.setCursor(cot + 2, hang);
    lcd.print(chuc1);
    lcd.setCursor(cot + 3, hang);
    lcd.print(donvi1);
    lcd.setCursor(cot + 4, hang);
    lcd.print(" ");
    lcd.setCursor(cot + 5, hang);
    lcd.print(" ");
    lcd.setCursor(cot + 6, hang);
    lcd.print(" ");
  }
  else if (tramnghin == 0 && chucnghin == 0 && nghin == 0 && tram == 0) {
    lcd.setCursor(cot, hang);
    lcd.print(chuc);
    lcd.setCursor(cot + 1, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 2, hang);
    lcd.print(".");
    lcd.setCursor(cot + 3, hang);
    lcd.print(chuc1);
    lcd.setCursor(cot + 4, hang);
    lcd.print(donvi1);
    lcd.setCursor(cot + 5, hang);
    lcd.print(" ");
    lcd.setCursor(cot + 6, hang);
    lcd.print(" ");
  } else if (tramnghin == 0 && chucnghin == 0 && nghin == 0) {
    lcd.setCursor(cot, hang);
    lcd.print(tram);
    lcd.setCursor(cot + 1, hang);
    lcd.print(chuc);
    lcd.setCursor(cot + 2, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 3, hang);
    lcd.print(".");
    lcd.setCursor(cot + 4, hang);
    lcd.print(chuc1);
    lcd.setCursor(cot + 5, hang);
    lcd.print(donvi1);
    lcd.setCursor(cot + 6, hang);
    lcd.print(" ");
  } else if (tramnghin == 0 && chucnghin == 0) {
    lcd.setCursor(cot, hang);
    lcd.print(nghin);
    lcd.setCursor(cot + 1, hang);
    lcd.print(tram);
    lcd.setCursor(cot + 2, hang);
    lcd.print(chuc);
    lcd.setCursor(cot + 3, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 4, hang);
    lcd.print(".");
    lcd.setCursor(cot + 5, hang);
    lcd.print(chuc1);
    lcd.setCursor(cot + 6, hang);
    lcd.print(" ");
  } else if (tramnghin == 0) {
    lcd.setCursor(cot, hang);
    lcd.print(chucnghin);
    lcd.setCursor(cot + 1, hang);
    lcd.print(nghin);
    lcd.setCursor(cot + 2, hang);
    lcd.print(tram);
    lcd.setCursor(cot + 3, hang);
    lcd.print(chuc);
    lcd.setCursor(cot + 4, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 5, hang);
    lcd.print(".");
    lcd.setCursor(cot + 6, hang);
    lcd.print(chuc1);
  } else {
    lcd.setCursor(cot, hang);
    lcd.print(tramnghin);
    lcd.setCursor(cot + 1, hang);
    lcd.print(chucnghin);
    lcd.setCursor(cot + 2, hang);
    lcd.print(nghin);
    lcd.setCursor(cot + 3, hang);
    lcd.print(tram);
    lcd.setCursor(cot + 4, hang);
    lcd.print(chuc);
    lcd.setCursor(cot + 5, hang);
    lcd.print(donvi);
    lcd.setCursor(cot + 6, hang);
    lcd.print(" ");
  }
}
