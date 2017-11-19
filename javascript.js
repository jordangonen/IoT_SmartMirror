
var currentView = "weather-modal";
document.getElementById("iterate-forwards").addEventListener("click", function() {
  if(currentView = "weather-modal"){
    swapElement("weather-modal", "calendar-modal");
  } else if(currentView = "calendar-modal"){
    swapElement("calendar-modal", "weather-modal");
  }
});


//elementSwapper
function swapElement(hide, show) {
  console.log(hide);
  document.getElementById(hide).style.display = 'none';
  document.getElementById(show).style.display = 'block';
  currentView = show;
  console.log(view);
}
