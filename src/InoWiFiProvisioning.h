
const int BUTTON_PIN = 2;  // the number of the pushbutton pin
bool buttonUsed = false;  // variable for reading the pushbutton status
int buttonState = 0;  // variable for reading the pushbutton status

#include <WiFiWebServer.h>
// Check if it's an AVR ATmega family board
#if defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega256RFR2__) || defined(__AVR_ATmega128RFA1__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega328PB__)
  #include <EEPROM.h>
  void EEPROMCommit() {
    // do nothing
  };
#else
  #include <FlashAsEEPROM.h>
  void EEPROMCommit() {
    EEPROM.commit();
  };
#endif
#include "secrets.h"
#include "utils.h"
#include "eepromManager.h"
#include "apServer.h"
#include "resetButton.h"