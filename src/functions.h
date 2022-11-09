//=======================================
// handle function: send webpage to client
//=======================================
void webpage()
{
  server.send_P(200, "text/html", webpageCode);
}
//=====================================================
// function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  if (type == WStype_TEXT) // receive text from client
  {
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0, separator);
    String val = payloadString.substring(separator + 1);


    if (var == "LED_0_onoff") {
      if (val == "ON")
        LED_0_onoff = true;
      else
        LED_0_onoff = false;
    }

    if (var == "LED_1_onoff") {
      if (val == "ON")
        LED_1_onoff = true;
      else
        LED_1_onoff = false;
    }

    if (var == "LED_2_onoff") {
      if (val == "ON")
        LED_2_onoff = true;
      else
        LED_2_onoff = false;
    }

    if (var == "LED_3_onoff") {
      if (val == "ON")
        LED_3_onoff = true;
      else
        LED_3_onoff = false;
    }
  }
}