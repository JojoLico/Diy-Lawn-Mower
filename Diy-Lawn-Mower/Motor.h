#ifndef Motor_h
#define Motor_h

//---------- Includes ---------//
#include "Arduino.h"
#include <TMC2209.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

//---------- Defines ----------//

//--------- Variables ---------//

//---------- Classes ----------//
class Motor {
  public:
    Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN, SoftwareSerial &softSerial);
    Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN);
    void setupMotor(bool invP);
    void motionContinuous(int speedMotorP);
    void motionStop();
    AccelStepper stepper;
  private:
    uint16_t _max_speed        = 4100;  //step/s
    uint16_t _max_acceleration = 100; //step/s²
    TMC2209 _driver;
};

#endif
