#include <Arduino.h>
#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"

DNSServer dnsServer;
AsyncWebServer server(80); 

void setup(){
   Serial.begin(115200);
 
  if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }
  //your other setup stuff...
  WiFi.softAP("esp-captive");
  dnsServer.start(53, "*", WiFi.softAPIP());
  //more handlers...
  server.begin();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/a.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/a.css", "text/css");
  });
}

void loop(){
  dnsServer.processNextRequest();
}
