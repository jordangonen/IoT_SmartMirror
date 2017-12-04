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

    var sendZip = particle.callFunction({ deviceId: deviceId, name: 'zipSetter', argument: currentZip, auth: token });

    sendZip.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
  });

}

function logFail(data) {
        alert("Wrong Username/Password, Please Try Again");
        console.log("fail");
}

var currentZip;
// LAYOUT SETTINGS
var layout = "1";
document.getElementById("layout-day").addEventListener("click", function() {
    layout=document.getElementById("layout-day-input").value;
    var sendLayout = particle.callFunction({ deviceId: deviceId, name: 'sendLayout', argument: layout, auth: token });
    sendLayout.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Layout Changed");
  });

document.getElementById("layout-three-day").addEventListener("click", function() {
    layout=document.getElementById("layout-three-day-input").value;

    var sendLayout = particle.callFunction({ deviceId: deviceId, name: 'sendLayout', argument: layout, auth: token });

    sendLayout.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Layout Changed");
  });
document.getElementById("layout-five-day").addEventListener("click", function() {
    layout=document.getElementById("layout-five-day-input").value;

    var sendLayout = particle.callFunction({ deviceId: deviceId, name: 'sendLayout', argument: layout, auth: token });

    sendLayout.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Layout Changed");
  });

// METRIC SETTINGS
var metric="1";
document.getElementById("metric-f").addEventListener("click", function() {
    metric=document.getElementById("metric-f-input").value;
    var sendMetric = particle.callFunction({ deviceId: deviceId, name: 'sendMetric', argument: layout, auth: token });
    sendMetric.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Metric Changed");
  });

document.getElementById("metric-c").addEventListener("click", function() {
    layout=document.getElementById("metric-c-input").value;

    var sendMetric = particle.callFunction({ deviceId: deviceId, name: 'sendMetric', argument: layout, auth: token });

    sendMetric.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Layout Changed");
  });
document.getElementById("metric-k").addEventListener("click", function() {
    layout=document.getElementById("metric-k-input").value;

    var sendMetric = particle.callFunction({ deviceId: deviceId, name: 'sendMetric', argument: layout, auth: token });

    sendMetric.then(
    function(data) {
      console.log('Function called succesfully:', data);
    }, function(err) {
      console.log('An error occurred:', err);
    });
    alert("Layout Changed");
  });
