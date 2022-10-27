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
#define LED 4
//-----------------------------------------------
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
//-----------------------------------------------
boolean LEDonoff = false;
String JSONtxt;
//-----------------------------------------------
#include "dashboard.h"
#include "functions.h"
//====================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
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
  if (LEDonoff == false)
    digitalWrite(LED, LOW);
  else
    digitalWrite(LED, HIGH);
  //-----------------------------------------------
  String LEDstatus = "OFF";
  if (LEDonoff == true)
    LEDstatus = "ON";
  JSONtxt = "{\"LEDonoff\":\"" + LEDstatus + "\"}";
  webSocket.broadcastTXT(JSONtxt);
}