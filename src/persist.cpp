#include "persist.h"

Preferences persist;

extern Config config;

#define DEFAULT_IRR_HOUR    22
#define DEFAULT_IRR_MINUTE  00
#define DEFAULT_IRR_TIME    10
#define DEFAULT_RTC_HOUR    15
#define DEFAULT_RTC_MINUTE  0
#define DEFAULT_SSID        "Estudiantes"
#define DEFAULT_SSID_PASS   "educar_2018"

void save_config(void){
    persist.begin("config");
    persist.putString("ssid",config.ssid);
    persist.putString("ssid_pass",config.ssid_pass);
    persist.putInt("rtc_hour",config.rtc_hour);
    persist.putInt("rtc_minute",config.rtc_minute);
    persist.putInt("irr_hour",config.irr_hour);
    persist.putInt("irr_minute",config.irr_minute);
    persist.putInt("irr_time",config.irr_time);
    persist.end();
    Serial.println("Config saved:");
    Serial.println(config.ssid);
    Serial.println(config.ssid_pass);
    Serial.println(config.rtc_hour);
    Serial.println(config.rtc_minute);
    Serial.println(config.irr_hour);
    Serial.println(config.irr_minute);
    Serial.println(config.irr_time);
}

void load_config(void){
    persist.begin("config");
    config.ssid=persist.getString("ssid",DEFAULT_SSID);
    config.ssid_pass=persist.getString("ssid_pass",DEFAULT_SSID_PASS);
    config.rtc_hour=persist.getInt("rtc_hour",DEFAULT_RTC_HOUR);
    config.rtc_minute=persist.getInt("rtc_minute",DEFAULT_RTC_MINUTE);
    config.irr_hour=persist.getInt("irr_hour",DEFAULT_IRR_HOUR);
    config.irr_minute=persist.getInt("irr_minute",DEFAULT_IRR_MINUTE);
    config.irr_time=persist.getInt("irr_time",DEFAULT_IRR_TIME);
    persist.end();
    Serial.println("Config readed:");
    Serial.println(config.ssid);
    Serial.println(config.ssid_pass);
    Serial.println(config.rtc_hour);
    Serial.println(config.rtc_minute);
    Serial.println(config.irr_hour);
    Serial.println(config.irr_minute);
    Serial.println(config.irr_time);
}