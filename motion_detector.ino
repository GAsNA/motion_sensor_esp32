#include <WiFi.h>

// include env.h with define:
//    - SSID_NAME
//    - SSID_PASS
//    - WEBHOOK_LINK
#include "env.h"
#include "connection_wifi.h"
#include "discord_webhook.h"

const int PIN_TO_SENSOR     = 19;                                // GIOP19 connected to OUTPUT pin of sensor
int       pinStateCurrent   = LOW;
int       pinStatePrevious  = LOW;

// SEE 'Debugger les problèmes de connexion' in 'https://www.upesy.fr/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32#'
void setup() {

  Serial.begin(9600);                                           // Initialize serial, bps
  
  delay(1000);                                                  // Why delay here ?

  connectionToWifi();

  pinMode(PIN_TO_SENSOR, INPUT);                                // Set ESP32 pin to input mode to read value from OUTPUT pin of sensor

}

void loop() {

  pinStatePrevious = pinStateCurrent;
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);                 // Read state of pin

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH)       // passed from non-active to active
  {
    Serial.println("Motion detected!");
    sendDiscordWebhook("Motion detected!", true, RED);
    Serial.print("\n");
  }
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW)  // passed from active to non-active
  {
    Serial.println("Motion stopped!");
    sendDiscordWebhook("Motion stopped!", false, DARK_GREEN);
    Serial.print("\n");
  }

}
