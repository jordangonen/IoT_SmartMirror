
//elementSwapper
function swapElement(hide, show) {
  document.getElementById(hide).style.display = 'none';
  document.getElementById(show).style.display = 'block';
  currentView = show;
}
document.getElementById("iterate").addEventListener("click", function() {
  swapElement(arrow);


});
