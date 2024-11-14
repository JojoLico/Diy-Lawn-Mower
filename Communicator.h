#ifndef Communicator_h
#define Communicator_h

//---------- Defines ----------//
#define BAUD_RATE      115200
#define TIME_SEND_DATA 500
#define BUFFER_LENGTH_SENT     8
#define BUFFER_LENGTH_RECEIVED 11
#define IN_COMMAND    0
#define IN_ASPIRATION 1
#define IN_VITESSE    3
#define IN_X          5
#define IN_Y          7
#define IN_NUM        9
#define OUT_ANGLE     0
#define OUT_X         2
#define OUT_Y         4
#define OUT_VBAT      6

//---------- Variables ----------//

//---------- Functions ----------//
void updateControl();
void serialAvailable();
void setupSerial();
void serialSendData();
void debugSerial(float vBat, float  angle, float  x, float y);
int serialReadData(int pos);
char serialReadCommand(int pos);
int byteDivider(int number);

#endif
