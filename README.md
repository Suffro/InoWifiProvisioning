
# Arduino WiFi Provisioning

#### Wifi provisioning for WiFiWebManager and EEPROM/FlashStorage supported boards.

Feel free to contribute to this library to make it more secure and efficent.


[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/) 
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Suffro/InoWifiProvisioning?display_name=tag&include_prereleases)](#)
[![GitHub issues](https://img.shields.io/github/issues/Suffro/InoWifiProvisioning)](https://github.com/Suffro/InoWifiProvisioning/issues)

<a href="https://www.buymeacoffee.com/suffro" title="Donate to my contributions using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my contributions using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>

### Features

- Connect your board to WiFi network from a browser.
- Cache wifi credentials.
- Reset credentials.


### Dependencies

- [**WiFiWebManager**](https://github.com/khoih-prog/WiFiWebServer)
    - [Prerequisites](https://github.com/khoih-prog/WiFiWebServer/blob/master/README.md#prerequisites)
    - [Supported boards](https://github.com/khoih-prog/WiFiWebServer/blob/master/README.md#currently-supported-boards)

- [**EEPROM**](https://docs.arduino.cc/learn/built-in-libraries/eeprom)
    - [Guide](https://docs.arduino.cc/learn/programming/eeprom-guide)

- [**FlashStorage**](https://github.com/cmaglie/FlashStorage)
    - [FlashAsEEPROM](https://github.com/cmaglie/FlashStorage/blob/master/src/FlashAsEEPROM.h)
    
**NOTE:** Flash Storage is used alternatively to EEPROM when EEPROM is not supported.


## Authors

- [Lorenzo Suffritti](https://github.com/Suffro)
