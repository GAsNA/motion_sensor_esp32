#ifndef DISCORD_WEBHOOK_H
# define DISCORD_WEBHOOK_H

# include <WiFiClientSecure.h>
# include <HTTPClient.h>
# include <ArduinoJson.h>
# include <ctime>

# include "colors.h"

void  sendDiscordWebhook(String title, String msg, bool ping, int color);

#endif
