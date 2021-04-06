const firebaseConfig = {
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
 var rootRef = firebase.database().ref();
  const auth = firebase.auth();
  
  function  signIn(){
    var gmail= document.getElementById("user");
    var pass = document.getElementById("pass");
    const login =auth.signInWithEmailAndPassword(gmail.value, pass.value);
     
    // login.catch(e => alert(e.message))
    login.catch(e=> document.getElementById('qmk').innerHTML = e.message)
    
   login.then(function (_result) {
     window.location.replace('trangchu.html');
   })
 
  }


  