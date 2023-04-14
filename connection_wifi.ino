#include "motion_detector.h"

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

  wifiStatus = WL_CONNECTED;

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

bool  checkConnection() {
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
  return true;
}