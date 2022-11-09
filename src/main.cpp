//==================================
// ESP32 WebSocket Server: Toggle LED
// by: Ulas Dikme
//==================================
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
//-----------------------------------------------
const char *ssid = "Casa_2.4GHz";
const char *password = "84694339";
//-----------------------------------------------
// Define Button LEDS
//-----------------------------------------------
#define LED_0 19
#define LED_1 18
#define LED_2 5
#define LED_3 17
//-----------------------------------------------
// Define Button Input
//-----------------------------------------------
#define BUTTON_0 16
#define BUTTON_1 4
#define BUTTON_2 2
#define BUTTON_3 15
//-----------------------------------------------
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
//-----------------------------------------------
boolean LED_0_onoff = false;
boolean LED_1_onoff = false;
boolean LED_2_onoff = false;
boolean LED_3_onoff = false;
String JSONtxt;
//-----------------------------------------------
#include "dashboard.h"
#include "functions.h"
//====================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  //-----------------------------------------------
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  //-----------------------------------------------
  server.on("/", webpage);
  //-----------------------------------------------
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
//====================================================================
void loop()
{
  webSocket.loop();
  server.handleClient();
  //-----------------------------------------------
  if (LED_0_onoff == false)
    digitalWrite(LED_0, LOW);
  else
    digitalWrite(LED_0, HIGH);
  
  if (LED_1_onoff == false)
    digitalWrite(LED_1, LOW);
  else
    digitalWrite(LED_1, HIGH);
  
  if (LED_2_onoff == false)
    digitalWrite(LED_2, LOW);
  else
    digitalWrite(LED_2, HIGH);
  
  if (LED_3_onoff == false)
    digitalWrite(LED_3, LOW);
  else
    digitalWrite(LED_3, HIGH);
  //-----------------------------------------------
  String LED_0_status = "OFF";
  String LED_1_status = "OFF";
  String LED_2_status = "OFF";
  String LED_3_status = "OFF";

  if (LED_0_onoff == true)
    LED_0_status = "ON";
  
  if (LED_0_onoff == true)
    LED_1_status = "ON";

  if (LED_0_onoff == true)
    LED_2_status = "ON";

  if (LED_0_onoff == true)
    LED_3_status = "ON";
  
  JSONtxt = "{"
    "\"LED_0_onoff\": \"" + LED_0_status + "\","
    "\"LED_1_onoff\": \"" + LED_1_status + "\","
    "\"LED_2_onoff\": \"" + LED_2_status + "\","
    "\"LED_3_onoff\": \"" + LED_3_status + "\","
    "}";
  webSocket.broadcastTXT(JSONtxt);
}