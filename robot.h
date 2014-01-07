#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define NBROBOT 6
#define TAILLEANNEAU 16

OPERATION opeSuivante(PRODUIT* p);
PRODUIT addOpe(PRODUIT p, OPERATION op);
void* cycleRobot(void* r);

#endif
