#ifndef Save_h
#define Save_h

//---------- External Variables ----------//
extern int wayPoints[][2]; // [x, y]
extern uint16_t it;
extern uint16_t i;

//---------- Functions ----------//
void saveSequence(int numSaveP);
void readSequence(int numSaveP);
void readFileInt(char fileName[], int pos);
void writeFileInt(char fileName[], int pos);
int sdByteDivider (int number);
int sdReadData(byte buf[], int Pos);

#endif
