#include "connection_wifi.h"

void  connectionToWifi() {

  WiFi.mode(WIFI_STA);                                          // Optionnal, mode station
  WiFi.begin(SSID_NAME, SSID_PASS);                             // Set credentials for WiFi connection
  Serial.print("\nConnecting to ");
  Serial.print(SSID_NAME);
  Serial.print(" with ");
  Serial.println(SSID_PASS);

  int timeout_counter = 0;

  while (WiFi.status() != WL_CONNECTED)                         // While not connected to WiFi, try again
  {
    Serial.print(".");
    delay(200);
    timeout_counter++;
    if (timeout_counter >= CONNECTION_TIMEOUT * 5) {
      Serial.println("Can't establish WiFi connexion. Restart...");
      ESP.restart();
    }
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());                               // Print local ESP32 IP

}

String  getWifiStatus(int status) {

  switch(status) {
    case WL_IDLE_STATUS:
      return "WL_IDLE_STATUS";
    case WL_SCAN_COMPLETED:
      return "WL_SCAN_COMPLETED";
    case WL_NO_SSID_AVAIL:
      return "WL_NO_SSID_AVAIL";
    case WL_CONNECT_FAILED:
      return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
      return "WL_CONNECTION_LOST";
    case WL_CONNECTED:
      return "WL_CONNECTED";
    case WL_DISCONNECTED:
      return "WL_DISCONNECTED";
  }

}