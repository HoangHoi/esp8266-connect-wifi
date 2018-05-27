#include "WifiService.h"

/**
 * constructor
 */
WifiServiceClass::WifiServiceClass()
{
}

/**
 * destructor
 */
WifiServiceClass::~WifiServiceClass()
{
}

int WifiServiceClass::connect()
{
    ECHOLN("[WifiService][connect] Read wifi SSID and PASS from EEPROM");
    String ssid = EEPROMH.read(EEPROM_WIFI_SSID_START, EEPROM_WIFI_SSID_END);
    String pass = EEPROMH.read(EEPROM_WIFI_PASS_START, EEPROM_WIFI_PASS_END);
    return connect(ssid, pass);
}

int WifiServiceClass::connect(const String &ssid, const String &pass, boolean isNew)
{
    ECHOLN("[WifiService][connect] Open STA....");
    ECHO("[WifiService][connect] Wifi connect to: ");
    ECHOLN(ssid);
    ECHO("[WifiService][connect] With pass: ");
    ECHOLN(pass);
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin(ssid.c_str(), pass.c_str());

    int c = 0;
    ECHOLN("Waiting for Wifi to connect");
    while (c < 20) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("Wifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());
            if (isNew) {
                storeWifi(ssid, pass);
            }

            return CONNECT_OK;
        }
        delay(500);
        ECHO(".");
        c++;
    }
    ECHOLN("");
    ECHOLN("Connect timed out");
    return CONNECT_TIMEOUT;
}

void WifiServiceClass::storeWifi(const String &ssid, const String &pass)
{
    EEPROMH.write(ssid, EEPROM_WIFI_SSID_START, EEPROM_WIFI_SSID_END);
    EEPROMH.write(pass, EEPROM_WIFI_PASS_START, EEPROM_WIFI_PASS_END);
    EEPROMH.commit();
}

void WifiServiceClass::setupAP()
{
    ECHOLN("[WifiService][setupAP] Open AP....");
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    delay(3000);
    WiFi.mode(WIFI_AP);

    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);
    ECHO("[WifiService][setupAP] Connect to wifi:");
    ECHOLN(WIFI_AP_SSID);
    ECHO("[WifiService][setupAP] Password:");
    ECHOLN(WIFI_AP_PASSWORD);

    ECHOLN("[WifiService][setupAP] Softap is running!");
    IPAddress myIP = WiFi.softAPIP();
    ECHO("[WifiService][setupAP] IP address: ");
    ECHOLN(myIP);
}

WifiServiceClass WifiService;
