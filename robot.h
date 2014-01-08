#ifndef ROBOT_H
#define ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define NBROBOT 6
#define TAILLEANNEAU 16

OPERATION opeSuivante(PRODUIT p);
int printCom(COMPOSANT_TYPE ca);
int printProd(PRODUIT_TYPE pr);
void* cycleRobot(void* r);
int printOp(OPERATION o);

#endif
