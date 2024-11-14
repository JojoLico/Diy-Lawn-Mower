#ifndef Control_h
#define Control_h

//---------- Includes ----------//
#include "Arduino.h"
#include "Motor.h"

//----------- Defines -----------//

//---------- Variables ----------//

//---------- Functions ----------//
void setupControl();
void avancer(int speedMotorP);
void reculer(int speedMotorP);
void translationDroite(int speedMotorP);
void translationGauche(int speedMotorP);
void rotationDroite(int speedMotorP);
void rotationGauche(int speedMotorP);
void enable();
void disable();
void runMotorSpeed();
void runMotorPosition();
void controlWaypoints(int distance1, int distance2, int distance3, int distance4);
bool ralliementWaypoints();
void controlAspirationSpeed(int aspirationCommandP);
void roomba(void);

#endif
