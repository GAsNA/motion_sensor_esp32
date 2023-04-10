#include "connection_wifi.h"

void  connectionToWifi() {

  WiFi.mode(WIFI_STA);                                          // Optionnal, mode station
  WiFi.begin(SSID_NAME, SSID_PASS);                             // Set credentials for WiFi connection
  Serial.print("\nConnecting to ");
  Serial.print(SSID_NAME);
  Serial.print(" with ");
  Serial.println(SSID_PASS);

  while (WiFi.status() != WL_CONNECTED)                         // While not connected to WiFi, try again
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());                               // Print local ESP32 IP

}