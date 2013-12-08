#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "composant.h"
#include "robot.h"
#define NBROBOT 6

void createThread(pthread_t t, ROBOT* r) {
	int val;

	if ((val = pthread_create(&t, 0, initRobot, (void*) r)) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}
	pthread_join(t,NULL);
}

int main() {

	// set thread detachstate attribute to DETACHED 
setbuf(stdout,NULL);
setbuf(stderr,NULL);
	pthread_t robot[NBROBOT];
	ROBOT r[NBROBOT];
	r[0].op = OP1;
	r[1].op = OP2;
	r[2].op = OP3;
	r[3].op = OP4;
	r[4].op = OP5;
	r[5].op = OP6;
	
	int i = 0;
	for (i = 0;i<NBROBOT;i++)
		createThread(robot[i], &r[i]);
	exit (EXIT_SUCCESS);
}

