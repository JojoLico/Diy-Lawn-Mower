//---------- Includes ----------//
#include "Sensor.h"

//---------- Variables ----------//

const float gVbat = 11.5*3.3/4096.0; // Correction du diviseur de tension

const float seuil_1 = 24.0; // V
const float seuil_2 = 21.6; // V
const float seuil_3 = 19.8; // V

const uint8_t LED_LEVEL1 = PF9;
const uint8_t LED_LEVEL2 = PC5;
const uint8_t LED_LEVEL3 = PG13;
const uint8_t LED_ON     = PA7;
const uint8_t VBAT_PIN   = PE5;

float vBat  = 0.0;

//---------- Functions ----------//
void setupSensor() {
               
  //LED Buzzer VBAT
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_LEVEL1, OUTPUT);
  pinMode(LED_LEVEL2, OUTPUT);
  pinMode(LED_LEVEL3, OUTPUT);
  pinMode(VBAT_PIN, INPUT);
  
  digitalWrite(LED_ON, HIGH);
  digitalWrite(LED_LEVEL1, HIGH);
  digitalWrite(LED_LEVEL2, HIGH);
  digitalWrite(LED_LEVEL3, HIGH);
}

void powerMonitoring() {
  //convert ADC tension divider
  vBat = gVbat*analogRead(VBAT_PIN);           
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
  }
}

void watchdog() {
  digitalWrite(LED_ON, !digitalRead(LED_ON));
}

float getVbat() {
  return vBat;
}
