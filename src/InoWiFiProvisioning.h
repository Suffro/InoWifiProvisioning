
const int BUTTON_PIN = 2;  // the number of the pushbutton pin
bool buttonUsed = false;  // variable for reading the pushbutton status
int buttonState = 0;  // variable for reading the pushbutton status

#include <WiFiWebServer.h>
#ifdef ARDUINO_SAMD_NANO_33_IOT // Check if it's an Arduino Uno
  #include <FlashAsEEPROM.h>
  void EEPROMCommit() {
    EEPROM.commit();
  };
#else
  #include <EEPROM.h>
  void EEPROMCommit() {
    // do nothing
  };
#endif
#include "secrets.h"
#include "utils.h"
#include "eepromManager.h"
#include "apServer.h"
#include "resetButton.h"