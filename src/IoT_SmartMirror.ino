/*
 * Project IoT_SmartMirror
 * Description: Final 222 Project
 * Author: Justin Friedman, Jordan Gonen
 * Date: Fall 2017
 */


 #include <ArduinoJson.h>
#include <Adafruit_HX8357.h>
 #include <Adafruit_mfGFX.h>


 const int TFT_CS = A2;
 const int TFT_DC = DAC;
 const int TFT_RST = -1;
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
 void setup() {
   Serial.begin(115200);

   tft.begin(HX8357D);
   tft.setRotation(1);
   tft.fillScreen(HX8357_BLACK);
   tft.setTextWrap(true);





 }


 void loop() {

   tft.begin(HX8357D);
   tft.setRotation(1);
   // Subscribe to the integration response event

   tft.fillScreen(HX8357_BLACK);
   tft.setTextSize(5);



 }
