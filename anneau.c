#include <stdio.h>
#include <stdlib.h>
#include "composant.h"
#include "anneau.h"
#include "robot.h"

// Initialisation de l'anneau
void initAnneau()
{
	int i=0;
	CASE ctemp;
	tapis = (CASE*)malloc(sizeof(CASE)*TAILLEANNEAU);
	//ctemp.CASE_TYPE=VIDE;
	for (i = 0 ; i < TAILLEANNEAU;i++)
	{
		tapis[i] = ctemp;
	}
}

// Attend que chaque robot ait effectue son operation
void checkAnneau()
{
	
	pthread_mutex_lock(&mutex);

	if (nbRobotOK >= NBROBOT)
	{
		printf("%d robots sont ok!  \n", nbRobotOK);
		nbRobotOK=0;
	}
	else
	{
		printf("Attente des robots...\n");
	}
	pthread_mutex_unlock(&mutex);
}

// Cycle du thread anneau
void* cycleAnneau(void* data)
{
	initAnneau();	
	while(1)
	{
		checkAnneau();
		usleep(20000);
	}
}
