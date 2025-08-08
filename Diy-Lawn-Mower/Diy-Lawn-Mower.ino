//------------ DIY Roomba ------------//
//-------------2025-08-06-------------//
//-------------Version V3-------------//
//-------------Joris Duran------------//

//---------- Includes ----------//
#include "Control.h"
#include "Communicator.h"
#include "Sensor.h"

//---------- Functions ----------//
void setup() {
  setupSensor();
  setupSerial();
  setupControl();
  setupTimer3();
}

void loop() {
  serialAvailable();
  serialSendData();
}

void setupTimer3() {
  TIM_TypeDef *Instance3 = TIM3;
  HardwareTimer *timer3 = new HardwareTimer(Instance3);
  timer3->setOverflow(50000, HERTZ_FORMAT); // Hz
  timer3->attachInterrupt(runMotorSpeed);
  timer3->resume();
}
