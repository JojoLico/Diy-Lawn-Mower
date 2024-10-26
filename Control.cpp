//---------- Includes ----------//
#include "Arduino.h"
#include "Motor.h"
#include "Control.h"
#include <SoftServo.h>

//---------- Variables ----------//
Motor motor1 = Motor(PF2, PF1, PE9, PC13, PC13);
Motor motor2 = Motor(PD7, PE8, PE11, PE3, PE3);
Motor motor3 = Motor(PC0, PC2, PE13, PE1, PE1);
Motor motor4 = Motor(PC3, PA0, PE14, PD4, PD4);

SoftServo aspiration;

const uint8_t BROSSE = PD12;
const uint8_t MOTOR  = PC1;

//---------- Functions ----------//

void controlWaypoints(int distance1, int distance2, int distance3, int distance4) {
  motor1.stepper.move(distance1*motor1.getStepPermm()); // Move distance mm
  motor2.stepper.move(distance2*motor2.getStepPermm()); // Move distance mm
  motor3.stepper.move(distance3*motor3.getStepPermm()); // Move distance mm
  motor4.stepper.move(distance4*motor4.getStepPermm()); // Move distance mm
}

bool ralliementWaypoints() {
  if ((motor1.stepper.distanceToGo() == 0) && (motor2.stepper.distanceToGo() == 0) && (motor3.stepper.distanceToGo() == 0) && (motor4.stepper.distanceToGo() == 0)) return true;
  return false;
}

void setupControl () {
    motor1.setupMotor();
    motor2.setupMotor();
    motor3.setupMotor();
    motor4.setupMotor();
    aspiration.attach(MOTOR);
    pinMode(BROSSE, OUTPUT);
}

void avancer(int speedMotorP) {
    motor1.motionContinuous(speedMotorP);
    motor2.motionContinuous(speedMotorP);
    motor3.motionContinuous(-speedMotorP);
    motor4.motionContinuous(-speedMotorP);
}

void reculer(int speedMotorP) {
    motor1.motionContinuous(-speedMotorP);
    motor2.motionContinuous(-speedMotorP);
    motor3.motionContinuous(speedMotorP);
    motor4.motionContinuous(speedMotorP);
}

void translationDroite(int speedMotorP) {
    motor1.motionContinuous(speedMotorP);
    motor2.motionContinuous(-speedMotorP);
    motor3.motionContinuous(-speedMotorP);
    motor4.motionContinuous(-speedMotorP);
}

void translationGauche(int speedMotorP) {
    motor1.motionContinuous(-speedMotorP);
    motor2.motionContinuous(speedMotorP);
    motor3.motionContinuous(speedMotorP);
    motor4.motionContinuous(speedMotorP);
}

void rotationGauche(int speedMotorP) {
    motor1.motionContinuous(-speedMotorP);
    motor2.motionContinuous(-speedMotorP);
    motor3.motionContinuous(-speedMotorP);
    motor4.motionContinuous(-speedMotorP);
}

void rotationDroite(int speedMotorP) {
    motor1.motionContinuous(speedMotorP);
    motor2.motionContinuous(speedMotorP);
    motor3.motionContinuous(speedMotorP);
    motor4.motionContinuous(speedMotorP);
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

void runMotorSpeed() {
  motor1.stepper.runSpeed();
  motor2.stepper.runSpeed();
  motor3.stepper.runSpeed();
  motor4.stepper.runSpeed();
}

void runMotorPosition() {
  motor1.stepper.run();
  motor2.stepper.run();
  motor3.stepper.run();
  motor4.stepper.run();
}

void controlAspirationSpeed(int aspirationCommandP) {
   aspiration.writeMicroseconds(1000 + 10*aspirationCommandP);
   if (aspirationCommandP == 0) digitalWrite(BROSSE, LOW); else digitalWrite(BROSSE, HIGH);
}

void refreshAspirationSpeed() {
   aspiration.refresh();
}

void roomba(void) {
  if (flagWaypoints) {
    runWaypoints();
    runMotorPosition();
  } else {
    runMotorSpeed();
  } 
}
