#ifndef Navigator_h
#define Navigator_h

//---------- Defines ----------//
#define MAX_SIZE 500

//---------- Functions ----------//
void runWaypoints();
void goWaypoint();
void pauseWaypoint();
void addWaypoint(int x, int y);
void suppWaypoints();
void repWaypoints();
void clearWaypoints();
int normeVecteur(int x, int y);
int scalairVecteur(int x1, int y1, int x2, int y2);
int vectorielVecteur(int x1, int y1, int x2, int y2);
float angleVecteur(int x1, int y1, int x2, int y2);

#endif
