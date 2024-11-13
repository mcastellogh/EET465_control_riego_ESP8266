/*********************************************************************************
 * 
 *                       ELECTRONICA II UTN - FRRO                                *
 * 
 * *******************************************************************************/

//===================[File header]================================================
// File:                app.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Julio 2024
// Info:                Project 'WiFi' for Electrónica II

//====================[Use & storage]============================================
// PCB:                 NodeMCU 
// Plataforma:          ESP32 
// Use:                 wifi
// Folder:              wifi
// Proyect name:        wifi

//====================[ToDo]=====================================================     
//        
//
//
//====================[Bugs]=====================================================     
//     
//                   
//
//====================[Commits]==================================================     
//
// Last commit:
//
//===================[End file header]===========================================


//--Includes
#include "app.h"

//--Local variables
bool wifi_state;


void digitalClockDisplay() {
  time_t tnow = time(nullptr);
  Serial.println(ctime(&tnow));

}
//--Main application
void App_loop(void){
    digitalClockDisplay();
    wifi_state=wifi_loop();
    Alarm.delay(1000);
}


