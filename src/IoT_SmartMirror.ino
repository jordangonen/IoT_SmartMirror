/*
 * Project IoT_SmartMirror
 * Description: Final 222 Project
 * Author: Justin Friedman, Jordan Gonen
 * Date: Fall 2017
 */

 #include "API/magicMirrorHWAPI.h"
 #include <ArduinoJson.h>




 void setup() {
   Serial.begin(9600);
   Particle.subscribe("hook-response/getCurrentWeather/0", currentWeatherHandler, MY_DEVICES);
   Particle.function("zipPost", zipPost);


 }

 void loop() {

   Particle.publish("getCurrentWeather", "10583");
   Serial.print("looped");
   delay(5000);

 }

 void currentWeatherHandler(const char *event, const char *data) {
   // Handle the webhook response
   String str = String(data);


      // Serial.println(str);


     char json[500] = "";
     str.toCharArray(json, 500);
    //  Serial.println(json);




    StaticJsonBuffer<500> jsonBuffer;

    //  int temp = atoi(strtok(json, "\"~"));
    //   String condition = strtok(NULL, "~");
    //   String name = strtok(NULL, "~");
    //   Serial.println(temp);



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

 int zipPost(String command) {
   Serial.println(command);


 }
