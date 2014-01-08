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

OPERATION opeSuivante(PRODUIT p)
{
	OPERATION op = FINI;
	int nbOpe = p.rangOperation;
	printf("Rang de l'operation:%d\n",nbOpe);
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
	
	while(1)
	{
		usleep(2000);
		pthread_mutex_lock(&mutex);
		printf("-------------\n");
		printf("Je suis le robot %d et mon operation est la %d\n", pos, opRobot);
		if (nbRobotOK < NBROBOT)
		{
			nbRobotOK++;
			if ((((ROBOT*)r)->produitEnCours) == TRUE)
				printf("Je m'occupe d'un produit\n");
			else
				printf("Je ne m'occupe d'aucun produit\n");
			
			if (tapis[posTapis].t == PRDT) // la case contient un produit
			{
				if (opeSuivante(tapis[posTapis].contenu.p) == FINI)
				{
						tapis[posTapis].contenu.p.operation = FINI;
						tapis[posTapis].contenu.p.rangOperation = ((ROBOT*)r)->enCours.rangOperation+1;
				}
				printf("La case contient un produit\n");
				if (((ROBOT*)r)->produitEnCours == FALSE)
				{
					printf("je ne possede pas de produit\n");
					OPERATION nextOp = opeSuivante(tapis[posTapis].contenu.p);
					if (nextOp == opRobot)
					{
						DEMANDE_ROBOT++;
						printf("Ajout de la nouvelle operation\n");
						//printOp(c.contenu.p.operation);
						//printOp(nextOp);						
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
			
				else if (tapis[posTapis].t == CMPSNT) // la case contient un composant
				{
					//printf("Je recupere un composant\n");
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
									//printf("Je crée un produit P1\n");
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
									//printf("Je crée un produit P2\n");
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
									//printf("Je crée un produit P3\n");
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
								//	printf("Je crée un produit P4\n");
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
}
