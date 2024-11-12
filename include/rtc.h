#ifndef _rtc_h_
#define _rtc_h_
#include <Arduino.h>
#include <time.h>
#include "wifi.h"
#include "config.h"

#define Timeout_NTP 20000

//--Prototypes
void rtc_ntp_init(void);
bool synchro_telemetry(void);
uint64_t get_unix_time_ms(void);
void re_sync(void);



#endif