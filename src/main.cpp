//==================================
// ESP32 WebSocket Server: Toggle LED
// by: Ulas Dikme
//==================================
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ezBuzzer.h>
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

// DEFINE BUZZER
#define BUZZER 21
//-----------------------------------------------
// INIT WEB SERVER
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
//-----------------------------------------------
// SET BUTTON, LED & JSON VARIABLES
boolean LED_0_onoff = false;
boolean LED_1_onoff = false;
boolean LED_2_onoff = false;
boolean LED_3_onoff = false;
boolean BUTTON_0_onoff = false;
boolean BUTTON_1_onoff = false;
boolean BUTTON_2_onoff = false;
boolean BUTTON_3_onoff = false;
boolean LOCK_PLAYER = false;
boolean SUCCESS_SFX = false;
boolean ERROR_SFX = false;
String JSONtxt;

//SET BUZZER OBJECT
ezBuzzer buzzer(BUZZER);

//-----------------------------------------------
#include "dashboard.h"
#include "melodies.h"
#include "functions.h"
//====================================================================


void setup()
{
  // SERIAL OUTPUT
  Serial.begin(115200);
  
  // SET UP ALL PINMODES
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);

  //-----------------------------------------------
  // START WIFI
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
  // SET WEBSERVER ROUTE
  server.on("/", webpage);
  server.begin();
  //-----------------------------------------------
  // INIT WEBSOKETS
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}



//====================================================================
void loop()
{
  BUTTON_0_onoff = !digitalRead(BUTTON_0);
  BUTTON_1_onoff = !digitalRead(BUTTON_1);
  BUTTON_2_onoff = !digitalRead(BUTTON_2);
  BUTTON_3_onoff = !digitalRead(BUTTON_3);


  //-----------------------------------------------
  // STATUS EVALUATION
  isOnorOffButton(BUTTON_0_onoff, LED_0_onoff);
  isOnorOffButton(BUTTON_1_onoff, LED_1_onoff);
  isOnorOffButton(BUTTON_2_onoff, LED_2_onoff);
  isOnorOffButton(BUTTON_3_onoff, LED_3_onoff);
 
  // MAKE ROUNDTRIP TO WEBSOCKET DATA
  webSocket.loop();
  server.handleClient();
  
  // BUZZER LOOP
  buzzer.loop();

  // EVALUATE LED
  isOnorOffLED(LED_0_onoff, LED_0);
  isOnorOffLED(LED_1_onoff, LED_1);
  isOnorOffLED(LED_2_onoff, LED_2);
  isOnorOffLED(LED_3_onoff, LED_3);

  //-----------------------------------------------
  String LED_0_status = "OFF";
  String LED_1_status = "OFF";
  String LED_2_status = "OFF";
  String LED_3_status = "OFF";
  
  String BUTTON_0_status = "OFF";
  String BUTTON_1_status = "OFF";
  String BUTTON_2_status = "OFF";
  String BUTTON_3_status = "OFF";

  String LOCK_PLAYER_status = "OFF";

  String SUCCESS_SFX_status = "OFF";
  String ERROR_SFX_status = "OFF";

  isOnorOffJSON(LED_0_onoff, LED_0_status);
  isOnorOffJSON(LED_0_onoff, LED_0_status);
  isOnorOffJSON(LED_0_onoff, LED_0_status);
  isOnorOffJSON(LED_0_onoff, LED_0_status);
  isOnorOffJSON(BUTTON_0_onoff, BUTTON_0_status);
  isOnorOffJSON(BUTTON_1_onoff, BUTTON_1_status);
  isOnorOffJSON(BUTTON_2_onoff, BUTTON_2_status);
  isOnorOffJSON(BUTTON_3_onoff, BUTTON_3_status);
  isOnorOffJSON(LOCK_PLAYER, LOCK_PLAYER_status);
  isOnorOffJSON(SUCCESS_SFX, SUCCESS_SFX_status);
  isOnorOffJSON(ERROR_SFX, ERROR_SFX_status);
  
  JSONtxt = "{"
    "\"LED_0_onoff\": \"" + LED_0_status + "\","
    "\"LED_1_onoff\": \"" + LED_1_status + "\","
    "\"LED_2_onoff\": \"" + LED_2_status + "\","
    "\"LED_3_onoff\": \"" + LED_3_status + "\","
    "\"BUTTON_0_onoff\": \"" + BUTTON_0_status + "\","
    "\"BUTTON_1_onoff\": \"" + BUTTON_1_status + "\","
    "\"BUTTON_2_onoff\": \"" + BUTTON_2_status + "\","
    "\"BUTTON_3_onoff\": \"" + BUTTON_3_status + "\","
    "\"LOCK_PLAYER\": \"" + LOCK_PLAYER_status + "\","
    "\"SUCCESS_SFX\": \"" + SUCCESS_SFX_status + "\","
    "\"ERROR_SFX\": \"" + ERROR_SFX_status + "\""
    "}";

  webSocket.broadcastTXT(JSONtxt);
  delay(1);
}