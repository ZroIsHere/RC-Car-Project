#include "Config.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ListLib.h>
#include <UUID.h>

AsyncWebServer WebServer(80);

/*                   D0 D1 D2 D3 D4  D5  D5  D6  D8 D9 D10*/
int usefullPins[] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};

bool DebugMode = true;

void setup() {
  /*--------------------------------------------------------------Define the pin and modes---------------------------------------------------------------*/
  for (int pin : usefullPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  /*--------------------------------------------------------------------Start serial---------------------------------------------------------------------*/
  Serial.begin(115200);
  delay(5000);
  /*--------------------------------------------------------------------Start SPIFFS---------------------------------------------------------------------*/
  if (!SPIFFS.begin()) {
    Serial.println("One error appeared when try to start SPIFFS");
    return;
  }
  /*---------------------------------------------------------------------Start WiFi----------------------------------------------------------------------*/
  WiFi.begin(ssid, wifiPassword);

  Serial.print("Connecting to: " + String(ssid));
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
  Serial.println("");

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }
  digitalWrite(LED_BUILTIN, LOW);
  /*---------------------------------------------------------------WebSite frontend calls----------------------------------------------------------------*/
  WebServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String());
  });
  WebServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  WebServer.on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/scripts.js", "application/javascript");
  });
  /*------------------------------------------------------------------WebSite api calls------------------------------------------------------------------*/
  WebServer.on("/setPinState", HTTP_POST, [](AsyncWebServerRequest * request) {
    int pin = usefullPins[request->arg("pin").toInt()];
    if (request->arg("state") == "high"){
      digitalWrite(pin, HIGH);
      Serial.println("High");
    }
    else {
      digitalWrite(pin, LOW);
      Serial.println("Low");
    }
    request->send(200, "text/plain", "");
  });
  WebServer.on("/changePinState", HTTP_POST, [](AsyncWebServerRequest * request) {
    int pin = usefullPins[request->arg("pin").toInt()];
    digitalWrite(pin, !digitalRead(pin));
    request->send(200, "text/plain", "");
  });
  /*--------------------------------------------------------------------Start WebSite--------------------------------------------------------------------*/
  WebServer.begin();
  Serial.print("Website on: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
}
