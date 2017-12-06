// This #include statement was automatically added by the Particle IDE.
#include <ArduinoJson.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_HX8357.h>
// use hardware SPI
#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
//instatiate vars for webhook response parse
 const char* conditions1;
 const char* conditions2;
 const char* conditions3;
 double high1;
 double low1;
 double high2;
 double low2;
 double high3;
 double low3;

 const char* name;
 const char* condition;
 double temp;
 double hum;
 double windS;
 double windD;

//printable vars
String zipCode = "99559";
String lastZip = "99559";
String layout = "simple";
String unit = "F";



//timer calls this every 30 secs to update display values, delay is to give the API server some time to send a responce
void apiFetch() {
   Particle.publish("getCurrentWeather", zipCode);

   delay(3000);

}
//weather update timer
Timer apiFetchTimer(30000, apiFetch);

//TFT pins
const int TFT_CS = A2;
const int TFT_DC = DAC;
const int TFT_RST = -1;

//tft object using lib
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
void setup() {
    Serial.begin(9600);
    //cloud vars
    Particle.variable("currentZip", zipCode);
   Particle.variable("currentUnit", unit);
   Particle.variable("layout", layout);

   //webhook
   Particle.subscribe("hook-response/getCurrentWeather/0", currentWeatherHandler, MY_DEVICES);
   Particle.subscribe("hook-error/getCurrentWeather/0", currentWeatherError, MY_DEVICES);

   //cloud functions
   Particle.function("zipPost", zipPost);
   Particle.function("layoutSetter", layoutSetter);
   Particle.function("unitSetter", unitSetter);
   //start timer and tft
   apiFetchTimer.start();
    tft.begin(HX8357D);
    //tft init
  tft.setTextSize(7);       // text size
  tft.fillScreen(HX8357_BLACK);

  tft.setTextWrap(false); // turn off text wrapping so we can do scrolling
  tft.setRotation(1);
  //get current default weather
  bool call;
  call = Particle.publish("getCurrentWeather", "99559");


}

void loop() {
//no looping code

}
//responce to current weather web hook
void currentWeatherHandler(const char *event, const char *data) {
   // Handle the webhook response

   //unuseable string
   String str = String(data);
   str = str.replace(" ", "");

      // Serial.println(str);

      //useable char array
     char json[500] = "";
     str.toCharArray(json, 500);

    StaticJsonBuffer<500> jsonBuffer;
    //convert to obj-array
   JsonObject& root = jsonBuffer.parseObject(json);
   if (!root.success()){
    Serial.println("parseObject() failed");
    return;
  }
  //assign vals

   condition  = root["condition"];
   temp = root["temp"];
   hum = root["hum"];
   windS = root["windS"];
   windD = root["windD"];
    name    = root["name"].asString();

   //units
   if ( unit == "F") {
     temp = temp*1.8-459.67;
   }
   if (unit == "C") {
     temp = temp-273.15;
   }


  screenSetter();
 }
 //if there is a bad zip that makes it to the particle
 void currentWeatherError(const char *event, const char *data) {
   zipCode = lastZip;


 }
//depreciated
 void threeDayWeatherHandler(const char *event, const char *data) {
   // Handle the webhook response


   String threeDay = String(data);


      // Serial.println(str);


     char json[500] = "";
     threeDay.toCharArray(json, 500);
    //  Serial.println(json);




    StaticJsonBuffer<500> jsonBuffer;

   JsonObject& root = jsonBuffer.parseObject(json);
   if (!root.success()){
    Serial.println("parseObject() failed");
    return;
  }
   conditions1    = root["conditions1"];
   conditions2    = root["conditions2"];
   conditions3    = root["conditions3"];
   high1 = root["high1"];
   low1 = root["low1"];
   high2 = root["high2"];
   low2 = root["low2"];
   high3 = root["high3"];
  low3 = root["low3"];

  //screenSetter();

 }

//get weather for new zip
 int zipPost(String command) {
    lastZip = zipCode;
     zipCode = command;
     Particle.publish("getCurrentWeather", zipCode);
     return 1;

 }

//set the layout of the tft
 int layoutSetter(String command) {
   if (command == "simple") {
     layout = command;
     Serial.println("Layout is now simple");
     screenSetter();
     return 1;

   }
   if (command == "advanced") {
     layout = command;
     Serial.println("Layout is now advanced");
     screenSetter();
     return 1;
   }
   if (command == "3day") {
     layout = command;
     Serial.println("Layout is now 3day");
     screenSetter();
     return 1;
   }
   else {
     Serial.println("Not a layout");
     return -1;
   }
 }
//convert for new units
 int unitSetter(String command) {
   if (command == "F") {
     if (unit != command) {
       temp = temp * 1.8 + 32;
     }
     unit = command;
    //  Serial.println("F");

     screenSetter();
     return 1;
   }
   if (command == "C") {
     if (unit != command) {
       temp = (temp - 32)/1.8;
     }
     unit = command;
    //  Serial.println("C");
     screenSetter();
     return 1;
   }
   else {
     return -1;
   }


 }
//write to tft
 void screenSetter() {
   if (layout == "simple") {
      tft.setTextSize(7);       // text size
        tft.setCursor(0,0);
        tft.fillScreen(HX8357_BLACK);

     tft.println(name);
     tft.print(temp);
     tft.print(" ");
     tft.println(unit);
     tft.println(condition);
     Serial.println("Simple");
     Serial.println(name);
     Serial.println(temp);
     Serial.println(condition);

   }
   if (layout == "advanced") {
     tft.setTextSize(4);       // text size
             tft.setCursor(0,0);
             tft.fillScreen(HX8357_BLACK);
     tft.println(name);
     tft.print(temp);
     tft.print(" ");
     tft.println(unit);
     tft.println(condition);
     tft.print("Humidity ");
     tft.print(hum);
     tft.println(" %");
     tft.print("Wind MPH: ");
     tft.println(windS);
     tft.print("Wind Deg: ");
     tft.println(windD);
     Serial.println("Advanced");
     Serial.println(name);
     Serial.println(temp);
     Serial.println(condition);
     Serial.println(hum);
     Serial.println(windS);
     Serial.println(windD);

   }
 }
