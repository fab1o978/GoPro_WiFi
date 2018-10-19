#include <GoPro_WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

GoPro_WiFi::GoPro_WiFi(char* SSID, char* password)
{
    _SSID = SSID;
    _password = password;
}

void GoPro_WiFi::connect()
{
    // ESP8266WiFiMulti WiFiMulti;

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(_SSID, _password);

    Serial.println("Added SSID: " + String(_SSID));
}

int GoPro_WiFi::command(String command, boolean secure = false)
{
    HTTPClient http;

    if(secure)
        command = command + "t=" + String(_password);

    if (http.begin("http://10.5.5.9/" + command)) {
        int httpCode = http.GET();
        //USE_SERIAL.print("HTTP Code: ");
        //USE_SERIAL.println(httpCode);

        http.end();

        return httpCode;
    }
}

wl_status_t GoPro_WiFi::status()
{
    return WiFiMulti.run();
}