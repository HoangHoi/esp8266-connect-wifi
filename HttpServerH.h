#ifndef HttpServerH_H_
#define HttpServerH_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "AppConfig.h"
#include "EEPRomService.h"
#include "WifiService.h"
#include "AppDebug.h"

extern ESP8266WebServer* server;

extern void startConfigServer();
extern void handleOk();
extern void handleRoot();
extern void handleConnectTo();
extern void handleStatus();
extern void handleWifis();

#endif /* HttpServerH_H_ */
