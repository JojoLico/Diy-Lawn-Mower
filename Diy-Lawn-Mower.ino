               //------------ DIY Roomba ------------//
//-------------2020-11-20-------------//
//-------------Version V2-------------//
//-------------Joris Duran------------//

// TODO asservissement en angle
// TODO asservissement en position
// TODO smart Roomba

//---------- Includes ----------//
#include "Control.h"
#include "Communicator.h"
#include "Sensor.h"

//---------- Functions ----------//
void setup() {
  setupSerial();
  setupControl();
  setupSensor();
  setupTimer3();
}

void loop() {
  serialAvailable();
  serialSendData();
}

void setupTimer3() {
  TIM_TypeDef *Instance3 = TIM3;
  HardwareTimer *timer3 = new HardwareTimer(Instance3);
  timer3->setOverflow(10000, HERTZ_FORMAT); // Hz
  timer3->attachInterrupt(roomba);
  timer3->resume();
}
