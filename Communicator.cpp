//---------- Includes ----------//
#include "Arduino.h"
#include "Communicator.h"
#include "Control.h"
#include "Navigator.h"
#include "Save.h"
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
    case 'A':
      avancer(serialReadData(IN_VITESSE));
      break;
    case 'R':
      reculer(serialReadData(IN_VITESSE));
      break;
    case 'D':
      translationDroite(serialReadData(IN_VITESSE));
      break;
    case 'G':
      translationGauche(serialReadData(IN_VITESSE));
      break;
    case 'T':
      rotationDroite(serialReadData(IN_VITESSE));
      break;
    case 'Q':
      rotationGauche(serialReadData(IN_VITESSE));
      break;
    case 'E':
      enable();
      break;
    case 'S':
      disable();
      break;
    case 'M':
      controlAspirationSpeed(serialReadData(IN_ASPIRATION));
      break;
    case 'C':
      addWaypoint(serialReadData(IN_X), serialReadData(IN_Y));
      break;
    case 'O':
      goWaypoint();
      break;
    case 'P':
      pauseWaypoint();
      break;
    case 'F':
      clearWaypoints();
      break;
    case 'X':
      suppWaypoints();
      break;
    case 'J':
      repWaypoints();
      break;
    case 'W':
      saveSequence(serialReadData(IN_NUM));
      break;
    case 'B':
      readSequence(serialReadData(IN_NUM));
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
    powerMonitoring();
    dataSent[OUT_ANGLE]     = byte( byteDivider(angle) );
    dataSent[OUT_ANGLE + 1] = byte(angle);
    
    dataSent[OUT_X]         = byte( byteDivider(x) );
    dataSent[OUT_X + 1]     = byte(x);

    dataSent[OUT_Y]         = byte( byteDivider(y) );
    dataSent[OUT_Y + 1]     = byte(y);

    dataSent[OUT_VBAT]      = byte( byteDivider(vBat) );
    dataSent[OUT_VBAT + 1]  = byte(vBat);
    
    Serial6.write(dataSent, BUFFER_LENGTH_SENT);
    current_time = millis();
    debugSerial();
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

void debugSerial () {                                                       //Variable to serial
  Serial.println("angle : " + String(angle) + "°");
  Serial.println("x : " + String(x));
  Serial.println("x : " + String(y));
  Serial.println("Vbat : " + String(vBat) + "V");
}
