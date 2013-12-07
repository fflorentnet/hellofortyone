#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "composant.h"
#include "robot.h"


#define NBROBOT 6


pthread_t robot[NBROBOT];
pthread_attr_t attr; // thread attribute


void createThread(pthread_t t, ROBOT* r) {
	if (pthread_create(&t, &attr, initRobot, (void *) r) < 0) {
		fprintf (stderr, "pthread_create error\n");
		exit (1);
	}
}

int main() {

	// set thread detachstate attribute to DETACHED 
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	ROBOT r;
	createThread(robot[0], &r);

}

