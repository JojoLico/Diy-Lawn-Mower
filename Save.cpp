//---------- Includes ----------//
#include "Arduino.h"
#include "Save.h"
#include <SPI.h>
#include "SdFat.h"

//---------- Variables ----------//
const uint8_t SOFT_MISO_PIN      = PA6;
const uint8_t SOFT_MOSI_PIN      = PB5;
const uint8_t SOFT_SCK_PIN       = PA5;
const uint8_t SD_CHIP_SELECT_PIN = PA4;

SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;

//---------- Functions ----------//

void saveSequence(int numSaveP) {
  char XFileName[] = {'X', 48+numSaveP, '.', 't', 'x', 't'}; // 48 = '0' en ascii
  char YFileName[] = {'Y', 48+numSaveP, '.', 't', 'x', 't'}; // 48 = '0' en ascii
          
  if (!sd.begin(SD_CHIP_SELECT_PIN)) return;
  sd.remove(XFileName);
  sd.remove(YFileName);
  writeFileInt(XFileName, 0);
  writeFileInt(YFileName, 1); 
}

void writeFileInt(char fileName[], int pos) {
    File file = sd.open(fileName, FILE_WRITE);
    byte bytes[it*2];

    if (file) {
      for(int j=0; j<it*2; j=j+2){
        bytes[j]   = byte( sdByteDivider(wayPoints[j/2][pos]) );
        bytes[j+1] = byte(wayPoints[j/2][pos]);
      }   
      file.write(bytes, it*2);
      file.close();
    }
}

void readSequence(int numSaveP) {
  char XFileName[] = {'X', 48+numSaveP, '.', 't', 'x', 't'}; // 48 = '0' en ascii
  char YFileName[] = {'Y', 48+numSaveP, '.', 't', 'x', 't'}; // 48 = '0' en ascii
  
  if (!sd.begin(SD_CHIP_SELECT_PIN)) return;
  readFileInt(XFileName, 0);
  readFileInt(YFileName, 1);
  i = 0;
}

void readFileInt(char fileName[], int pos) {
    File file = sd.open(fileName);
    byte bytes[file.size()];

    if (file) {
      file.read(bytes, sizeof(bytes));
      for(int j=0; j<sizeof(bytes); j=j+2){
        wayPoints[j/2][pos] = sdReadData(bytes, j);
      } 
      file.close();
    }
}

int sdByteDivider (int number) {                      //Divide byte to be send
  return number >> 8;
}

int sdReadData(byte buf[], int Pos) {
    return ( buf[Pos] << 8) | ( buf[Pos+1] & 0xFF ); //Assembly the byte received to built an int
  }
