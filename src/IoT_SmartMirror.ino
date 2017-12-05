/*
 * Project IoT_SmartMirror
 * Description: Final 222 Project
 * Author: Justin Friedman, Jordan Gonen
 * Date: Fall 2017
 */

 #include "API/magicMirrorHWAPI.h"
 #include <ArduinoJson.h>

String zipCode = "";
String lastZip = "";
String layout = "simple";
String unit = "F";


 void setup() {
   Serial.begin(9600);
   Particle.subscribe("hook-response/getCurrentWeather/0", currentWeatherHandler, MY_DEVICES);
   Particle.subscribe("hook-error/getCurrentWeather/0", currentWeatherError, MY_DEVICES);

   Particle.subscribe("hook-response/getCurrentWeather/0", threeDayWeatherHandler, MY_DEVICES);

   Particle.function("zipPost", zipPost);
   Particle.function("layoutSetter", layoutSetter);
   Particle.function("unitSetter", unitSetter);


 }

 void loop() {





 }

 void currentWeatherHandler(const char *event, const char *data) {
   // Handle the webhook response
   Serial.println(data[2]);

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
  const char* name    = root["name"];
  const char* condition  = root["condition"];
  double temp = root["temp"];
  double hum = root["hum"];
  double windS = root["windS"];
  double windD = root["windD"];


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
  const char* conditions1    = root["conditions1"];
  const char* conditions2    = root["conditions2"];
  const char* conditions3    = root["conditions3"];
  double high1 = root["high1"];
  double low1 = root["low1"];
  double high2 = root["high2"];
  double low2 = root["low2"];
  double high3 = root["high3"];
  double low3 = root["low3"];


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
     return 1;

   }
   if (command == "advanced") {
     layout = command;
     Serial.println("Layout is now advanced");
     return 1;
   }
   if (command == "3day") {
     layout = command;
     Serial.println("Layout is now 3day");
     return 1;
   }
   else {
     Serial.println("Not a layout");
     return -1;
   }
 }

 int unitSetter(String command) {
   if (command == "F") {
     unit = command;
     Serial.println("F");
     return 1;
   }
   if (command == "C") {
     unit = command;
     Serial.println("C");
     return 1;
   }
   else {
     return -1;
   }


 }


 void publishScheduler() {
   if (layout == "simple" || layout == "advanced") {
      Particle.publish("getCurrentWeather", zipCode);
   }
   if (layout == "3day") {

   }
 }
