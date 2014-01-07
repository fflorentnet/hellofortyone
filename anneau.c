#include <stdio.h>
#include <stdlib.h>
#include "composant.h"
#include "anneau.h"
#include "robot.h"


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
void* anneau(void* data)
{
	initAnneau();	
	while(1)
	{
		checkAnneau();
		usleep(20000);
	}
}
