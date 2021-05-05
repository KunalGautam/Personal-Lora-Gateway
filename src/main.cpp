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

#define FWVER 0.01
#define FWRELDATE 05MAY2021

#include <html.h>

DNSServer dnsServer;
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  Serial.begin(115200);
  Serial.println('Welcome');

  //your other setup stuff...
  WiFi.softAP("esp-captive");
  dnsServer.start(53, "*", WiFi.softAPIP());
  //more handlers...
  server.begin();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webIndex);
    response->print(webFOOTER);
    request->send(response);
  });

   server.on("/wc", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webWC);
    response->print(webFOOTER);
    request->send(response);
  });

   server.on("/ss", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webSS);
    response->print(webFOOTER);
    request->send(response);
  });

   server.on("/ds", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webDS1);
    // response->print(webDS21);
    // response->print(webDS22);
    // response->print(webDS23);
    // response->print(webDS24);
    // response->print(webDS25);
    // response->print(webDS26);
    // response->print(webDS27);
    // response->print(webDS28);
    // response->print(webDS29);
    // response->print(webDS30);
    // response->print(webDS31);
    response->print(webDS4);
    response->print(webFOOTER);
    request->send(response);
  });

   server.on("/wec", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webWEC);
    response->print(webFOOTER);
    request->send(response);
  });

   server.on("/fw", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print(webHEAD);
    response->print(webFW1);
    response->print(FWVER);
    response->print(webFW2);
    response->print(webFOOTER);
    request->send(response);
  });



  server.on("/a.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/css");
    response->print(webCSS);
    request->send(response);
  });

  server.on("/a.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/javascript");
    response->print(webJS);
    request->send(response); });
}

void loop()
{
  dnsServer.processNextRequest();
}
