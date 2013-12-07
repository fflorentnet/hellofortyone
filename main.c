#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "composant.h"
#include "robot.h"


#define NBROBOT 6



void* afficheEtat(void* rien)
{
	printf("test ta mère");
}

void createThread(pthread_t t, ROBOT* r) {

pthread_attr_t attr; // thread attribute
	if (pthread_attr_init (&attr) != 0) {
		fprintf (stdout, "pthread_attr_init error");
		exit (1);
	}
	if (pthread_create(&t, &attr, afficheEtat, NULL) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}
}

int main() {

	// set thread detachstate attribute to DETACHED 

//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
pthread_t robot[NBROBOT];
	ROBOT r;
	r.op = OP1;
	createThread(robot[0], &r);
	return (EXIT_SUCCESS);
}

