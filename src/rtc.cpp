#include "rtc.h"

#define MS_TIME_UODATE  1000

// NTP Server settings
//const char *ntp_server = "pool.ntp.org";     // Default NTP server
extern bool wifi_state;
extern Config config;

//extern bool synchronized;
uint32_t clock_NTP_timeout=0;
time_t timeFlagTrue = 0;
uint8_t diff_to_sync;
bool rtc_set;
bool resync=1;
uint32_t ms_update_time;

//--Start NTP
void rtc_ntp_init(void){
if (wifi_state){
    clock_NTP_timeout=millis();
    Serial.print(F("Config NTP..."));
    configTime(-3*3600, 0, "pool.ntp.org");
    //set clock
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {  // Wait for the NTP time to be set
        //digitalWrite(LED_SYN,HIGH);
        delay(250);
        //digitalWrite(LED_SYN,LOW);
        delay(250);
        Serial.print(F("."));
        now = time(nullptr);
        if(millis()-clock_NTP_timeout>Timeout_NTP){
            Serial.println("[ERROR] Time from NTP not configured");
            set_manual_time();
            return;
        }
    }
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    rtc_set=1;
    //synchronized=0; //to resynchronize with 5 mins multiple
    //publish_spec_attribute(SYNCHRONIZED_TELEMETRY);
    //gmtime_r(&now, &timeinfo);
    Serial.print(F("\r\nConfigured RTC date & time: "));
    Serial.printf("Hora actual: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    digitalWrite(RTC_NO_SET_LED_PIN,LOW);
    return;
    }else{
        rtc_set=0;
        Serial.println("[ERROR] No WiFi connection. Time from NTP not configured");
        set_manual_time();
    }
}

bool synchro_telemetry(void){
    time_t now = time(NULL);       // get actual time
    struct tm *timeinfo = localtime(&now);
    if (timeinfo->tm_min % 5 == 0) {
        timeFlagTrue = now;
        return 1;
    } else {
        diff_to_sync=5-(timeinfo->tm_min % 5);
        //Serial.println(diff_to_sync);
        return 0;
    }
}

uint64_t get_unix_time_ms(void){
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    // Convertir struct tm a Unix timestamp en segundos
    time_t unixTime = mktime(&timeinfo);

    // Obtener la parte de milisegundos usando gettimeofday()
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Combinar segundos y milisegundos
    uint64_t timestampMillis = (uint64_t)unixTime * 1000 + tv.tv_usec / 1000;

    // Mostrar el timestamp en milisegundos
    Serial.print("Milliseconds timestamp: ");
    Serial.println(timestampMillis);
    return timestampMillis;
}

void re_sync(void){
    time_t now = time(NULL);       // get actual time
    struct tm *time_sync_00 = localtime(&now);
    if ((time_sync_00->tm_min + time_sync_00->tm_hour) == 0) {//if new day
        if(resync){
            //synchronized=0; //Request sync
            resync=0;
        }
    }else{
        resync=1;
    }
}


void set_manual_time(void){
    digitalWrite(RTC_NO_SET_LED_PIN,HIGH);
    Serial.println("Set time mannualy");
    struct tm tm;
    tm.tm_year = 2024 - 1900;  // Año desde 1900
    tm.tm_mon = 11 - 1;     // Mes desde 0
    tm.tm_mday = 20;          // Día del mes
    tm.tm_hour = config.rtc_hour;         // Hora
    tm.tm_min = config.rtc_minute;           // Minuto
    tm.tm_sec = 0;           // Segundo
    time_t t = mktime(&tm);    // Convertir a time_t
    struct timeval now = { .tv_sec = t };
    settimeofday(&now, NULL); 
    // Configuración de zona horaria sin servidor NTP
    configTime(0, 0, "");
}

void digitalClockDisplay(void){
    if(millis()-ms_update_time>MS_TIME_UODATE){
        time_t tnow = time(nullptr);
        Serial.println(ctime(&tnow));
        ms_update_time=millis();
    }

}