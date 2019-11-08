// Based on example by http://shawnhymel.com/1882/how-to-create-a-web-server-with-websockets-using-an-esp32-in-arduino/

#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include "Passwords.h"
 
// Constants
const char* ssid = ssid2;
const char* password =  password2;
const char *msg_toggle_led = "toggleLED";
const char *msg_get_led = "getLEDState";
const int ws_port = 81;
const int led_pin = 2;
 
// Globals
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(ws_port);
char msg_buf[10];
int led_state = 0;
 
/***********************************************************
 * Functions
 */
 
// Callback: receiving any WebSocket message
void onWebSocketEvent(uint8_t client_num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {
 
  // Figure out the type of WebSocket event
  switch(type) 
  {
 
    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_num);
      break;
 
    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("[%u] Connection from ", client_num);
        Serial.println(ip.toString());
      }
      break;
 
    // Handle text messages from client
    case WStype_TEXT:
      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", client_num, payload);
 
      // Toggle LED
      if ( strcmp((char *)payload, "toggleLED") == 0 )
        {
          led_state = led_state ? 0 : 1;
          Serial.printf("Toggling LED to %u\n", led_state);
          digitalWrite(led_pin, led_state);
  
        // Report the state of the LED
        }
      else if ( strcmp((char *)payload, "getLEDState") == 0 )
        {
          sprintf(msg_buf, "%d", led_state);
          Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
          webSocket.sendTXT(client_num, msg_buf);
        }
      else // Message not recognized
        {
          Serial.println("[%u] Message not recognized");
        }
      break;
 
    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

/***********************************************************
 * Main
 */
void setup() 
  {
    // Init LED and turn off
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);
  
    // Start Serial port
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
  
    // Start web server
    server.begin();
  
    // Start WebSocket server and assign callback
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
  }
 
void loop() 
  {
    // Look for and handle WebSocket data
    webSocket.loop();
  }