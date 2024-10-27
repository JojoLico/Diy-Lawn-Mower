#ifndef Motor_h
#define Motor_h

//---------- Includes ----------//
#include "Arduino.h"
#include <TMC2209.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>

//---------- Defines ----------//

//---------- Classes ----------//
class Motor {
  public:
    Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN, SoftwareSerial softSerial);
    void setupMotor();
    void motionContinuous(int speedMotorP);
    void motionStop();
    uint16_t getStepPermm();
    AccelStepper stepper;
  private:
    uint16_t _step_per_mm      = 80;  //mm/step
    uint16_t _max_speed        = 70;  //step/s
    uint16_t _max_acceleration = 100; //step/s²
    TMC2209 _driver;
};

#endif
