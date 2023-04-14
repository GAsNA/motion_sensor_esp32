#include "motion_detector.h"

const int PIN_TO_SENSOR     = 19;                                // GIOP19 connected to OUTPUT pin of sensor
int       pinStateCurrent   = LOW;
int       pinStatePrevious  = LOW;

int       wifiStatus        = WL_IDLE_STATUS;
int       previousWifiStatus= WL_IDLE_STATUS;
time_t    begin             = NULL;


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

  // CHECK WIFI CONNECTION
  wifiStatus = WiFi.status();
  if (wifiStatus != WL_CONNECTED) {

    Serial.println("\nThere is some issues with the connection.");
    Serial.println((String)"Status is: " + getWifiStatus(wifiStatus));
    delay(1000);

    if (begin == NULL) { begin = time(NULL); }
  } else if (wifiStatus == WL_CONNECTED && previousWifiStatus != WL_CONNECTED) {
    
    time_t end = time(NULL);
    unsigned long secondes = (unsigned long) difftime(end, begin);
    char buf[50];
    ltoa(secondes, buf, 10);
  
    String str = (String)"Connection lost for " + buf + " secondes.";                             // SOMETIMES IMPOSSIBLE TO REACH CONNECTION AGAIN, WHY ??
    sendDiscordWebhook(str, true, DARK_ORANGE);
  
    begin = NULL;
  }
  previousWifiStatus = wifiStatus;

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
