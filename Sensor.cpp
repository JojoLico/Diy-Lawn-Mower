//---------- Includes ----------//
#include "Arduino.h"
#include "Sensor.h"
#include "MPU9250.h"

//---------- Variables ----------//
//MPU9250 mpu;

const float gVbat = 11.5*3.3/4096.0; // Correction du diviseur de tension

const float seuil_1 = 24.0; // V
const float seuil_2 = 21.6; // V
const float seuil_3 = 19.8; // V

const uint8_t FAN        = PC8;
const uint8_t BUZZER     = PC4;
const uint8_t LED_LEVEL1 = PF9;
const uint8_t LED_LEVEL2 = PC5;
const uint8_t LED_LEVEL3 = PG13;
const uint8_t LED_ON     = PD3;
const uint8_t VLOGIC     = PF8;
const uint8_t VBAT_PIN   = PE5;

float vBat  = 0.0;

//---------- Functions ----------//
void setupSensor() {
  //IMU
  /*Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();
  mpu.setup(0x68);

  mpu.setAccBias(0, 0, 0);
  mpu.setGyroBias(0, 0 ,0);
  mpu.setMagBias(396.20, 155.50, 244.56);
  mpu.setMagScale(0.66, 1.59, 1.17);
  mpu.setMagneticDeclination(1);*/
               
  //LED Buzzer VBAT
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_LEVEL1, OUTPUT);
  pinMode(LED_LEVEL2, OUTPUT);
  pinMode(LED_LEVEL3, OUTPUT);
  pinMode(VLOGIC, OUTPUT);
  pinMode(VBAT_PIN, INPUT);
  
  digitalWrite(LED_ON, HIGH);
  digitalWrite(LED_LEVEL1, HIGH);
  digitalWrite(LED_LEVEL2, HIGH);
  digitalWrite(LED_LEVEL3, HIGH);
  digitalWrite(VLOGIC, HIGH);
  buzzer();

  //Stop
  /*pinMode(STOP_PIN_A, INPUT_PULLUP);
  pinMode(STOP_PIN_R, INPUT_PULLUP);
  attachInterrupt(STOP_PIN_A, buttonPressed, FALLING);
  attachInterrupt(STOP_PIN_A, buttonPressed, FALLING);*/
  
  //FAN
  /*pinMode(FAN, OUTPUT);
  digitalWrite(FAN, HIGH);*/

}

float getYawAngle() {
  /*mpu.update();
  return mpu.getYaw();*/
  return 0.0;
}

float getXposition() {
  return 0.0; 
}

float getYposition() {
  return 0.0; 
}

float powerMonitoring() {
  float vBat = gVbat*analogRead(VBAT_PIN);           //convert ADC tension divider
  if (vBat > seuil_1 || vBat < 3.3) {
    digitalWrite(LED_LEVEL1, HIGH);
    digitalWrite(LED_LEVEL2, HIGH);
    digitalWrite(LED_LEVEL3, HIGH);
  } else if (vBat > seuil_2) {
    digitalWrite(LED_LEVEL1, HIGH);
    digitalWrite(LED_LEVEL2, HIGH);
    digitalWrite(LED_LEVEL3, LOW); 
  } else if (vBat > seuil_3) {
    digitalWrite(LED_LEVEL1, HIGH);
    digitalWrite(LED_LEVEL2, LOW);
    digitalWrite(LED_LEVEL3, LOW);  
  } else {
    digitalWrite(LED_LEVEL1, LOW);
    digitalWrite(LED_LEVEL2, LOW);
    digitalWrite(LED_LEVEL3, LOW);
    buzzer();
  }
  return vBat;
}

void buzzer() {
  tone(BUZZER, 440, 500); // LA half a second
}
