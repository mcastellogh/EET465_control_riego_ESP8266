#include "rtc.h"

// NTP Server settings
//const char *ntp_server = "pool.ntp.org";     // Default NTP server
extern bool wifi_state;
//extern bool synchronized;
uint32_t clock_NTP_timeout=0;
time_t timeFlagTrue = 0;
uint8_t diff_to_sync;
bool rtc_set;
bool resync=1;


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
            rtc_set=0;
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
    //Serial.println(timeinfo->tm_hour);//, "%Y/%m/%d %H:%M:%S");  // Print the time
    return;
    }else{
        rtc_set=0;
        Serial.println("[ERROR] No WiFi connection. Time from NTP not configured");
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