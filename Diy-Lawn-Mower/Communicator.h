#ifndef Communicator_h
#define Communicator_h

//---------- Includes ----------//
#include "Arduino.h"
#include "sbus.h"

//---------- Defines ----------//

//---------- Variables ----------//

//---------- Functions ----------//
void serialAvailable();
void setupSerial();
void serialSendData();
void debugSerial();

#endif
