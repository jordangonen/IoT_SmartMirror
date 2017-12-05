#include "magicMirrorHWAPI.h"
#include "../../lib/Adafruit_HX8357/src/Adafruit_HX8357.h"
const int TFT_CS = A2;
const int TFT_DC = DAC;
const int TFT_RST = -1;

int zip = 00000;
String spotSong = "";
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
int state = 0;
int zipSetter(String command)
{

  if(command.length() == 5){
    if (command.toInt() != 0) {
        zip = (int)command.toInt();
          Serial.println("GOT ZIP");
          Serial.println(zip);
          return 1;
    }

  }
  else {
    return -1;
  }
}





//setup
void apiSetup() {
  Serial.begin(9600);


  tft.begin(HX8357D);
  tft.setRotation(1);
  // Subscribe to the integration response event

  tft.fillScreen(HX8357_BLACK);
  tft.setTextSize(5);
   Particle.function("zipSetter", zipSetter);


};
//screen setup
//fsm





//format setter
//variable publisher
//internet button
//distance get
//3rd party data get functions assocaited with different formats
