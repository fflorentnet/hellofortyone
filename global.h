#ifndef GLOBAL_H
#define GLOBAL_H

#define TAILLEANNEAU 16
#include "composant.h"

volatile pthread_mutex_t mutex;
volatile int nbRobotOK;
volatile CASE* tapis;

#endif
