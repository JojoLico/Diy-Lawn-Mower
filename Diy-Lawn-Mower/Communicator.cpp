//---------- Includes ----------//
#include "Arduino.h"
#include "Communicator.h"
#include "Control.h"
#include "Sensor.h"

//---------- Variables ----------//
HardwareSerial Serial6(PC7, PC6); //RX TX

byte dataSent[BUFFER_LENGTH_SENT];
byte dataReceived[BUFFER_LENGTH_RECEIVED];

//---------- Functions ----------//
void updateControl() {
  static char cmdm1;
  char cmd = serialReadCommand(IN_COMMAND);
  Serial.println(cmd);
  if (cmd == 'V') cmd = cmdm1;
  switch (cmd) {
    case 'E':
      enable();
      break;
    case 'S':
      disable();
      break;
    case 'M':
      controlAspirationSpeed(serialReadData(IN_ASPIRATION));
      break;
    default:
      break;
  }
  cmdm1 = cmd;
}

void serialAvailable() {
   if (Serial6.available() == BUFFER_LENGTH_RECEIVED) {
    Serial6.readBytes(dataReceived, BUFFER_LENGTH_RECEIVED);
    updateControl();
   }
}

void setupSerial() {
  Serial.begin(BAUD_RATE);
  Serial6.begin(BAUD_RATE);
  delay(500);
}

void serialSendData() {
  static long current_time = 0; //ms
  if (Serial6 && ((millis()-current_time) > TIME_SEND_DATA)) {
    float vBat = powerMonitoring();

    dataSent[OUT_VBAT]      = byte( byteDivider(vBat) );
    dataSent[OUT_VBAT + 1]  = byte(vBat);
    
    Serial6.write(dataSent, BUFFER_LENGTH_SENT);
    current_time = millis();
    
    powerMonitoring();
    debugSerial(vBat);
    watchdog();
  }
}

int serialReadData(int pos) {
    return ( dataReceived[pos] << 8) | ( dataReceived[pos + 1] & 0xFF );    //Assembly the byte received to built an int
  }

char serialReadCommand(int pos) {
    return char(dataReceived[pos]);
  }
  
int byteDivider (int number) {                                              //Divide byte to be send
  return number >> 8;
}

void debugSerial (float vBat) {                                                     //Variable to serial
  Serial.println("vBat : " + String(vBat) + "V");
}
