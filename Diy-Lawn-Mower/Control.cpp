//---------- Includes ----------//
#include "Arduino.h"
#include "Motor.h"
#include "Control.h"
#include <Servo.h>

//---------- Variables ----------//
SoftwareSerial softSerialMotor1(PC13, PC13);
SoftwareSerial softSerialMotor2(PE3, PE3);
SoftwareSerial softSerialMotor3(PE1, PE1);
SoftwareSerial softSerialMotor4(PD4, PD4);

Motor motor1 = Motor(PF2, PF1, PE9, softSerialMotor1);
Motor motor2 = Motor(PD7, PE8, PE11, softSerialMotor2);
Motor motor3 = Motor(PC0, PC2, PE13, softSerialMotor3);
Motor motor4 = Motor(PC3, PA0, PE14, softSerialMotor4);

Servo aspiration;
const uint8_t MOTOR  = PC1;

//---------- Functions ----------//

void setupControl () {
    motor1.setupMotor();
    motor2.setupMotor();
    motor3.setupMotor();
    motor4.setupMotor();
    aspiration.attach(MOTOR);
}

void setRunSpeed(int speedMotor1, int speedMotor2, int speedMotor3, int speedMotor4) {
    motor1.motionContinuous(speedMotor1);
    motor2.motionContinuous(speedMotor2);
    motor3.motionContinuous(speedMotor3);
    motor4.motionContinuous(speedMotor4);
}

void enable() {
  motor1.motionStop();
  motor2.motionStop();
  motor3.motionStop();
  motor4.motionStop();
}

void disable() {
  motor1.stepper.disableOutputs();
  motor2.stepper.disableOutputs();
  motor3.stepper.disableOutputs();
  motor4.stepper.disableOutputs();
}

void runMotorSpeed(void) {
  motor1.stepper.runSpeed();
  motor2.stepper.runSpeed();
  motor3.stepper.runSpeed();
  motor4.stepper.runSpeed();
}

void controlAspirationSpeed(int aspirationCommandP) {
   aspiration.writeMicroseconds(1000 + 10*aspirationCommandP);
}

