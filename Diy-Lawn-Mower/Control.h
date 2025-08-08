#ifndef Control_h
#define Control_h

//---------- Includes ----------//
#include "Arduino.h"
#include "sbus.h"

//----------- Defines -----------//

//---------- Variables ----------//

//---------- Functions ----------//
void updateControl(bfs::SbusData data, bool connected);
void setupControl();
void setRunSpeed(int speedMotor1, int speedMotor2, int speedMotor3, int speedMotor4);
void enable();
void disable();
void runMotorSpeed(void);
void controlAspirationSpeed(int aspirationCommandP);

#endif
