#ifndef Sensor_h
#define Sensor_h

//---------- Includes ---------//
#include "Arduino.h"

//---------- Defines ----------//

//--------- Variables ---------//

//--------- Functions ---------//
void setupSensor();
void watchdog();
void powerMonitoring();

float getVbat();

#endif
