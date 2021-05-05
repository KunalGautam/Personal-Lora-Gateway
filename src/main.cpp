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
#define FWRELDATE "05MAY2021"

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
    response->printf_P(webHEAD);
    response->printf_P(webIndex);
    response->printf_P(webFOOTER);
    request->send(response);
  });

   server.on("/wc", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf_P(webHEAD);
    response->printf_P(webWC);
    response->printf_P(webFOOTER);
    request->send(response);
  });

   server.on("/ss", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf_P(webHEAD);
    response->printf_P(webSS);
    response->printf_P(webFOOTER);
    request->send(response);
  });

   server.on("/ds", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf_P(webHEAD);
    response->printf_P(webDS1);
    response->printf_P(webDS2);
    response->printf_P(webDS3);
    response->printf_P(webFOOTER);
    request->send(response);
  });

   server.on("/wec", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf_P(webHEAD);
    response->printf_P(webWEC);
    response->printf_P(webFOOTER);
    request->send(response);
  });

   server.on("/fw", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->printf_P(webHEAD);
    response->printf_P(webFW1);
    response->print(FWVER);
    response->printf_P(webFW2);
    response->printf_P(webFOOTER);
    request->send(response);
  });



  server.on("/a.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    // AsyncResponseStream *response = request->beginResponseStream("text/css");
    // response->printf_P(webCSS);
    request->send_P(200, PSTR("text/html"),webCSS);
  });

  server.on("/a.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, PSTR("text/html"),webJS);
     });
}

void loop()
{
  dnsServer.processNextRequest();
}
