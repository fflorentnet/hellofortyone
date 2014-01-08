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

void affichageTapis()
{
	int i = 0;
	for (i=0 ;  i < TAILLEANNEAU; i++)
	{
		if(tapis[i].t == VIDE)
		{
			printf("La case %d est vide\n",i);
		}
		else if(tapis[i].t == PRDT)
		{
			printf("La case %d contient un PRODUIT %d a l'operation %d\n",i,printProd(tapis[i].contenu.p.type), printOp(tapis[i].contenu.p.operation));
		}
		else if(tapis[i].t == CMPSNT)
		{
			printf("La case %d contient un composant de type %d\n",i, printCom(tapis[i].contenu.c.type));
		}
	}
}
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
	int i;

	/*for(i=0; i<TAILLEANNEAU; i++) {
		printf("Case %d : %d\n",i,tapis[i].t);
	}*/

	CASE* temp = (CASE*)malloc(sizeof(CASE)*TAILLEANNEAU); 
	CASE last = tapis[TAILLEANNEAU-1];
	for(i=TAILLEANNEAU-1; i>0; i--) {
		temp[i] = tapis[i-1];
	}
	
	temp[0] = last;
    tapis = temp;
}

// Attend que chaque robot ait effectue son operation
void checkAnneau()
{
	int b = 0;
	int c=0;
	pthread_mutex_lock(&mutex);
	int random;

	if (nbRobotOK >= NBROBOT)
	{
		affichageTapis();

		if (COMPTEUR_COMPOSANT[0] == 0 && COMPTEUR_COMPOSANT[1] == 0 &&	COMPTEUR_COMPOSANT[2] == 0 && COMPTEUR_COMPOSANT[3] == 0)
		{
				printf("Plus de composant.\n");
				c=1;
		}


		
		printf("Demande robot : %d\n",DEMANDE_ROBOT);
		if (tapis[0].t == PRDT)
		{
			if (tapis[0].contenu.p.operation == FINI)
			{
				printf("Le produit est fini!\n");
				COMPTEUR_PROD++;
				tapis[0].t = VIDE;
			}
		}
		tournerRoue();
		if (DEMANDE_ROBOT == 0) // Les robots n'ont pas besoin d'une case libre
		{
			if (tapis[1].t == VIDE && c != 1) 
			{
				COMPOSANT tempComposant;
				do
				{
					random = rand() % 5 + 1;
					if (random < 5)
					{
						if (COMPTEUR_COMPOSANT[random-1] > 0)
						{
							b = 1;
							COMPTEUR_COMPOSANT[random-1]--;
						}
					}
					else
						b=1;

					switch(random)
					{
					/* case 1 à case 4 : On ajoute un composant
					 *	
					 */
					case 1: tapis[1].contenu.c.type = C1;
						tapis[1].t = CMPSNT;
						break;
					case 2:tapis[1].contenu.c.type = C2;
						tapis[1].t = CMPSNT;
						break;
					case 3:tapis[1].contenu.c.type = C3;
						tapis[1].t = CMPSNT;
						break;
					case 4:tapis[1].contenu.c.type = C4;
						tapis[1].t = CMPSNT;
						break;
					default: // La case reste vide
						tapis[1].t = VIDE;
						break;
					}	
				}while(b != 1);
			}
		}
		nbRobotOK=0;
		printf("Nombre de produit fini:%d\n",COMPTEUR_PROD);
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
	while(COMPTEUR_PROD != NB_PRODUIT_TOTAL)
	{
		checkAnneau();
		usleep(2000);
	}
}
