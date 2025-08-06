#ifndef Communicator_h
#define Communicator_h

//---------- Defines ----------//
#define BAUD_RATE      115200
#define TIME_SEND_DATA 500
#define BUFFER_LENGTH_SENT     8
#define BUFFER_LENGTH_RECEIVED 11
#define IN_COMMAND    0
#define IN_ASPIRATION 1
#define OUT_VBAT      6

//---------- Variables ----------//

//---------- Functions ----------//
void updateControl();
void serialAvailable();
void setupSerial();
void serialSendData();
void debugSerial(float vBat);
int serialReadData(int pos);
char serialReadCommand(int pos);
int byteDivider(int number);

#endif
