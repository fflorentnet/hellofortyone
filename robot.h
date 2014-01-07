#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define NBROBOT 6
#define TAILLEANNEAU 16

OPERATION opeSuivante(PRODUIT* p);
void addOpe(PRODUIT* p, OPERATION op);
void* cycleRobot(void* r);
void printOp(OPERATION o);

#endif
