#include "discord_webhook.h"

//openssl s_client -showcerts -connect discordapp.com:443
    //1 s:C = US, O = "Cloudflare, Inc.", CN = Cloudflare Inc ECC CA-3
      //i:C = IE, O = Baltimore, OU = CyberTrust, CN = Baltimore CyberTrust Root
      //a:PKEY: id-ecPublicKey, 256 (bit); sigalg: RSA-SHA256
      //v:NotBefore: Jan 27 12:48:08 2020 GMT; NotAfter: Dec 31 23:59:59 2024 GMT"
const char  *discordCertificate = \
                                  "-----BEGIN CERTIFICATE-----\n"\
                                  "MIIDzTCCArWgAwIBAgIQCjeHZF5ftIwiTv0b7RQMPDANBgkqhkiG9w0BAQsFADBa\n"\
                                  "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\n"\
                                  "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\n"\
                                  "MDEyNzEyNDgwOFoXDTI0MTIzMTIzNTk1OVowSjELMAkGA1UEBhMCVVMxGTAXBgNV\n"\
                                  "BAoTEENsb3VkZmxhcmUsIEluYy4xIDAeBgNVBAMTF0Nsb3VkZmxhcmUgSW5jIEVD\n"\
                                  "QyBDQS0zMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEua1NZpkUC0bsH4HRKlAe\n"\
                                  "nQMVLzQSfS2WuIg4m4Vfj7+7Te9hRsTJc9QkT+DuHM5ss1FxL2ruTAUJd9NyYqSb\n"\
                                  "16OCAWgwggFkMB0GA1UdDgQWBBSlzjfq67B1DpRniLRF+tkkEIeWHzAfBgNVHSME\n"\
                                  "GDAWgBTlnVkwgkdYzKz6CFQ2hns6tQRN8DAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0l\n"\
                                  "BBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1UdEwEB/wQIMAYBAf8CAQAwNAYI\n"\
                                  "KwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5j\n"\
                                  "b20wOgYDVR0fBDMwMTAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQuY29tL09t\n"\
                                  "bmlyb290MjAyNS5jcmwwbQYDVR0gBGYwZDA3BglghkgBhv1sAQEwKjAoBggrBgEF\n"\
                                  "BQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzALBglghkgBhv1sAQIw\n"\
                                  "CAYGZ4EMAQIBMAgGBmeBDAECAjAIBgZngQwBAgMwDQYJKoZIhvcNAQELBQADggEB\n"\
                                  "AAUkHd0bsCrrmNaF4zlNXmtXnYJX/OvoMaJXkGUFvhZEOFp3ArnPEELG4ZKk40Un\n"\
                                  "+ABHLGioVplTVI+tnkDB0A+21w0LOEhsUCxJkAZbZB2LzEgwLt4I4ptJIsCSDBFe\n"\
                                  "lpKU1fwg3FZs5ZKTv3ocwDfjhUkV+ivhdDkYD7fa86JXWGBPzI6UAPxGezQxPk1H\n"\
                                  "goE6y/SJXQ7vTQ1unBuCJN0yJV0ReFEQPaA1IwQvZW+cwdFD19Ae8zFnWSfda9J1\n"\
                                  "CZMRJCQUzym+5iPDuI9yP+kHyCREU3qzuWFloUwOxkgAyXVjBYdwRVKD05WdRerw\n"\
                                  "6DEdfgkfCv4+3ao8XnTSrLE=\n"\
                                  "-----END CERTIFICATE-----\n";

// Get with Developer Mode on discord: user settings->advanced-> enable Developer Mode. Then right click on profile->"Copy User ID".
String  my_id = "<@474355372799557643>";

/**
 * @brief Send a embed with a discord webhook
 * 
 * @param msg Message to be sent.
 * @param ping If want to be ping or not.
 * @param color Color of the embed.
 */
void  sendDiscordWebhook(String msg, bool ping, int color) {

  WiFiClientSecure client;

  client.setCACert(discordCertificate);

  Serial.println("\nStarting connection to server...");
  if (!client.connect("discord.com", 443)) {
    Serial.println("Connection failed!");
  } else {
    Serial.println("Connected to server.");
    
    HTTPClient https;    
    if (https.begin(client, WEBHOOK_LINK)) {
      https.addHeader("Content-Type", "application/json");
      //https.addHeader("Content-Type", "multipart/form-data");

      // https://discord.com/developers/docs/resources/webhook

      Serial.println("Send message...");

      // Use arduinojson.org/v6/assistant to compute the capacity.
      StaticJsonDocument<384> doc;

      // StaticJsonObject allocates memory on the stack, it can be
      // replaced by DynamicJsonDocument which allocates in the heap.
      // DynamicJsonDocument  doc(200)

      if (ping)
        doc["content"] = my_id;

      /*StaticJsonDocument<96> attachment;
      attachment["url"] = "images/red_alert.png";
      attachment["filename"] = "red_alert.png";

      JsonArray attachments = doc.createNestedArray("attachments");
      attachments.add(attachment);*/

      StaticJsonDocument<96> file;
      file["attachment"] = "images/red_alert.png";
      file["name"] = "red_alert.png";

      JsonArray files = doc.createNestedArray("files");
      files.add(file);

      StaticJsonDocument<64> thumbnail;
      if (ping) {
        thumbnail["url"] = "https://cdn.discordapp.com/embed/avatars/4.png";              // SEND LOCAL IMAGE, HOW ??
        //thumbnail["url"] = "attachment://red_alert.png";
        //thumbnail["height"] = 256; ?
        //thumbnail["witdh"] = 256; ?
      }

      StaticJsonDocument<256> embed;
      embed["title"] = "Something happened...";
      embed["description"] = msg;
      embed["color"] = color;
      embed["thumbnail"] = thumbnail;

      JsonArray embeds = doc.createNestedArray("embeds");
      embeds.add(embed);

      String  output;
      serializeJson(doc, output);

      int httpCode = https.POST(output);

      if (httpCode > 0) {
        Serial.print("[HTTP] Status code: ");
        Serial.println(httpCode);
        Serial.println(https.errorToString(httpCode).c_str());

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.print("[HTTP] Response: ");
          Serial.println(https.getString());
        }
      } else {
        Serial.print("[HTTP] Post failed, error: ");
        Serial.println(https.errorToString(httpCode).c_str());
      }
    } else {
      Serial.println("[HTTP] Unable to connect.");
    }
  }
}