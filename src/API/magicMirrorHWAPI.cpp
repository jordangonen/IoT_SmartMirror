#include "magicMirrorHWAPI.h"
#include "../../lib/Adafruit_HX8357/src/Adafruit_HX8357.h"
const int TFT_CS = A2;
const int TFT_DC = DAC;
const int TFT_RST = -1;
int onDeck = 0;
int done = 0;
int sent = 0;
String spotSong = "";
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
int state = 0;
void trelloNewOnDeck(const char *event, const char *data){
  Serial.println("ondeck ran");
    onDeck = onDeck + 1;

    if (state == 0) {
        FSM(state);
    }


}
void trelloNewDone(const char *event, const char *data) {
  Serial.println("done ran");
  done = done+1;

  if (state == 0) {
      FSM(state);
  }

}
void gmailNewSent (const char *event, const char *data) {
  Serial.println("gmail ran");
  sent = sent + 1;

  if (state == 1) {
      FSM(state);
  }


}
void spotifyNewSave (const char *event, const char *data) {
  Serial.println("spotufy ran");
    spotSong = String(data);

    if (state == 2) {
        FSM(state);
    }


}



//setup
void apiSetup() {
  Serial.begin(9600);


  tft.begin(HX8357D);
  tft.setRotation(1);
  // Subscribe to the integration response event
  Particle.subscribe("trello/newOnDeck", trelloNewOnDeck);
  Particle.subscribe("gmail/newSent", gmailNewSent);
  Particle.subscribe("spotify/newSave", spotifyNewSave);
  Particle.subscribe("trello/newDone", trelloNewDone);
  tft.fillScreen(HX8357_BLACK);
  tft.setTextSize(5);


};
//screen setup
//fsm

void FSM (int arg) {
  switch(arg) {
    case 0 : //trello
      tft.fillScreen(HX8357_BLACK);
      tft.setCursor(0,0);
      tft.print("Trello Progress");
      tft.print('\n');
      tft.print("On Deck: ");
      tft.print(onDeck);
      tft.print('\n');
      tft.print("Done: ");
      tft.print(done);
      Serial.println("reqrote screen");


      break;
    case 1 : // gmail
    tft.fillScreen(HX8357_BLACK);
    tft.setCursor(0,0);
    tft.print("gmails sent today: ");
    tft.print(sent);

    Serial.println("reqrote screen");


    break;
    case 2 : //spotify
    tft.fillScreen(HX8357_BLACK);
    tft.setCursor(0,0);
    tft.print("Last Saved Spotify");
    tft.print('\n');
    tft.print(spotSong);

    Serial.println("reqrote screen");


    break;
  }


}



//format setter
//variable publisher
//internet button
//distance get
//3rd party data get functions assocaited with different formats
