# IoT_SmartMirror
This project was to build a smart mirror that can retreive data from a variety of sources via webhooks in Particle Cloud and IFTTT + Photon integrations. 

The alpha was able to pull Trello work statistics, Spotify listening data and Gmail statistics via IFTTT. That was fine for testing and development durning normal college student work hours (read late night) but IFTTT servers prooved to be too slow for the tech to 1) work reliably during working hours 2) be demoable. 

Thus, the beta just focused on weather data and developing a robust webhook-API call pipeline that could be easily adapted to be used with non-weather data sources. 

Webhook responces are parsed in mustache case on Particle Cloud with additional parsing done on the emmbedded hardware with the ArduinoJson Library and built in string and const char methods. 

## User Guide 
https://github.com/justinfriedman/IoT_SmartMirror/blob/master/github-imgs/Guide.pdf
## Hardware

Particle Photon 
Smart Mirror Glass
3.5" TFT 320x480 + Touchscreen Breakout Board w/MicroSD Socket - HXD8357D

## Images
![front](https://github.com/justinfriedman/IoT_SmartMirror/blob/master/github-imgs/IMG_7566.JPG "front")
![back](https://github.com/justinfriedman/IoT_SmartMirror/blob/master/github-imgs/IMG_0192.JPG "back")

