#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "composant.h"
#include "anneau.h"

#include "robot.h"


void createThread(pthread_t t, ROBOT* r) {
	int val;
	pthread_attr_t attr; // thread attribute
    if (pthread_attr_init (&attr) != 0) {
            fprintf (stdout, "pthread_attr_init error");
            exit (1);
    }
	if ((val = pthread_create(&t, &attr, initRobot, (void*) r)) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}
	//pthread_join(t,NULL);
}

int main() {
	pthread_t robot[NBROBOT];
	pthread_t anneau_t;
	ROBOT r[NBROBOT];
	r[0].op = OP1;
	r[1].op = OP2;
	r[2].op = OP3;
	r[3].op = OP4;
	r[4].op = OP5;
	r[5].op = OP6;
	
	pthread_attr_t attr; // thread attribute
    if (pthread_attr_init (&attr) != 0) {
		fprintf (stdout, "pthread_attr_init error");
	}
           
	int i = 0;
	for (i = 0;i<NBROBOT;i++)
		createThread(robot[i], &r[i]);
	
	if ((pthread_create(&anneau_t, &attr, anneau, NULL)) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}

	while(1);
	exit (EXIT_SUCCESS);
}

