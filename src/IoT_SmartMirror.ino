/*
 * Project IoT_SmartMirror
 * Description: Final 222 Project
 * Author: Justin Friedman, Jordan Gonen
 * Date: Fall 2017
 */


 #include <ArduinoJson.h>
#include <Adafruit_HX8357.h>







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

String zipCode = "10583";
String lastZip = "10583";
String layout = "simple";
String unit = "F";




void apiFetch() {
   Particle.publish("getCurrentWeather", zipCode);

   delay(3000);

}



const int TFT_CS = A2;
const int TFT_DC = DAC;
const int TFT_RST = -1;


Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

 Timer apiFetchTimer(30000, apiFetch);

 void setup() {
   Serial.begin(9600);

   tft.begin(HX8357D);
   tft.setRotation(1);
   tft.fillScreen(HX8357_BLACK);
   tft.setTextWrap(true);

   Particle.variable("currentZip", zipCode);

   Particle.variable("currentUnit", unit);
   Particle.variable("layout", layout);


   Particle.subscribe("hook-response/getCurrentWeather/0", currentWeatherHandler, MY_DEVICES);
   Particle.subscribe("hook-error/getCurrentWeather/0", currentWeatherError, MY_DEVICES);

   Particle.subscribe("hook-response/getCurrentWeather/0", threeDayWeatherHandler, MY_DEVICES);

   Particle.function("zipPost", zipPost);
   Particle.function("layoutSetter", layoutSetter);
   Particle.function("unitSetter", unitSetter);
   apiFetchTimer.start();


 }


 void loop() {





 }

 void currentWeatherHandler(const char *event, const char *data) {
   // Handle the webhook response


   String str = String(data);


      // Serial.println(str);


     char json[500] = "";
     str.toCharArray(json, 500);
    //  Serial.println(json);




    StaticJsonBuffer<500> jsonBuffer;

   JsonObject& root = jsonBuffer.parseObject(json);
   if (!root.success()){
    Serial.println("parseObject() failed");
    return;
  }
   name    = root["name"];
   condition  = root["condition"];
   temp = root["temp"];
   hum = root["hum"];
   windS = root["windS"];
   windD = root["windD"];


   if ( unit == "F") {
     temp = temp*1.8-459.67;
   }
   if (unit == "C") {
     temp = temp-273.15;
   }


  screenSetter();
 }

 void currentWeatherError(const char *event, const char *data) {
   zipCode = lastZip;


 }

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

 int zipPost(String command) {
    lastZip = zipCode;
     zipCode = command;
     Particle.publish("getCurrentWeather", zipCode);
     return 1;

 }

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

 void screenSetter() {
   if (layout == "simple") {
     tft.println("Simple");
     tft.println(temp);
     tft.println(condition);

   }
   if (layout == "advanced") {
     Serial.println("Advanced");
     Serial.println(temp);
     Serial.println(condition);
     Serial.println(hum);
     Serial.println(windS);
     Serial.println(windD);

   }
 }
