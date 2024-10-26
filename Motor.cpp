//---------- Includes ----------//
#include "Arduino.h"
#include "Motor.h"

//---------- Functions ----------//
Motor::Motor(uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STEP_PIN, uint16_t SW_RX, uint16_t SW_TX) {
  _en_pin  = EN_PIN;
  _driver  = TMC2209Stepper(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS); // Software serial
  stepper = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);
  }

void Motor::setupMotor() {
  _driver.beginSerial(_baudrate);       // SW UART drivers
  _driver.begin();
  _driver.toff(4);
  _driver.blank_time(_blank_time);
  _driver.rms_current(_rms_current);
  _driver.microsteps(_microstep);
  
  _driver.TCOOLTHRS(0xFFFFF);           // 20bit max
  _driver.semin(5);
  _driver.semax(2);
  _driver.sedn(0b01);
  _driver.SGTHRS(_stallGuard);

  stepper.setMaxSpeed(_max_speed*_step_per_mm);            // 100mm/s @ 80 steps/mm
  stepper.setAcceleration(_max_acceleration*_step_per_mm); // 100mm/s^2
  stepper.setEnablePin(_en_pin);
  stepper.setPinsInverted(false, false, true);
  delay(50);
}

void Motor::motionContinuous(int speedMotorP) {
  stepper.setSpeed(speedMotorP*_step_per_mm);
  stepper.enableOutputs();
}

void Motor::motionStop() {
  stepper.setSpeed(0);
  stepper.enableOutputs();
}

uint16_t Motor::getStepPermm() {
  return _step_per_mm;
}
