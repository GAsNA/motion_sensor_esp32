#ifndef CONNECTION_WIFI_H
# define CONNECTION_WIFI_H

void    connectionToWifi();
String  getWifiStatus(int status);
bool    checkConnection();
String  secondsToTime(unsigned long sec);

#endif
