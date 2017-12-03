var deviceId = "5b004b000f51353338363333";
var name = "jbf_photon"

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

    var sendZip = particle.callFunction({ deviceId: deviceId, name: name, argument: currentZip, auth: token });

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
