#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

#include "composant.h"
#include "anneau.h"
#include "robot.h"

void traitantSIGINT(int num)
{
    if (num != SIGINT) 
		printf("y-a un lezard...");

    printf("\n---- Ctrl-C interdit ----\n");  
}

void traitantSIGTSTP(int num)
{
    if (num != SIGTSTP) 
		printf("y-a un lezard...");

    printf("\n---- Suspension du processus ----\n"); 

	kill(getpid(), SIGTSTP);
}


void initSegment()
{
	// On initialise le tableau de SEQUENCE: Il s'agit d'une suite d'operation a effectuer permettant de finaliser un PRODUIT
	
	SEQUENCE_PRODUIT_UN = (OPERATION*)malloc(sizeof(OPERATION)*5);
	SEQUENCE_PRODUIT_DEUX = (OPERATION*)malloc(sizeof(OPERATION)*5);
	SEQUENCE_PRODUIT_TROIS = (OPERATION*)malloc(sizeof(OPERATION)*6);
	SEQUENCE_PRODUIT_QUATRE=(OPERATION*)malloc(sizeof(OPERATION)*4);


	SEQUENCE_PRODUIT_UN[0]=OP1;
	SEQUENCE_PRODUIT_UN[1]=OP2;
	SEQUENCE_PRODUIT_UN[2]=OP3;
	SEQUENCE_PRODUIT_UN[3]=OP5;
	SEQUENCE_PRODUIT_UN[4]=FINI;

	
	SEQUENCE_PRODUIT_DEUX[0] = OP2;
	SEQUENCE_PRODUIT_DEUX[1] = OP4;
	SEQUENCE_PRODUIT_DEUX[2] = OP1;
	SEQUENCE_PRODUIT_DEUX[3] = OP6;
	SEQUENCE_PRODUIT_DEUX[4] = FINI;

	SEQUENCE_PRODUIT_TROIS[0] = OP3;
	SEQUENCE_PRODUIT_TROIS[1] = OP1;
	SEQUENCE_PRODUIT_TROIS[2] = OP5;
	SEQUENCE_PRODUIT_TROIS[3] = OP1;
	SEQUENCE_PRODUIT_TROIS[4] = OP3;
	SEQUENCE_PRODUIT_TROIS[5] = FINI;

	SEQUENCE_PRODUIT_QUATRE[0] = OP4;
	SEQUENCE_PRODUIT_QUATRE[1] = OP6;
	SEQUENCE_PRODUIT_QUATRE[2] = OP1;
	SEQUENCE_PRODUIT_QUATRE[3] = FINI;
}


void createThread(pthread_t t, ROBOT* r) {
	int val;
	pthread_attr_t attr; // thread attribute

    if (pthread_attr_init (&attr) != 0) {
        fprintf (stdout, "pthread_attr_init error");
        exit (1);
    }
    if (pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED) != 0)
    {
    	printf("setdetachstate failed");
    	exit(1);
    }
	if ((val = pthread_create(&t, &attr, cycleRobot, (void*) r)) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}
}
int main() {

	int i = 0;
	pthread_t robot[NBROBOT];
	pthread_t anneau_t;
	struct sigaction action;
	
	ROBOT r[NBROBOT]; //
	for (i = 1; i<=NBROBOT;i++)
	{
		r[i-1].pos = i; 
		r[i-1].composant = 0;
		r[i-1].produitEnCours = FALSE;
	}
	r[0].op = OP1;
	r[1].op = OP2;
	r[2].op = OP3;
	r[3].op = OP4;
	r[4].op = OP5;
	r[5].op = OP6;
	
	DEMANDE_ROBOT = 0;
	COMPTEUR_PROD = 0;
	NB_PRODUIT_TOTAL = NB_PRODUIT_UN+NB_PRODUIT_DEUX+NB_PRODUIT_TROIS+NB_PRODUIT_QUATRE;
	
	 /* Installation des traitants de signaux */
	signal(SIGINT, traitantSIGINT);
	action.sa_handler = traitantSIGTSTP;
	action.sa_flags = SA_RESETHAND; 
	sigaction(SIGTSTP, &action, NULL);
	
	signal(SIGINT, traitantSIGINT);
 	sigaction(SIGTSTP, &action, NULL);
	
	initSegment();
	pthread_attr_t attr; // thread attribute
    
	/* Creation thread des Robots */
	for (i = 0;i<NBROBOT;i++) {
		createThread(robot[i], &r[i]);
		
	}
	if (pthread_attr_init (&attr) != 0) {
		fprintf (stdout, "pthread_attr_init error");
	}
	
	if (pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED) != 0)
    {
		fprintf (stdout, "setdetachstate failed");
    	exit(1);
    }
	/* Creation du thread de l'anneau */	
	if ((pthread_create(&anneau_t, &attr, cycleAnneau, NULL)) != 0) {
		printf ("pthread_create error\n");
		exit (1);
	}
	
	pthread_exit (EXIT_SUCCESS);
	return 0;
}

