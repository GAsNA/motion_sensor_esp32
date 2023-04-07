// include env.h with define:
//    - SSID_NAME
//    - SSID_PASS
//    - WEBHOOK_LINK
#include "env.h"

const int PIN_TO_SENSOR     = 19;                                // GIOP19 connected to OUTPUT pin of sensor
int       pinStateCurrent   = LOW;
int       pinStatePrevious  = LOW;

void setup() {

  Serial.begin(9600);                                           // Initialize serial, bps
  pinMode(PIN_TO_SENSOR, INPUT);                                // Set ESP32 pin to input mode to read value from OUTPUT pin of sensor

}

void loop() {

  pinStatePrevious = pinStateCurrent;
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);                 // Read state of pin

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH)       // passed from non-active to active
  {
    Serial.println("Motion detected!");
    // TODO: send webhook of 'motion detected'
  }
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW)  // passed from active to non-active
  {
    Serial.println("Motion stopped!");
    // TODO: send webhook of 'motion stopped'
  }

}
