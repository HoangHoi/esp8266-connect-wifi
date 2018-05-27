#ifndef EEPROM_SERVICE_H_
#define EEPROM_SERVICE_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "AppDebug.h"

#define EEPROM_SIZE 250

class EEPRomHClass
{
public:
    EEPRomHClass();
    ~EEPRomHClass();
    void write(const String &data, int begin, int endMax);
    String read(int begin, int end);
    void clear(int start, int end);
    void commit();
};

extern EEPRomHClass EEPROMH;

#endif /* EEPROM_SERVICE_H_ */
