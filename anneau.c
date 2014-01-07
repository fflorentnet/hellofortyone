#include <stdio.h>
#include <stdlib.h>
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

	if (nbRobotOK >= NBROBOT)
	{
		//printf("bump  \n", nbRobotOK);
		
		CASE caseTemp = tapis[0];
		if (caseTemp.t == PRDT) //SORTIE : verification que le produit est fini
		{
			if (caseTemp.contenu.p.listeOperation[(sizeof(caseTemp.contenu.p.listeOperation)/sizeof(OPERATION))-1] == FINI)
			{
				printf("Un produit vient de sortir\n");
				caseTemp.t = VIDE;
				tapis[0] = caseTemp;
			}
		}
		tournerRoue();
		
		if (tapis[1].t == VIDE)
		{
			//printf("La case est vide !\n");
			COMPOSANT tempComposant;
			
			do
			{
				int random = ((double) rand() / RAND_MAX) * (MAX_R-MIN_R+1)+MIN_R;
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
		usleep(20000);
	}
}
