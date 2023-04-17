#ifndef CONNECTION_WIFI_H
# define CONNECTION_WIFI_H

# define CONNECTION_TIMEOUT 10

void    connectionToWifi();
String  getWifiStatus(int status);
bool    checkConnection();
String  secondsToTime(unsigned long sec);

#endif
