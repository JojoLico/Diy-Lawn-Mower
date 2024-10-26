//---------- Includes ----------//
#include "Arduino.h"
#include "Navigator.h"
#include "Control.h"
#include "Communicator.h"

//---------- Variables ----------//
const uint16_t scaleFactor  = 11;  // mm/pixel
const uint16_t rayon        = 100; // mm

const int speedDefault = 30;  // mm/s

uint16_t it = 0; // Nombre de waypoints
uint16_t i  = 0; // Position dans la liste de waypoints

int vxm1 = 0;
int vym1 = 1;

int wayPoints[MAX_SIZE][2]; // [x, y]

bool flagWaypoints = false;

//---------- Functions ----------//

void runWaypoints() {
  static bool motionType = false;
  //Parcours des waypoints
  if (ralliementWaypoints() && (it > 1) && (i < it-1)) {
    int vx = wayPoints[i+1][0] - wayPoints[i][0];
    int vy = wayPoints[i+1][1] - wayPoints[i][1];
    //Rotation
    if (!motionType) {
      int distance = angleVecteur(vx, vy, vxm1, vym1)*vectorielVecteur(vx, vy, vxm1, vym1)*rayon;
      controlWaypoints(distance, distance, distance, distance);
      motionType = true;
    }
    //Translation
    else {
      int distance = normeVecteur(vx, vy)*scaleFactor;
      controlWaypoints(distance, distance, -distance, -distance);
      i += 1;
      vxm1 = vx;
      vym1 = vy;
      motionType = false;
    }
  }
}

void goWaypoint() {
  flagWaypoints = true;
  avancer(speedDefault);
}

void pauseWaypoint() {
  enable();
}

void addWaypoint(int x, int y) {
  wayPoints[it][0] = x;
  wayPoints[it][1] = y;
  it += 1;
}

void suppWaypoints() {
  if (it > 0) {
    it -= 1;
  } else {
    clearWaypoints();
  }
}

void repWaypoints() {
  i    = 0;
  vxm1 = 0;
  vym1 = 1;
}

void clearWaypoints() {
  it   = 0;
  vxm1 = 0;
  vym1 = 1;
  flagWaypoints = false;
  enable();
}

int normeVecteur(int x, int y) {
  return sqrt( pow(x,2)+pow(y,2) );
}

int scalairVecteur(int x1, int y1, int x2, int y2) {
  return x1*x2+y1*y2;
}

int vectorielVecteur(int x1, int y1, int x2, int y2) {
  if (x1*y2-y1*x2 < 0) return -1; else return 1;
}

float angleVecteur(int x1, int y1, int x2, int y2) {
  int sca   = scalairVecteur(x1,y1,x2,y2);
  int norm1 = normeVecteur(x1,y1);
  int norm2 = normeVecteur(x2,y2);
  return abs(acos((float) sca/(norm1*norm2)));
}
