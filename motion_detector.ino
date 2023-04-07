#include <WiFi.h>

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
  
  delay(1000);                                                  // Why delay here ?

  WiFi.mode(WIFI_STA);                                          // Optionnal
  WiFi.begin(SSID_NAME, SSID_PASS);                             // Set credentials for WiFi connection
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED)                         // While not connected to WiFi, try again
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());                               // Print local ESP32 IP

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
