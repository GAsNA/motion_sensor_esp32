#ifndef DISCORD_WEBHOOK_H
# define DISCORD_WEBHOOK_H

# include <WiFiClientSecure.h>
# include <HTTPClient.h>
# include <ArduinoJson.h>

# include "colors.h"

void  sendDiscordWebhook(String msg, bool ping, int color);

#endif
