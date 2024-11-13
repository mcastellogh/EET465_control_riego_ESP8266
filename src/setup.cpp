//=======================================================================
// File:                setup.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Julio 2024
// Info:                Project for Electrónica II
//=======================================================================

//--Includes
#include "setup.h"

//--Local variables
uint8_t var_count;
extern bool wifi_state;
Config config;


//--Extern variables




//--Startup function
void App_setup(void){
    Serial.begin(SERIAL_BAUDRATE);

    //--PINS
    pinMode(ONBOARD_LED_PIN,OUTPUT);
    pinMode(WIFI_LED_PIN,OUTPUT);

    led_welcome();
    conf_read();

    //--Init wifi
    wifi_state=wifi_init(WIFI_STA);

    //--Set the clock
    rtc_ntp_init();

    //--Set the irrigation program
    Alarm.alarmRepeat(config.irr_hour,config.irr_minute,0, irrigation_prg1);

    //--Presentation
    Serial.println("\r\nEETP 465 Gral. Manuel Belgrano");
    Serial.println("Automated irrigation system");
}