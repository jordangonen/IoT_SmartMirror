var deviceId = "5b004b000f51353338363333";

var particle = new Particle();

document.getElementById("login-btn").addEventListener("click", function() {
        var email = document.getElementById('email').value;
        var pass = document.getElementById('password').value;
        particle.login({
                username: email,
                password: pass
        }).then(logSuccess, logFail)
});
var token;
function logSuccess(data) {
  document.getElementById("login").style.display = "none";
  document.getElementById("main").style.display = "block";

  token = data.body.access_token;

  document.getElementById("zip-input-btn").addEventListener("click", function() {
    currentZip = String(document.getElementById("zip-input").value);

    var sendZip = particle.callFunction({ deviceId: deviceId, name: 'zipPost', argument: currentZip, auth: token });

    sendZip.then(
    function(data) {
      console.log('Function called succesfully:', data);

    }, function(err) {
      console.log('An error occurred:', err);
    });
  });

  //Get all events
  particle.getEventStream({auth: token}).then(function(stream) {
    stream.on('hook-error/getCurrentWeather/0', function(data) {
      alert("Please enter a correct zip-code");
      console.log("Event:Broken ", data);
    });
  });

}

document.getElementById("status");


function logFail(data) {
        alert("Wrong Username/Password, Please Try Again");
        console.log("fail");
}

var currentZip;

// LAYOUT SETTINGS
var layout = "simple";
document.getElementById("layout-simple").addEventListener("click", function() {
    layout=document.getElementById("layout-simple-input").value;

    var sendLayout1 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: layout, auth: token });
    sendLayout1.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });

document.getElementById("layout-advanced").addEventListener("click", function() {
    layout=document.getElementById("layout-advanced-input").value;

    var sendLayout2 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: layout, auth: token });

    sendLayout2.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });
document.getElementById("layout-three-day").addEventListener("click", function() {
    layout=document.getElementById("layout-three-day-input").value;

    var sendLayout3 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: layout, auth: token });

    sendLayout3.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });




// METRIC SETTINGS
var unit="F";
document.getElementById("unit-f").addEventListener("click", function() {
    // unit=document.getElementById("unit-f-input").value;
    var sendUnit1 = particle.callFunction({ deviceId: deviceId, name: 'unitSetter', argument: 'F', auth: token });
    sendUnit1.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });

document.getElementById("unit-c").addEventListener("click", function() {
    // unit=document.getElementById("unit-c-input").value;

    var sendUnit2 = particle.callFunction({ deviceId: deviceId, name: 'unitSetter', argument: 'C', auth: token });

    sendUnit2.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });
