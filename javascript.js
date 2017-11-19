
//elementSwapper
function swapElement(hide, show) {
  console.log(hide);
  console.log(show);
  document.getElementById(hide).style.display = 'none';
  document.getElementById(show).style.display = 'block';
  currentView = show;
  // console.log(currentView);
  console.log(document.getElementById("weather-modal").style.display);
}
currentView = "calendar-modal";
document.getElementById("iterate").addEventListener("click", function() {
  console.log(document.getElementById("weather-modal").style.display);
  if(currentView = "weather-modal"){
    swapElement("weather-modal", "calendar-modal");
  }
  else if(currentView = "calendar-modal"){
    swapElement("calendar-modal", "weather-modal");
  }
});
