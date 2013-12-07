#include "robot.h"
#include "composant.h"
void* initRobot(void* r)
{
	printf("test");
	switch( ((ROBOT*)r)->op)
	{
		case OP1: printf("Je fais l'operation\n");
			break;
		default: printf("Je n'ai pas d'opération :(\n"); break;
	}
}
