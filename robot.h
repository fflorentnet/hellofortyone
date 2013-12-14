#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#define NBROBOT 6
#define TAILLEANNEAU 16

extern pthread_mutex_t mutex;

extern int nbRobotOK = 0;

void* initRobot(void* r);
void checkAnneau();
void* anneau(void* data);

#endif
