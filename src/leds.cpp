//=======================================================================
// File:                leds.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Mayo 2024
// Info:                Part of project for Electrónica II
//=======================================================================

#include "leds.h"


//--Local variables
uint8_t led_state = LED_OFF;
uint32_t FSM_led_crono = 0;

//--Do welcome by flashing leds
void led_welcome(void){
  for(int i=0;i<10;i++){
      digitalWrite(WIFI_LED_PIN,LOW);
      delay(80);
      digitalWrite(WIFI_LED_PIN,HIGH);
      delay(80);
      digitalWrite(RTC_NO_SET_LED_PIN,HIGH);
      delay(80);
      digitalWrite(RTC_NO_SET_LED_PIN,LOW);
      delay(80);
      digitalWrite(LED_RELE_PIN ,HIGH);
      delay(80);
      digitalWrite(LED_RELE_PIN, LOW);
      delay(80);
  }
}

//--Blink led by delay
void led_blink(uint8_t ton, uint8_t toff, uint8_t led_pin){
  digitalWrite(led_pin,HIGH);
  delay(ton);
  digitalWrite(led_pin,LOW);
  delay(toff);
}

//--Flash led by delay n times
void led_flash(uint8_t ton, uint8_t count, uint8_t led_pin){
  for (uint8_t i=0; i<count; i++){
    digitalWrite(led_pin,HIGH);
    delay(ton);
    digitalWrite(led_pin,LOW);
    if(count>0){
      delay(20);
    } 
  }
}

//--State machine for blink led
//--Changes the blink parameters LED according to the service status
void led_blink_FSM(uint8_t ton, uint8_t toff, uint8_t led_pin){
  switch (led_state){
    case LED_ON:   
      digitalWrite(led_pin, HIGH);
      FSM_led_crono = millis();
      led_state = LED_WAIT_ON;
      break;

    case LED_OFF:  
      digitalWrite(led_pin, LOW);
      FSM_led_crono = millis();
      led_state = LED_WAIT_OFF;
      break;

    case LED_WAIT_OFF:
      if (millis() - FSM_led_crono >= toff){
        led_state = LED_ON;
      }
      break;
 
    case LED_WAIT_ON:
      if (millis() - FSM_led_crono >= ton){
        led_state = LED_OFF;
      }
      break;

    case LED_STOP:
      digitalWrite(led_pin, LOW);
      break;

    default:
      led_state = LED_OFF;
      break;
  }
}