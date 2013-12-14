#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define NBROBOT 6
#define TAILLEANNEAU 16

void* initRobot(void* r);
void checkAnneau();
void* anneau(void* data);

#endif
