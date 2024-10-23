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

List<int> isAuto;
int usefullPins[] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1};

bool DebugMode = true;

void setup() {
  /*--------------------------------------------------------------Define the pin and modes---------------------------------------------------------------*/
  for (int pin : usefullPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    isAuto.Add(pin);
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
  /*---------------------------------------------------------------WebSite frontend calls----------------------------------------------------------------*/
  WebServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String());
  });
  WebServer.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  WebServer.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/jquery.js", "application/javascript");
  });
  /*------------------------------------------------------------------WebSite api calls------------------------------------------------------------------*/
  WebServer.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    
      int pin = usefullPins[request->arg("pin").toInt()];
      if (isAuto.Contains(pin)) {
        isAuto.Remove(isAuto.IndexOf(pin));
      }
      digitalWrite(pin, LOW);
      request->send(200, "text/plain", GetPinState(pin));
  });
  WebServer.on("/updateStates", HTTP_GET, [](AsyncWebServerRequest * request) {
    String ret = "notLogged";
    ret = "";
      for (int pin : usefullPins) {
        String retStr = GetPinState(pin);

        if (ret == "") {
          ret += '"' + retStr + '"';
        } else {
          ret += ",\"" + retStr + '"';
        }
      }

    request->send(200, "text/plain", "[" + ret + "]");
  });
  /*--------------------------------------------------------------------Start WebSite--------------------------------------------------------------------*/
  WebServer.begin();
  Serial.print("Website on: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
}

String GetPinState(int pin) {

  String retStr = "ON";
  if (digitalRead(pin)) {
    retStr = "OFF";
  }
  if (isAuto.Contains(pin)) {
    retStr = "Auto - " + retStr;
  }
  return retStr;
}
