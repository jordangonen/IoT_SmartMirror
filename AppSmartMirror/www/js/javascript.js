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
    document.getElementById("waiting-screen").style.display = "block";
    document.getElementById("logout").style.display = "block";

    token = data.body.access_token;

    particle.getVariable({ deviceId: deviceId, name: 'currentZip', auth: token }).then(function(stream) {
        document.getElementById("zip-input").placeholder = stream.body.result;
        document.getElementById("status").innerHTML="Online 😎";

        particle.getVariable({ deviceId: deviceId, name: 'currentUnit', auth: token }).then(function(stream2) {
          console.log('Device variable retrieved successfully:', data);
            if(stream2.body.result == "F") {
              document.getElementById("unit-c-input").checked = "false";
              document.getElementById("unit-f-input").checked = "true";
            }
            if(stream2.body.result == "C") {
              document.getElementById("unit-f-input").checked = "false";
              document.getElementById("unit-c-input").checked = "true";
            }

        }, function(err) {
          console.log('An error occurred while getting attrs:', err);
        });


        particle.getVariable({ deviceId: deviceId, name: 'layout', auth: token }).then(function(stream2) {
          console.log('Device variable retrieved successfully:', data);
            if(stream2.body.result == "simple") {
              document.getElementById("layout-advanced-input").checked = "false";
              document.getElementById("layout-simple-input").checked = "true";
            }
            if(stream2.body.result == "advanced") {
              document.getElementById("layout-simple-input").checked = "false";
              document.getElementById("layout-advanced-input").checked = "true";
            }

        }, function(err) {
          console.log('An error occurred while getting attrs:', err);
        });

        console.log('Device variable retrieved successfully:', stream);
        document.getElementById("waiting-screen").style.display = "none";
        document.getElementById("login").style.display = "none";
        document.getElementById("logout").style.display = "block";

        document.getElementById("main").style.display = "block";

        document.getElementById("logout").addEventListener("click", function() {
          location.reload();
        });



        document.getElementById("zip-input-btn").addEventListener("click", function() {

          currentZip = String(document.getElementById("zip-input").value);
          if(currentZip.length!=5) {
            alert("Please enter a valid zip code length");
            return;
          }

          var sendZip = particle.callFunction({ deviceId: deviceId, name: 'zipPost', argument: currentZip, auth: token });

          sendZip.then(
          function(data) {
            console.log('Function called succesfully:', data);
          }, function(err) {
            console.log('An error occurred:', err);
          });
        });

        //Get all events
        // particle.getEventStream({auth: token}).then(function(stream) {
        //   stream.on('hook-error/getCurrentWeather/0', function(data) {
        //     alert("Please enter a correct zip-code");
        //     console.log("Event:Broken ", data);
        //   });
        // });


    }, function(err) {
      console.log('An error occurred while getting attrs:', err);
    });

}


function logFail(data) {
        alert("Wrong Username/Password, Please Try Again");
        console.log("fail");
}

var currentZip;
var layout;

// LAYOUT SETTINGS
document.getElementById("layout-simple").addEventListener("click", function() {
    console.log("sending simple layout");
    var sendLayout1 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: "simple", auth: token });
    sendLayout1.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });

document.getElementById("layout-advanced").addEventListener("click", function() {
    console.log("sending advanced layout");

    var sendLayout2 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: "advanced", auth: token });

    sendLayout2.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });
// document.getElementById("layout-three-day").addEventListener("click", function() {
//     layout=document.getElementById("layout-three-day-input").value;
//
//     var sendLayout3 = particle.callFunction({ deviceId: deviceId, name: 'layoutSetter', argument: layout, auth: token });
//
//     sendLayout3.then(
//     function(data) {
//       console.log('Function called succesfully:', data);
//     }, function(err) {
//       console.log('An error occurred:', err);
//     });
//   });


// METRIC SETTINGS
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
