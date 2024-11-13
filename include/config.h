#ifndef _config_h_
#define _config_h_

//--Includes
#include <Arduino.h>

//--Hardware PINS definitions
#define ONBOARD_LED_PIN             2
#define WIFI_LED_PIN                23
#define VALVE1                      16

//--Software constants
#define SERIAL_BAUDRATE             19200

//--Structures
struct Config {
  String ssid;
  String ssid_pass;
  uint8_t rtc_hour;
  uint8_t rtc_minute;
  uint8_t irr_hour;
  uint8_t irr_minute;
  uint8_t irr_time;
};

#endif