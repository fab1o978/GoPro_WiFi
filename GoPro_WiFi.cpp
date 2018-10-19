#include <GoPro_WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

// const string GoPro_WiFi::GP_STATUS = "http://10.5.5.9/bacpac/sx?t={password}";

GoPro_WiFi::GoPro_WiFi(char* SSID, char* password)
{
    _SSID = SSID;
    _password = password;

    _commands[GP_STATUS] =  "http://10.5.5.9/camera/sx?t={password}";
    _commands[GP_POWER_ON] =  "http://10.5.5.9/bacpac/PW?t={password}&p=%01";
    _commands[GP_POWER_OFF] = "http://10.5.5.9/bacpac/PW?t={password}&p=%00";
    _commands[GP_TAKE_PICTURE] =  "http://10.5.5.9/bacpac/SH?t={password}&p=%01";
}

void GoPro_WiFi::connect()
{
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(_SSID, _password);

    Serial.println("Added SSID: " + String(_SSID));
}

int GoPro_WiFi::command(String command)
{
    HTTPClient http;

    if(command.indexOf("{password}") != -1){
        command.replace("{password}", _password);
    }

    Serial.print("Command: ");
    Serial.println(command);

    if (http.begin(command)) {
        int httpCode = http.GET();

        http.end();

        return httpCode;
    } else {
        Serial.println("http error!");
    }
}

int GoPro_WiFi::command(gopro_commands_t commandID)
{
    return command(_commands[commandID]);
}

wl_status_t GoPro_WiFi::status()
{
    return WiFiMulti.run();
}