#include "motion_detector.h"

const int PIN_TO_SENSOR     = 19;                                // GIOP19 connected to OUTPUT pin of sensor
int       pinStateCurrent   = LOW;
int       pinStatePrevious  = LOW;

int       wifiStatus        = WL_CONNECTED;
int       previousWifiStatus= WL_CONNECTED;
time_t    begin             = NULL;


// SEE 'Debugger les problèmes de connexion' in 'https://www.upesy.fr/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32#'
void setup() {

  Serial.begin(9600);                                           // Initialize serial, bps
  
  delay(1000);

  // WIFI CONNECTION
  connectionToWifi();

  pinMode(PIN_TO_SENSOR, INPUT);                                // Set ESP32 pin to input mode to read value from OUTPUT pin of sensor

}

void loop() {

  pinStatePrevious = pinStateCurrent;
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);                 // Read state of pin

  // CHECK WIFI CONNECTION
  if (checkConnection() == false) { return; }

  // MOTION DETECTION
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH)       // passed from non-active to active
  {
    Serial.println("\nMotion detected!");
    sendDiscordWebhook("Motion detected!", true, RED);
  }
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW)  // passed from active to non-active
  {
    Serial.println("\nMotion stopped!");
    sendDiscordWebhook("Motion stopped!", false, DARK_GREEN);
  }

}
