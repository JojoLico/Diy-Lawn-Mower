#ifndef Motor_h
#define Motor_h

//---------- Includes ----------//
#include "Arduino.h"
#include <TMCStepper.h>
#include <AccelStepper.h>

//---------- Defines ----------//
#define R_SENSE        0.11f // Match to your driver SilentStepStick series use 0.11
#define DRIVER_ADDRESS 0b00  // TMC2209 Driver address according to MS1 and MS2

//---------- Classes ----------//
class Motor {
  public:
    Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN, uint16_t SW_RX, uint16_t SW_TX);
    void setupMotor();
    void motionContinuous(int speedMotorP);
    void motionStop();
    uint16_t getStepPermm();
    AccelStepper stepper;
  private:
    uint32_t _baudrate         = 115200;
    uint16_t _en_sw            = 4;
    uint16_t _blank_time       = 24;
    uint16_t _rms_current      = 1200; //mA
    uint16_t _microstep        = 16;
    uint16_t _stallGuard       = 50; //-[0,255]+
    uint16_t _step_per_mm      = 80;  //mm/step
    uint16_t _max_speed        = 70;  //step/s
    uint16_t _max_acceleration = 100; //step/s²
    uint16_t _en_pin           = 0;
    TMC2209Stepper _driver;
    
};

#endif
