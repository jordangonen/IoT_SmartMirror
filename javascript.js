
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
document.getElementById("iterate").addEventListener("click", function() {
  console.log(document.getElementById("weather-modal").style.display);
  if(document.getElementById("weather-modal").style.display = 'block'){
    console.log('weather');
    swapElement("weather-modal", "calendar-modal");
  }
  else if(document.getElementById("calendar-modal").style.display = 'block'){
    console.log('calendar');
    swapElement("calendar-modal", "weather-modal");
  }
});
