//---------- Includes ----------//
#include "Control.h"
#include "Motor.h"
#include <Servo.h>

//---------- Variables ----------//
/*SoftwareSerial softSerialMotor1(PE4, PC13); // X RX, TX
SoftwareSerial softSerialMotor2(PE2, PE3); // Y
SoftwareSerial softSerialMotor3(PD0, PD1); // E1
SoftwareSerial softSerialMotor4(PD2, PD4); // E0

Motor motor1 = Motor(PF2, PF1, PE9, softSerialMotor1);  // X EN, DIR, STEP
Motor motor2 = Motor(PD7, PE8, PE11, softSerialMotor2); // Y
Motor motor3 = Motor(PA3, PE7, PD15, softSerialMotor3); // E1
Motor motor4 = Motor(PC3, PA0, PE14, softSerialMotor4); // E0*/

Motor motor1 = Motor(PF2, PF1, PE9);  // X EN, DIR, STEP
Motor motor2 = Motor(PD7, PE8, PE11); // Y
Motor motor3 = Motor(PA3, PE7, PD15); // E1
Motor motor4 = Motor(PC3, PA0, PE14); // E0

Servo aspiration;

const uint8_t MOTOR  = PC9;

const uint8_t CHANNEL_DROIT   = 1;
const uint8_t CHANNEL_GAUCHE  = 5;
const uint8_t CHANNEL_MOTOR   = 4;
const uint8_t CHANNEL_MODE    = 6;

const float convCmd = 5;   // Correction commande

//---------- Functions ----------//

void updateControl(bfs::SbusData data, bool connected) {
  // Wheels
  if ((data.lost_frame == 0) && (data.ch[CHANNEL_MODE] > 900) && connected) {
    setRunSpeed((data.ch[CHANNEL_GAUCHE] - 992)*convCmd, 
                (data.ch[CHANNEL_DROIT] - 992)*convCmd, 
                (data.ch[CHANNEL_DROIT] - 992)*convCmd, 
                (data.ch[CHANNEL_GAUCHE] - 992)*convCmd);
  } else {
    disable();
  }
  // Motor
  if ((data.lost_frame == 0) && connected) {
    controlAspirationSpeed(data.ch[CHANNEL_MOTOR]);
  } else {
    controlAspirationSpeed(900);
  }
}

void setupControl () {
    motor1.setupMotor(false);
    motor2.setupMotor(true);
    motor3.setupMotor(true);
    motor4.setupMotor(false);
    aspiration.attach(MOTOR);
    setRunSpeed(0, 0, 0, 0);
    disable();
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
  static int aspirationCommandM1 = 992;
  aspirationCommandM1 = 0.8*aspirationCommandM1 + 0.2*aspirationCommandP;
  aspiration.writeMicroseconds(aspirationCommandM1);
}

