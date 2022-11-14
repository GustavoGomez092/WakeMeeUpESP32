//=====================================================
// SOUND EFFECTS
//=====================================================
void successSound() {
  if (buzzer.getState() == BUZZER_IDLE) {
    int length = sizeof(successTime) / sizeof(int);
    buzzer.playMelody(successNotes, successTime, length);
    SUCCESS_SFX = false;
  }
}

void errorSound() {
  if (buzzer.getState() == BUZZER_IDLE) {
    int length = sizeof(errorTime) / sizeof(int);
    buzzer.playMelody(errorNotes, errorTime, length);
    ERROR_SFX = false;
  }
}
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

    if (var == "LOCK_PLAYER") {
      if (val == "ON")
        LOCK_PLAYER = true;
      else
        LOCK_PLAYER = false;
    }

    if (var == "SUCCESS_SFX") {
      if (val == "ON")
        successSound();
    }

    if (var == "ERROR_SFX") {
      if (val == "ON")
        errorSound();
    }

  }
}

//=====================================================
// BUTTON PRESS TO TURN ON LED
//=====================================================
void isOnorOffButton(bool device, bool& led) {
  if(!LOCK_PLAYER) {
    if(device) {
      led = true;      
    } else {
      led = false;
    }
  }
}

//=====================================================
// LED STATUS TO PIN VOLTAGE FUNCTION
//=====================================================
void isOnorOffLED(bool device, int pin) {
  if(device == false){
    digitalWrite(pin, LOW);

  } else{
    digitalWrite(pin, HIGH);

  }
}

//=====================================================
// JSON STATUS EVAL FUNCTION
//=====================================================
void isOnorOffJSON(bool device, String& status) {
  if (device == true)
    status = "ON";
}
