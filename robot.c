#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "composant.h"

void printOp(OPERATION op)
{
	switch(op)
	{
	case 1: printf("operation 1\n"); break;
	case 2: printf("operation 2\n"); break;
	case 3: printf("operation 3\n"); break;
	case 4: printf("operation 4\n"); break;
	case 5: printf("operation 5\n"); break;
	case 6: printf("operation 6\n"); break;
	case FINI: printf("operation fini\n"); break;
	default: break;
	}
}

OPERATION opeSuivante(PRODUIT* p)
{
	OPERATION op = FINI;

	if (p->listeOperation != NULL)
	{
		int nbOpe = (sizeof(p->listeOperation)/sizeof(OPERATION));
		if (p->listeOperation[nbOpe-1] != FINI)
		{
			if (p->type == P1)
			{
				op = SEQUENCE_PRODUIT_UN[nbOpe];
				printf("un\n");
			}
			else if (p->type == P2)
			{
				op = SEQUENCE_PRODUIT_DEUX[nbOpe];
				printf("deux\n");
			}
			else if (p->type == P3)
			{
				op = SEQUENCE_PRODUIT_TROIS[nbOpe];
				printf("trois\n");
			}
			else if (p->type == P4)
			{
				op = SEQUENCE_PRODUIT_QUATRE[nbOpe];
				printf("quatre\n");
			}
		}
		else
		{
			printf("Le produit est fini\n");
		}
		printOp(op);
	}
	return op;
}

void addOpe(PRODUIT* p, OPERATION op)
{
	p->listeOperation = (OPERATION*) realloc(p->listeOperation,sizeof(OPERATION)*( sizeof(p->listeOperation)+1 ) );
	int nbOpe = (sizeof(p->listeOperation)/sizeof(OPERATION));
	p->listeOperation[nbOpe] = op;

}
void* cycleRobot(void* r)
{
	int pos = ((ROBOT*)r)->op;
	int posTapis = 2+2*pos+1;
	CASE c;
	int b = 0;
	while(b == 0)
	{
		usleep(2000);
		pthread_mutex_lock(&mutex);


		if (nbRobotOK < NBROBOT)
		{
			nbRobotOK++;
			c = tapis[posTapis];
			//printf("Recuperation de la case.\n");

			if (c.t == VIDE) // la case est vide
			{
				// printf("Case vide\n");
				if ((((ROBOT*)r)->produitEnCours) == TRUE)
				{			
					c.t = PRDT;
					c.contenu.p = ((ROBOT*)r)->enCours;
					tapis[posTapis]=c;
				}
			}

			else if (c.t == PRDT) // la case contient un produit
			{

				if (((ROBOT*)r)->produitEnCours == FALSE)
				{
					//printf("La case contient un produit\n");
					OPERATION nextOp = opeSuivante(&(c.contenu.p));

					if (nextOp == ((ROBOT*)r)->op)
					{
						printf("Ajout de la nouvelle operation\n");
						addOpe(&(c.contenu.p), nextOp);
						((ROBOT*)r)->enCours = c.contenu.p;
						c.t = VIDE;
						tapis[posTapis] = c;

					}
				}
			}
			else if (c.t == CMPSNT) // la case contient un composant
			{
				printf("Je recupere un composant\n");
				switch( ((ROBOT*)r)->op)
				{
				case OP1: 
					if (c.contenu.c.type == C1)
					{
						((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
						c.t = VIDE;
						tapis[posTapis] = c;
					}
					break;
				case OP2: 
					if (c.contenu.c.type == C2)
					{
						((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
						c.t = VIDE;
						tapis[posTapis] = c;
					}
					break;
				case OP3:
					if (c.contenu.c.type == C3)
					{
						((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
						c.t = VIDE;
						tapis[posTapis] = c;
					}
					break;
				case OP4:
					if (c.contenu.c.type == C4)
					{
						((ROBOT*)r)->composant = ((ROBOT*)r)->composant+1;
						c.t = VIDE;
						tapis[posTapis] = c;
					}
					break;
				default: break;
				}
			}
			if (((ROBOT*)r)->produitEnCours == FALSE)
			{
				PRODUIT prodTemp;


				switch( ((ROBOT*)r)->op)
				{
				case OP1: 
					if (((ROBOT*)r)->composant >= NB_COMPOSANT_UN)
					{
						printf("Je crée un produit P1\n");
						prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
						if (prodTemp.listeOperation == NULL)
							printf("Erreur malloc P1\n");
						prodTemp.listeOperation[0] = INIT;
						prodTemp.type = P1;
						((ROBOT*)r)->enCours = prodTemp;
						((ROBOT*)r)->produitEnCours = TRUE;
					}
					break;
				case OP2: 
					if (((ROBOT*)r)->composant >= NB_COMPOSANT_DEUX)
					{
						printf("Je crée un produit P2\n");
						prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
						if (prodTemp.listeOperation == NULL)
							printf("Erreur malloc P2\n");
						prodTemp.listeOperation[0] = INIT;
						prodTemp.type = P2;
						((ROBOT*)r)->enCours = prodTemp;
						((ROBOT*)r)->produitEnCours = TRUE;
					}
					break;
				case OP3:
					if (((ROBOT*)r)->composant >= NB_COMPOSANT_TROIS)
					{
						printf("Je crée un produit P3\n");
						prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
						if (prodTemp.listeOperation == NULL)
							printf("Erreur malloc P3\n");
						prodTemp.listeOperation[0] = INIT;
						prodTemp.type = P3;
						((ROBOT*)r)->enCours = prodTemp;
						((ROBOT*)r)->produitEnCours = TRUE;
					}
					break;
				case OP4:
					if (((ROBOT*)r)->composant >= NB_COMPOSANT_QUATRE)
					{
						printf("Je crée un produit P4\n");
						prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
						if (prodTemp.listeOperation == NULL)
							printf("Erreur malloc P4\n");
						prodTemp.listeOperation[0] = INIT;
						prodTemp.type = P4;
						((ROBOT*)r)->enCours = prodTemp;
						((ROBOT*)r)->produitEnCours = TRUE;
					}
					break;
				default: break;
				}


			}
		}
		pthread_mutex_unlock(&mutex);
	}
}
