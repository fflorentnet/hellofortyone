#include "robot.h"
#include "composant.h"
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;

int p = 0;
void* initRobot(void* r)
{
		while(1)
		{

		usleep(200000);
		pthread_mutex_lock(&mutex);
				

		if (p < NBROBOT)
		{
			p++;
			switch( ((ROBOT*)r)->op)
			{
				case OP1: printf("Je fais l'operation 1\n"); break;
				case OP2: printf("Je fais l'operation 2\n"); break;
				case OP3: printf("Je fais l'operation 3\n"); break;
				case OP4: printf("Je fais l'operation 4\n"); break;
				case OP5: printf("Je fais l'operation 5\n"); break;
				case OP6: printf("Je fais l'operation 6\n"); break;

				default: printf("Je n'ai pas d'opération :(\n"); break;
			}
		}

		pthread_mutex_unlock(&mutex);
	}
	while(1);
}
void checkAnneau()
{
	pthread_mutex_lock(&mutex);
	if (p >= NBROBOT)
	{
		printf("Robots ok!  %d\n",p);
		p=0;
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
		usleep(200000);
	}
}
