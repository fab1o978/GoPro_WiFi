#ifndef GoPro_WiFi_h
#define GoPro_WiFi_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

class GoPro_WiFi
{
  public:
    GoPro_WiFi(char* SSID, char* password);
    void connect();
    wl_status_t status();
    int command(String command, boolean secure);
    ESP8266WiFiClass WiFi;
    ESP8266WiFiMulti WiFiMulti;
  private:
    char* _SSID;
    char* _password;
};

#endif