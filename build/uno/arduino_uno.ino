#include "EmonLib.h"
#include<EEPROM.h>
#include <Wire.h>
#include "UART_ARDUINO.h"
#include <SoftwareSerial.h>
SoftwareSerial SIM900(10, 11);
String textSMS = "CANH BAO QUA CONG SUAT";
char tempchar;
UART Gui;
UART Nhan;
#define CURRENT_CAL 66
#define VOLT_CAL 300
float dien_ap, dong_dien, cong_suat, dien_nang, caidat;
int i;
EnergyMonitor emon1;
double kilos = 0;
int peakPower = 0;
void setup()
{
  Gui.begin(9600);
  //Nhan.begin(9600);
  SIM900.begin(9600);
  Wire.begin();
  i = 0;
  dien_nang = 0;
  emon1.current(A0, CURRENT_CAL);
  emon1.voltage(A1, VOLT_CAL, 1.7);
}
void loop()
{
  emon1.calcVI(20, 2000);
  dien_ap = emon1.Vrms;
  dong_dien = emon1.Irms;
  cong_suat = emon1.apparentPower;
  float powerFactor = emon1.powerFactor; //he so cosfi giua P realpower chua loc RMS voi Prms la P apparentPower
  //dien_nang = (dien_nang + cong_suat)/1000/3600; KWH
  //dien_nang = (dien_nang + cong_suat);//WS
  if (cong_suat > peakPower )
  {
    peakPower = cong_suat ;
  }
  if (dong_dien > 0.5) {
    dien_nang = dien_nang + (cong_suat * (2.05 / 60 / 60 / 10000)); // tinh kilowat gio da su dung
  }

  gui_du_lieu(dien_ap, dong_dien, cong_suat, dien_nang, powerFactor);
  if (nhan_du_lieu(&caidat) == true)
  {
    EEPROM.write(0, caidat);
  }
  if (cong_suat > EEPROM.read(0))
  {
    i++;
    if (i == 1 or i == 2)
    {
      sendSMS(textSMS);
    }
  }
  else
  {
    i = 0;
  }
  delay(1000);
}
void gui_du_lieu(float a, float b, float c, float d, float f)
{
  Gui.write_float(a);
  Gui.write_float(b);
  Gui.write_float(c);
  Gui.write_float(d);
  Gui.write_float(f);
}
bool nhan_du_lieu(float* e)
{
  uint32_t kich_co_goi_tin = sizeof(*e);
  if (Serial.available() >= kich_co_goi_tin)
  {
    (*e) = Nhan.read_float();
    Nhan.clear_buffer();
    return true;
  }
  else
  {
    return false;
  }
}
void sendSMS(String message)
{
  SIM900.print("AT+CSCS=\"GSM\"\r\n"); // Lệnh AT để gửi in nhắnSMS
  SIM900_response(500);
  SIM900.print("AT+CMGF=1\r\n"); // Bắt đầu quá trình gửi tin nhắn
  SIM900_response(500);
  SIM900.print("AT+CMGS=\"+84348968979\"\r"); // Số điên thoại của người nhântheo format quốc tế
  SIM900_response(500);
  SIM900.print(message); // gửi nội dung tin nhắn
  SIM900_response(500);
  SIM900.print((char)26); // Kết thúc lênh gửi
  SIM900_response(5000);
}
void SIM900_response(int time)
{
  int tnow = millis();
  while ((millis() - tnow) < time) {
    if (SIM900.available()) {
      tempchar = (char)SIM900.read();
    }
  }
}
