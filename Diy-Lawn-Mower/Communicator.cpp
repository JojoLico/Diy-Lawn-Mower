//---------- Includes ----------//
#include "Communicator.h"
#include "Control.h"
#include "Sensor.h"

//---------- Variables ----------//
HardwareSerial Serial3(PD9, PD8);

bfs::SbusRx sbus_rx(&Serial3, false);
bfs::SbusData data;

//---------- Functions ----------//

void serialAvailable() {
   volatile static unsigned int count = 10000;
   if (sbus_rx.Read()) {
    data = sbus_rx.data();
    updateControl(data, true);
    count = 0;
   } else {
    count++;
    if (count > 1000) updateControl(data, false);
   }
   delay(1); // Tempo très importante
}

void setupSerial() {
  Serial.begin(115200);
  sbus_rx.Begin();
  delay(500);
}

void serialSendData() {
  static long current_time = 0; // ms
  if ((millis()-current_time) > 500) {
    powerMonitoring();
    debugSerial();
    watchdog();
    current_time= millis();
  }
}

void debugSerial () {                                //Variable to serial
  if (Serial) {
    // Vbat
    Serial.println("vBat : " + String(getVbat()) + "V");
    // SBUS
    for (int8_t i = 0; i < data.NUM_CH; i++) {
      Serial.print(data.ch[i]);
      Serial.print("\t");
    }
    /* Display lost frames and failsafe data */
    Serial.print(data.lost_frame);
    Serial.print("\t");
    Serial.println(data.failsafe);
  }
}
