#include "funciones.h"


extern Config config;

#define TOUT_SERIAL_CONFIG 10000

void conf_read(void){
    StaticJsonDocument<1024> parse_comm;
    const char *ssid;
    const char *ssid_pass;
    uint8_t rtc_hour;
    uint8_t rtc_minute;
    uint8_t irr_hour;
    uint8_t irr_minute;
    uint8_t irr_time;
    uint32_t st;
    Serial.println(F("Put json config file..."));
    st=millis();
    
    while(millis()-st<TOUT_SERIAL_CONFIG){
        if (Serial.available()>0){
            String comm = Serial.readStringUntil('\n');
            Serial.println(comm);
            DeserializationError error = deserializeJson(parse_comm, comm);
            if (error) {
                Serial.print(F("Faill to parse Json file. "));
                Serial.println(error.f_str());
                break;
            }
            //--Configure device
            if(parse_comm.containsKey("device")){
                ssid=parse_comm["device"]["ssid"];
                ssid_pass=parse_comm["device"]["ssid_pass"];
                rtc_hour=parse_comm["device"]["rtc_hour"];
                rtc_minute=parse_comm["device"]["rtc_minute"];
                config.ssid=ssid;
                config.ssid_pass=ssid_pass;
                config.rtc_hour=rtc_hour;
                config.rtc_minute=rtc_minute;
                Serial.println(ssid);
                Serial.println(ssid_pass);
                Serial.println(rtc_hour);
                Serial.println(rtc_minute  );
                save_config(DEVICE_CONFIG);
            }
            //--Configure irrigation program
            if(parse_comm.containsKey("irr")){
                irr_hour=parse_comm["irr"]["irr_hour"];
                irr_minute=parse_comm["irr"]["irr_minute"];
                irr_time=parse_comm["irr"]["irr_time"];
                config.irr_hour=irr_hour;
                config.irr_minute=irr_minute;
                config.irr_time=irr_time;
                Serial.println(irr_hour);
                Serial.println(irr_minute);
                Serial.println(irr_time);
                save_config(IRR_CONFIG);
            }
            Serial.println(F("Configuration changed!"));
            
            delay(10);
            return;
        }
        delay(10);
    }
    Serial.println(F("No file received. No changes."));
    load_config();
}