//---------- Includes ----------//
#include "Motor.h"

//---------- Functions ----------//

Motor::Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN, SoftwareSerial &softSerial) {
  Motor(EN_PIN, DIR_PIN, STEP_PIN);
  _driver.setup(softSerial);
  }

Motor::Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN) {
  _driver.setHardwareEnablePin(EN_PIN);
  _driver.setRunCurrent(100); // %
  _driver.enableCoolStep();
  _driver.enable();

  stepper = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);
  stepper.setEnablePin(EN_PIN);

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  }

void Motor::setupMotor(bool invP) {
  stepper.setMaxSpeed(_max_speed);
  stepper.setAcceleration(_max_acceleration);
  stepper.setPinsInverted(invP, false, true); // dir, step, en
  delay(50);
}

void Motor::motionContinuous(int speedMotorP) {
  stepper.setSpeed(speedMotorP);
  stepper.enableOutputs();
}

void Motor::motionStop() {
  stepper.setSpeed(0);
  stepper.enableOutputs();
}
