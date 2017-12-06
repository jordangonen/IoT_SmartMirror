// define deviceID
var deviceId = "5b004b000f51353338363333";
var particle = new Particle();
//login to device and send to logSuccess or logFail
document.getElementById("login-btn").addEventListener("click", function() {
        var email = document.getElementById('email').value;
        var pass = document.getElementById('password').value;
        particle.login({
                username: email,
                password: pass
        }).then(logSuccess, logFail)
});
var token;
// log success if login is "successful" obviously
function logSuccess(data) {
        // get rid of login screen
        document.getElementById("login").style.display = "none";
        // put waiting screen
        document.getElementById("waiting-screen").style.display = "block";
        // grab token from data object
        token = data.body.access_token;
        //get the "current state" from last login
        particle.getVariable({
                deviceId: deviceId,
                name: 'currentZip',
                auth: token
        }).then(function(stream) {
                console.log("gets in");
                document.getElementById("zip-input").placeholder = stream.body.result;
                document.getElementById("status").innerHTML = "Online 😎";
                // grab units from last login
                particle.getVariable({
                        deviceId: deviceId,
                        name: 'currentUnit',
                        auth: token
                }).then(function(stream2) {
                        console.log('Device variable retrieved successfully:', data);
                        // set units if F OR C
                        if (stream2.body.result == "F") {
                                document.getElementById("unit-c-input").checked = "false";
                                document.getElementById("unit-f-input").checked = "true";
                        }
                        if (stream2.body.result == "C") {
                                document.getElementById("unit-f-input").checked = "false";
                                document.getElementById("unit-c-input").checked = "true";
                        }
                        // throw error
                }, function(err) {
                        console.log('An error occurred while getting attrs:', err);
                });

                // get layout from last login
                particle.getVariable({
                        deviceId: deviceId,
                        name: 'layout',
                        auth: token
                }).then(function(stream2) {
                        console.log('Device variable retrieved successfully:', data);
                        // set layout simple or advanced
                        if (stream2.body.result == "simple") {
                                document.getElementById("layout-advanced-input").checked = "false";
                                document.getElementById("layout-simple-input").checked = "true";
                        }
                        if (stream2.body.result == "advanced") {
                                document.getElementById("layout-simple-input").checked = "false";
                                document.getElementById("layout-advanced-input").checked = "true";
                        }
                        // error
                }, function(err) {
                        console.log('An error occurred while getting attrs:', err);
                });
                console.log('Device variable retrieved successfully:', stream);
                // turn off waiting screen and turn off login , turn on logout and turn on main
                document.getElementById("waiting-screen").style.display = "none";
                document.getElementById("login").style.display = "none";
                document.getElementById("logout").style.display = "block";

                document.getElementById("main").style.display = "block";
                // reload for logout
                document.getElementById("logout").addEventListener("click", function() {
                        location.reload();
                });


                // send zip on button click
                document.getElementById("zip-input-btn").addEventListener("click", function() {

                        currentZip = String(document.getElementById("zip-input").value);

                        // if too short
                        if (currentZip.length != 5) {
                                alert("Please enter a valid zip code length");
                                return;
                        }
                        // if zip function send it as an argument currentZip
                        var sendZip = particle.callFunction({
                                deviceId: deviceId,
                                name: 'zipPost',
                                argument: currentZip,
                                auth: token
                        });

                        sendZip.then(
                                function(data) {
                                        // if success returns a 1
                                        console.log('Function called succesfully:', data);
                                },
                                function(err) {

                                        // returns a -1
                                        console.log('An error occurred:', err);
                                });
                });
                // stupid error
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

// if log fails
function logFail(data) {
        alert("Wrong Username/Password, Please Try Again");
        console.log("fail");
}

var currentZip;
var layout;

// LAYOUT SETTINGS

// simple layout
document.getElementById("layout-simple").addEventListener("click", function() {
        console.log("sending simple layout");
        //sendit
        var sendLayout1 = particle.callFunction({
                deviceId: deviceId,
                name: 'layoutSetter',
                argument: "simple",
                auth: token
        });
        sendLayout1.then(
                function(data) {
                        console.log('Function called succesfully:', data);
                },
                function(err) {
                        console.log('An error occurred:', err);
                });
});

// advanced layout
document.getElementById("layout-advanced").addEventListener("click", function() {
        console.log("sending advanced layout");
        //sendit
        var sendLayout2 = particle.callFunction({
                deviceId: deviceId,
                name: 'layoutSetter',
                argument: "advanced",
                auth: token
        });
        sendLayout2.then(
                function(data) {
                        console.log('Function called succesfully:', data);
                },
                function(err) {
                        console.log('An error occurred:', err);
                });
});



// METRIC SETTINGS
document.getElementById("unit-f").addEventListener("click", function() {
        // unit=document.getElementById("unit-f-input").value;
        // farenheit
        var sendUnit1 = particle.callFunction({
                deviceId: deviceId,
                name: 'unitSetter',
                argument: 'F',
                auth: token
        });
        sendUnit1.then(
                function(data) {
                        console.log('Function called succesfully:', data);
                },
                function(err) {
                        console.log('An error occurred:', err);
                });
});

document.getElementById("unit-c").addEventListener("click", function() {
        // unit=document.getElementById("unit-c-input").value;
        // celsius
        var sendUnit2 = particle.callFunction({
                deviceId: deviceId,
                name: 'unitSetter',
                argument: 'C',
                auth: token
        });

        sendUnit2.then(
                function(data) {
                        console.log('Function called succesfully:', data);
                },
                function(err) {
                        console.log('An error occurred:', err);
                });
});
