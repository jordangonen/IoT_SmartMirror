#include "magicMirrorHWAPI.h"
#include "../../lib/Adafruit_HX8357/src/Adafruit_HX8357.h"
const int TFT_CS = A2;
const int TFT_DC = DAC;
const int TFT_RST = -1;
//setup
void apiSetup() {
  Serial.begin(9600);

  Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
  tft.begin(HX8357D);
  tft.setRotation(1);
  tft.fillScreen(HX8357_BLACK);
  tft.setTextSize(5);
  tft.println("72c, 10:10am");

};
//screen setup
//fsm
//format setter
//variable publisher
//internet button
//distance get
//3rd party data get functions assocaited with different formats
