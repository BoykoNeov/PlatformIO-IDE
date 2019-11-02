#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "Passwords.h"
#include <ArduinoWebsockets.h>
 
const char* ssid = ssid2;
const char* password =  password2;
 
AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
   
    Serial.println(WiFi.localIP());
  
    if(!SPIFFS.begin(true)) // Initialize SPIFFS
    {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
    }
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
    request->send(SPIFFS, "/index.html", String(), false);
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
    request->send(SPIFFS, "/style.css", "text/css");
    });
   
    server.begin();
}

void loop()
{
}