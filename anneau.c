#include <stdio.h>
#include <stdlib.h>

#include <time.h> // fonction srand + ctime

#include "composant.h"
#include "anneau.h"
#include "robot.h"
#include "global.h"
#define MAX_R 5
#define MIN_R 1

int* COMPTEUR_COMPOSANT; // nombre de composants restants

// Initialisation de l'anneau
void initAnneau()
{
	int i=0;
	CASE ctemp;
	
	COMPTEUR_COMPOSANT = (int*)malloc(sizeof(int)*4);
	COMPTEUR_COMPOSANT[0] = NB_COMPOSANT_UN*NB_PRODUIT_UN;
	COMPTEUR_COMPOSANT[1] = NB_COMPOSANT_DEUX*NB_PRODUIT_DEUX;
	COMPTEUR_COMPOSANT[2] = NB_COMPOSANT_TROIS*NB_PRODUIT_TROIS;
	COMPTEUR_COMPOSANT[3] = NB_COMPOSANT_QUATRE*NB_PRODUIT_QUATRE;
	
	
	tapis = (CASE*)malloc(sizeof(CASE)*TAILLEANNEAU);
	ctemp.t=VIDE;
		printf("Initialisation de l'anneau\n");
	for (i = 0 ; i < TAILLEANNEAU;i++)
	{
		tapis[i] = ctemp;
	}
	printf("Anneau initialisee\n");
}

void tournerRoue()
{
	CASE temp = tapis[TAILLEANNEAU - 1]; 
    memmove(&tapis[1], tapis, (TAILLEANNEAU - 1) * sizeof(CASE));
    tapis[0] = temp;
}

// Attend que chaque robot ait effectue son operation
void checkAnneau()
{
	int b = 0;
	pthread_mutex_lock(&mutex);
	int random;

	if (nbRobotOK >= NBROBOT)
	{
		//printf("bump  \n", nbRobotOK);
		if (COMPTEUR_COMPOSANT[0] == 0 && COMPTEUR_COMPOSANT[1] == 0 &&	COMPTEUR_COMPOSANT[2] == 0 && COMPTEUR_COMPOSANT[3] == 0)
			printf("Plus de composant.\n");

		if (tapis[0].t == PRDT) //SORTIE : verification que le produit est fini
		{
			int ope = (sizeof(tapis[0].contenu.p.listeOperation)/sizeof(OPERATION));
			
			if (tapis[0].contenu.p.listeOperation[ope-1] == FINI)
			{
				tapis[0].t = VIDE;
			}

		}
		tournerRoue();
		
		if (tapis[1].t == VIDE) 
		{
			//printf("La case est vide !\n");
			COMPOSANT tempComposant;
			
			do
			{
				//srand(time(0));
				random = rand() % 5 + 1;

				if (random < 5)
				{
					if (COMPTEUR_COMPOSANT[random-1] > 0)
					{
						b = 1;
					}
				}
				else
					b=1;
				
				switch(random)
				{
					/* case 1 à case 4 : On ajoute un composant
					*	
					*/
					case 1: tempComposant.type = C1;
							tapis[1].contenu.c = tempComposant;
							tapis[1].t = CMPSNT;
						break;
					case 2:tempComposant.type = C2;

					tapis[1].contenu.c = tempComposant;
							tapis[1].t = CMPSNT;
						break;
					case 3:tempComposant.type = C3;
					tapis[1].contenu.c = tempComposant;
							tapis[1].t = CMPSNT;
						break;
					case 4:tempComposant.type = C4;
					tapis[1].contenu.c = tempComposant;
							tapis[1].t = CMPSNT;
						break;
					default: // La case reste vide
						break;
				}	
			}while(b != 1);
		
		}
		nbRobotOK=0;
	}
	else
	{

		//printf("Attente des robots...\n");
	}
	pthread_mutex_unlock(&mutex);
}

// Cycle du thread anneau
void* cycleAnneau(void* data)
{
	initAnneau();	
	while(1)
	{
		checkAnneau();
		usleep(200000);
	}
}
