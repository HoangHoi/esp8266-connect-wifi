#include <ESP8266WebServer.h>
#include "EEPRomService.h"
#include "AppDebug.h"
#include "AppConfig.h"
#include "WifiService.h"
#include "HttpServerH.h"

ESP8266WebServer* server = nullptr;
int appMode = NORMAL_MODE;
unsigned long settingTimeout = 0;
unsigned long toggleTimeout = 0;

void handleNormalMode()
{
  if (WiFi.status() == WL_CONNECTED) {
    if(toggleTimeout <= millis()) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      toggleTimeout = millis() + LED_TIME_INTERVAL;
    }
    return;
  }

  WifiService.connect();
}

void handleServerMode()
{
  if (server) {
    server->handleClient();
  }
}

void checkButtonResetClick()
{
  if (digitalRead(PIN_RESET) == LOW && (settingTimeout + SETTING_HOLD_TIME) <= millis() && appMode != SERVER_MODE) {
    settingTimeout = millis();
    if (appMode != SERVER_MODE) {
      appMode = SERVER_MODE;
      WifiService.setupAP();
    }
  } else if(digitalRead(PIN_RESET) == HIGH) {
    settingTimeout = millis();
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("\nStart up...");
  pinMode(PIN_RESET, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  WifiService.connect();
}

void loop() {
  if (appMode == NORMAL_MODE) {
    handleNormalMode();
  } else {
    handleServerMode();
  }
  checkButtonResetClick();
}
