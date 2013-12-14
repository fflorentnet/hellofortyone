#ifndef GLOBAL_H
#define GLOBAL_H

#define TAILLEANNEAU 16

/* Variables globales */
volatile pthread_mutex_t mutex;
volatile int nbRobotOK;
volatile CASE[TAILLEANNEAU] tapis;

#endif
