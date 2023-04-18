#include "connection_wifi.h"

void  connectionToWifi() {

  WiFi.mode(WIFI_STA);                                          // Optionnal, mode station
  WiFi.begin(SSID_NAME, SSID_PASS);                             // Set credentials for WiFi connection
  Serial.println((String)"\nConnecting to " + SSID_NAME + " with " + SSID_PASS);

  int timeout_counter = 0;

  while (WiFi.status() != WL_CONNECTED)                         // While not connected to WiFi, try again
  {
    Serial.print(".");

    delay(200);
    
    timeout_counter++;
    if (timeout_counter >= 500) {
      Serial.println("Can't establish WiFi connexion. Reload...");
      connectionToWifi();
    }
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());    // Print local ESP32 IP

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
  static int  other_status = 0;

  wifiStatus = WiFi.status();
  if (wifiStatus != WL_CONNECTED) {

    Serial.println("\nThere is some issues with the connection.");
    Serial.println((String)"Status is: " + getWifiStatus(wifiStatus));

    if (begin == NULL) { begin = time(NULL); }
    time_t end = time(NULL);
    unsigned long secondes = (unsigned long) difftime(end, begin);
    //Serial.println(secondes);

    delay(1000);

    other_status++;
    if (other_status >= 100) { connectionToWifi(); other_status = 0; }

    previousWifiStatus = wifiStatus;    
    return false;
  } else if (wifiStatus == WL_CONNECTED && previousWifiStatus != WL_CONNECTED) {
    
    time_t end = time(NULL);
    unsigned long secondes = (unsigned long) difftime(end, begin);
  
    String str = (String)"Connection lost for " + secondsToTime(secondes) + ".";
    sendDiscordWebhook(str, true, DARK_ORANGE);
  
    begin = NULL;
  }
  other_status = 0;
  previousWifiStatus = wifiStatus;
  return true;
}

String  secondsToTime(unsigned long secondes)
{
  String  str = "";

  unsigned long minutes = 0, hours = 0;

  minutes = long(secondes / 60);  secondes = secondes % 60;
  hours = long(minutes / 60);     minutes = minutes % 60;

  char  sec[50];  ltoa(secondes, sec, 10);
  char  min[50];  ltoa(minutes, min, 10);
  char  h[50];    ltoa(hours, h, 10);

  if (hours > 0) { str += (String)h + " hour.s"; }
  if (minutes > 0) {
    if (str != "") { str += " "; }
    str += (String)min + " minute.s";
  }
  if (secondes > 0) {
    if (str != "") { str += " and "; }
    str += (String)sec + " seconde.s";
  }

  return str;
}