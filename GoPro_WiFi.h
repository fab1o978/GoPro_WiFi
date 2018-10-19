#ifndef GoPro_WiFi_h
#define GoPro_WiFi_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <GoPro_Constants.h>

typedef enum {
    ACTION_POWER_ON = 1
} gopro_actions_t;

typedef enum {
  GP_STATUS = 0,
  GP_TAKE_PICTURE = 1,
  GP_POWER_ON = 2,
  GP_POWER_OFF = 3
} gopro_commands_t;

class GoPro_WiFi
{
  public:
    GoPro_WiFi(char* SSID, char* password);
    void connect();
    wl_status_t status();
    int command(String command);
    int command(gopro_commands_t command);
    ESP8266WiFiClass WiFi;
    ESP8266WiFiMulti WiFiMulti;
  private:
    char* _SSID;
    char* _password;
    String _commands[10];
};

#endif