#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "composant.h"

int printCom(COMPOSANT_TYPE co)
{
	int c = -1;
	switch(co)
	{
		case C1: c=1; break;
		case C2: c=2; break;
		case C3: c=3; break;
		case C4: c=4; break;
		default: break;
	}
	return c;
}
int printProd(PRODUIT_TYPE pr)
{
	int c = -1;
	switch(pr)
	{
		case P1: c=1; break;
		case P2: c=2; break;
		case P3: c=3; break;
		case P4: c=4; break;
		default: break;
	}
	return c;
}
int printOp(OPERATION op)
{
	int c = -1;
	switch(op)
	{
		case INIT: c=100; break;
		case OP1: c=1; break;
		case OP2: c=2; break;
		case OP3: c=3; break;
		case OP4: c=4; break;
		case OP5: c=5; break;
		case OP6: c=6; break;
		case FINI: c=-1; break;
		default: break;
	}
	return c;
}
//Recuperation de l'operation suivante d'un produit en fonction de son type et de sa derniere operation
OPERATION opeSuivante(PRODUIT p)
{
	OPERATION op = FINI;
	int nbOpe = p.rangOperation;
	if (p.operation != FINI)
	{
		if (p.type == P1)
		{
			op = SEQUENCE_PRODUIT_UN[nbOpe];
		}
		else if (p.type == P2)
		{
			op = SEQUENCE_PRODUIT_DEUX[nbOpe];
		}
		else if (p.type == P3)
		{
			op = SEQUENCE_PRODUIT_TROIS[nbOpe];
		}
		else if (p.type == P4)
		{
			op = SEQUENCE_PRODUIT_QUATRE[nbOpe];
		}
	}
	else
	{
		printf("Le produit est fini\n");
	}
	return op;
}
void* cycleRobot(void* r)
{
	int pos = ((ROBOT*)r)->pos;
	int posTapis = 2*pos+1;

	OPERATION opRobot = ((ROBOT*)r)->op;
	
	while(COMPTEUR_PROD != NB_PRODUIT_TOTAL)
	{
		usleep(2000);
		pthread_mutex_lock(&mutex);
		printf("-------------\n");
		printf("Je suis le robot %d et mon operation est la %d\n", pos, opRobot);
		if (nbRobotOK < NBROBOT)
		{
			nbRobotOK++;
			
			if (tapis[posTapis].t == PRDT) // la case contient un produit
			{
				//Si le produit a fait sa derniere operation, on indique qu'il est fini
				if (opeSuivante(tapis[posTapis].contenu.p) == FINI)
				{
						tapis[posTapis].contenu.p.operation = FINI;
						tapis[posTapis].contenu.p.rangOperation = ((ROBOT*)r)->enCours.rangOperation+1;
				}
				printf("La case contient un produit\n");
				/* Si le robot n'a pas de produit en cours
				* On regarde si le robot s'occupe de la prochaine operation du robot
				* Si c'est le cas, on recupere le produit, on vide la case et on applique l'operation sur le robot 
				* Puis, le robot indique qu'il aura besoin d'une case vide pour reposer le produit */
				if (((ROBOT*)r)->produitEnCours == FALSE)
				{
					printf("Je ne possede pas de produit\n");
					OPERATION nextOp = opeSuivante(tapis[posTapis].contenu.p);
					if (nextOp == opRobot)
					{
						DEMANDE_ROBOT++;
						printf("Ajout de la nouvelle operation\n");	
						((ROBOT*)r)->enCours.operation = nextOp;
						((ROBOT*)r)->enCours.rangOperation = tapis[posTapis].contenu.p.rangOperation+1;
						((ROBOT*)r)->enCours.type=tapis[posTapis].contenu.p.type;
						((ROBOT*)r)->produitEnCours = TRUE;
						tapis[posTapis].t = VIDE;
					}
				}
			}
			else
			{
				/* Si la case est vide et que le robot a un produit dans la main
				* On repose ce produit dans la case
				* Et le robot indique qu'il n'a plus besoin de case vide */ 
				if (tapis[posTapis].t == VIDE) // la case est vide
				{
					printf("La case est vide\n");
					if ((((ROBOT*)r)->produitEnCours) == TRUE)
					{
						printf("je possede un produit\n");
						
						
						tapis[posTapis].contenu.p.operation = ((ROBOT*)r)->enCours.operation;
						tapis[posTapis].contenu.p.rangOperation = ((ROBOT*)r)->enCours.rangOperation;

						tapis[posTapis].contenu.p.type = ((ROBOT*)r)->enCours.type;
						tapis[posTapis].t = PRDT;
						DEMANDE_ROBOT--;
						((ROBOT*)r)->produitEnCours = FALSE;
					}
				}
				/* Si la case contient un composant qui contient un composant qu'il lui correspond
				* Le robot recupere ce composant et vide la case */
				else if (tapis[posTapis].t == CMPSNT)
				{
					switch(opRobot)
					{
					case OP1: 
						if (tapis[posTapis].contenu.c.type == C1)
						{
							((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
							tapis[posTapis].t = VIDE;
						}
						break;
					case OP2: 
						if (tapis[posTapis].contenu.c.type == C2)
						{
							((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
							tapis[posTapis].t = VIDE;
						}
						break;
					case OP3:
						if (tapis[posTapis].contenu.c.type == C3)
						{
							((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
							tapis[posTapis].t = VIDE;
						}
						break;
					case OP4:
						if (tapis[posTapis].contenu.c.type == C4)
						{
							((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
							tapis[posTapis].t = VIDE;
						}
						break;
					default: break;
					}
				}
				/* S'il n'y a pas de demande de place de la part des robots
				 * Et que le robot est libre de tout produit
				 * Le robot cree alors un produit avec le(s) composant(s) qu'il possede
				 * Puis fait une demande de place */
				if (DEMANDE_ROBOT == 0)
				{
					if (((ROBOT*)r)->produitEnCours == FALSE)
					{
						printf("je ne possede pas de produit\n");
						switch(opRobot)
						{
							case OP1: 
								if (((ROBOT*)r)->composant >= NB_COMPOSANT_UN)
								{
									((ROBOT*)r)->enCours.operation=INIT;
									((ROBOT*)r)->enCours.rangOperation = 0;
									((ROBOT*)r)->enCours.type = P1;
									((ROBOT*)r)->produitEnCours = TRUE;
									((ROBOT*)r)->composant = ((ROBOT*)r)->composant - NB_COMPOSANT_UN;
									DEMANDE_ROBOT++;
								}
								break;
							case OP2: 
								if (((ROBOT*)r)->composant >= NB_COMPOSANT_DEUX)
								{
									((ROBOT*)r)->enCours.operation=INIT;
									((ROBOT*)r)->enCours.rangOperation = 0;
									((ROBOT*)r)->enCours.type = P2;
									((ROBOT*)r)->produitEnCours = TRUE;
									((ROBOT*)r)->composant = ((ROBOT*)r)->composant - NB_COMPOSANT_DEUX;
									DEMANDE_ROBOT++;
								}
								break;
							case OP3:
								if (((ROBOT*)r)->composant >= NB_COMPOSANT_TROIS)
								{
									((ROBOT*)r)->enCours.operation=INIT;
									((ROBOT*)r)->enCours.rangOperation = 0;
									((ROBOT*)r)->enCours.type = P3;
									((ROBOT*)r)->produitEnCours = TRUE;
									((ROBOT*)r)->composant = ((ROBOT*)r)->composant - NB_COMPOSANT_TROIS;
									DEMANDE_ROBOT++;
								}
								break;
							case OP4:
								if (((ROBOT*)r)->composant >= NB_COMPOSANT_QUATRE)
								{
									((ROBOT*)r)->enCours.operation=INIT;
									((ROBOT*)r)->enCours.rangOperation = 0;
									((ROBOT*)r)->enCours.type = P4;
									((ROBOT*)r)->produitEnCours = TRUE;
									((ROBOT*)r)->composant = ((ROBOT*)r)->composant - NB_COMPOSANT_QUATRE;
									DEMANDE_ROBOT++;
								}
								break;
							default: break;
						}
					}
				}
			}
		}
		pthread_mutex_unlock(&mutex);
	}
	printf("Le robot s'eteint.\n");
	pthread_exit(NULL);
}
