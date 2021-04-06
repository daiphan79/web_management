
    var firebaseConfig = {
        apiKey: "AIzaSyAB_xVOEIUGPoLt14ypYv9A0JyV8DQePWM",
        authDomain: "webtest-3cede.firebaseapp.com",
        databaseURL: "https://webtest-3cede-default-rtdb.firebaseio.com",
        projectId: "webtest-3cede",
        storageBucket: "webtest-3cede.appspot.com",
        messagingSenderId: "795889023005",
        appId: "1:795889023005:web:d1f523e13d48f4a717aef4",
        measurementId: "G-04YSBD3B35"
      };
    
      // Initialize Firebase
      firebase.initializeApp(firebaseConfig);
    
        var dienap = document.getElementById('diennang1')
        var read123 = firebase.database().ref().child("da")
         read123.on('value',function(read123){
        dienap.innerHTML=read123.val();
        console.log(read123);
        });
    
         var dongdien = document.getElementById('dongdien')
        var dd = firebase.database().ref().child("dongdien")
         dd.on('value',function(dd){
        dongdien.innerHTML=dd.val();
        console.log(dd);
        });
    
        var congsuat = document.getElementById('congsuat')
        var cs = firebase.database().ref().child("congsuat")
         cs.on('value',function(cs){
        congsuat.innerHTML=cs.val();
        console.log(cs);
        });
    
        // var diennang1 = document.getElementById('dn')
        // var wh = firebase.database().ref().child("dn")
        //  wh.on('value',function(wh){
        // diennang.innerHTML=wh.val();
        // console.log(wh);
        // });

function btn_all(){
    if (all.innerHTML==="ON_ALL"){
       all.innerText= "OFF_ALL"
       all.style.color= "white"
     document.getElementById('btn_all1').style.backgroundColor=' #4391f0'
  

    //  firebase.database().ref().child("auto_man").set("1");
    }
    
    else{
      all.innerText= "ON_ALL"
      //all.innerText= "ALL"
     all.style.color='#4391f0'
      document.getElementById('btn_all1').style.backgroundColor='white'
     
    //   firebase.database().ref().child("auto_man").set("0");
    }
  }
  function btn_tb1(){
    if (tb1.innerHTML==="ON_TB1"){
       tb1.innerText= "OFF_TB1"
       tb1.style.color= "white"
     document.getElementById('btn_tb1').style.backgroundColor=' #4391f0'
   
     //  firebase.database().ref().child("auto_man").set("1");
    }
    
    else{
      tb1.innerText= "ON_TB1"
      //tb1.innerText= "ALL"
     tb1.style.color='#4391f0'
      document.getElementById('btn_tb1').style.backgroundColor='#fff'
    //   firebase.database().ref().child("auto_man").set("0");
    }
  }
  function btn_tb2(){
    if (tb2.innerHTML==="ON_TB2"){
       tb2.innerText= "OFF_TB2"
       tb2.style.color= "white"
     document.getElementById('btn_tb2').style.backgroundColor=' #4391f0'
    //  firebase.database().ref().child("auto_man").set("1");
    }
    
    else{
      tb2.innerText= "ON_TB2"
      //tb2.innerText= "ALL"
     tb2.style.color='#4391f0'
      document.getElementById('btn_tb2').style.backgroundColor='#fff'
    //   firebase.database().ref().child("auto_man").set("0");
    }
  }
  function btn_tb3(){
    if (tb3.innerHTML==="ON_TB3"){
       tb3.innerText= "OFF_TB3"
       tb3.style.color= "white"
     document.getElementById('btn_tb3').style.backgroundColor=' #4391f0'
    //  firebase.database().ref().child("auto_man").set("1");
    }
    
    else{
      tb3.innerText= "ON_TB3"
      //tb3.innerText= "ALL"
     tb3.style.color='#4391f0'
      document.getElementById('btn_tb3').style.backgroundColor='#fff'
    //   firebase.database().ref().child("auto_man").set("0");
    }
  }
  function btn_tb4(){
    if (tb4.innerHTML==="ON_TB4"){
       tb4.innerText= "OFF_TB4"
       tb4.style.color= "white"
     document.getElementById('btn_tb4').style.backgroundColor=' #4391f0'
    //  firebase.database().ref().child("auto_man").set("1");
    }
    
    else{
      tb4.innerText= "ON_TB4"
      //tb4.innerText= "ALL"
     tb4.style.color='#4391f0'
      document.getElementById('btn_tb4').style.backgroundColor='#fff'
    //   firebase.database().ref().child("auto_man").set("0");
    }
  }