#ifndef _config_h_
#define _config_h_

//--Includes
#include <Arduino.h>

//--Hardware PINS definitions
#define ONBOARD_LED_PIN             2
#define RTC_NO_SET_LED_PIN          14
#define WIFI_LED_PIN                2
#define VALVE1_PIN                  0
#define LED_RELE_PIN                12

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