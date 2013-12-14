#include <stdio.h>
#include <stdlib.h>

#include "anneau.h"
#include "robot.h"
#include "composant.h"

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
	
	while(1)
	{
		checkAnneau();
		usleep(20000);
	}
}
