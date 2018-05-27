#ifndef WIFI_SERVICE_H_
#define WIFI_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "EEPRomService.h"
#include "AppDebug.h"
#include "HttpServerH.h"

#define WIFI_AP_SSID "BE-CA"
#define WIFI_AP_PASSWORD "12345678"

#define CONNECT_OK (1)
#define CONNECT_TIMEOUT (-1)
#define CONNECT_SUSPENDED (-2)

#define EEPROM_WIFI_SSID_START 0
#define EEPROM_WIFI_SSID_END 19

#define EEPROM_WIFI_PASS_START 20
#define EEPROM_WIFI_PASS_END 39

class WifiServiceClass
{
public:
    WifiServiceClass();
    ~WifiServiceClass();
    void setupAP();
    int connect(const String &ssid, const String &pass, boolean isNew = false);
    int connect();
    void storeWifi(const String &ssid, const String &pass);
};

extern WifiServiceClass WifiService;

#endif /* WIFI_SERVICE_H_ */
