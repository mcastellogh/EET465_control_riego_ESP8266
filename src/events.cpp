#include "events.h"


extern Config config;

void irrigation_prg1(void){
    Serial.print(config.irr_hour);
    Serial.print(":");
    Serial.print(config.irr_minute);
    Serial.println(" Irrigation time!");
    Serial.print("Irrigation during ");
    Serial.print(config.irr_time);
    Serial.println("minutes.");
    Alarm.timerOnce(config.irr_time*60, irrigation_stop);
    irrigation_start();
}


void irrigation_start(void){
    Serial.println("Start irrigation");
    digitalWrite(VALVE1,HIGH);

}

void irrigation_stop(void){
    Serial.println("Stop irrigation");
    digitalWrite(VALVE1,LOW);
}