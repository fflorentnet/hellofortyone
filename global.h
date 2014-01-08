#ifndef GLOBAL_H
#define GLOBAL_H

#define TAILLEANNEAU 16

#define NB_PRODUIT_UN 10
#define NB_PRODUIT_DEUX 15
#define NB_PRODUIT_TROIS 12
#define NB_PRODUIT_QUATRE 8

#define NB_COMPOSANT_UN 3
#define NB_COMPOSANT_DEUX 3
#define NB_COMPOSANT_TROIS 1
#define NB_COMPOSANT_QUATRE 2

#include "composant.h"

volatile pthread_mutex_t mutex;
volatile int nbRobotOK;
volatile CASE* tapis;
volatile int* COMPTEUR_PRODUIT;
volatile int DEMANDE_ROBOT;
volatile int NB_PRODUIT_TOTAL;
volatile int COMPTEUR_PROD;

volatile OPERATION *SEQUENCE_PRODUIT_UN;
volatile OPERATION *SEQUENCE_PRODUIT_DEUX;
volatile OPERATION *SEQUENCE_PRODUIT_TROIS;
volatile OPERATION *SEQUENCE_PRODUIT_QUATRE;

#endif
