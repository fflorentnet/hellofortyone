#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "composant.h"

void* cycleRobot(void* r)
{
	while(1)
	{
		usleep(200000);
		pthread_mutex_lock(&mutex);
				

		if (nbRobotOK < NBROBOT)
		{
			nbRobotOK++;
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
			printf("\t%d\n",nbRobotOK);
		}

		pthread_mutex_unlock(&mutex);
	}
}
