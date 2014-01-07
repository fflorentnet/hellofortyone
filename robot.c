#include <stdio.h>
#include <stdlib.h>

#include "robot.h"
#include "composant.h"

OPERATION opeSuivante(PRODUIT* p)
{
	OPERATION op;
	int nbOpe = (sizeof(p->listeOperation)/sizeof(OPERATION));

	if (p->type == P1)
	{
		if (p->listeOperation[nbOpe+1] != FINI)
		{
			op = SEQUENCE_PRODUIT_UN[nbOpe];
		}
	}
	else if (p->type == P2)
	{
		if (p->listeOperation[nbOpe+1] != FINI)
		{
			op = SEQUENCE_PRODUIT_DEUX[nbOpe];
		}		
	}
	else if (p->type == P3)
	{
		if (p->listeOperation[nbOpe+1] != FINI)
		{
			op = SEQUENCE_PRODUIT_TROIS[nbOpe];
		}		
	}
	else
	{
		if (p->listeOperation[nbOpe+1] != FINI)
		{
			op = SEQUENCE_PRODUIT_QUATRE[nbOpe];
		}		
	}
	return op;
}

void addOpe(PRODUIT* p, OPERATION op)
{
	p->listeOperation = (OPERATION*)malloc(sizeof(OPERATION)*(sizeof(p->listeOperation)+1));
	int nbOpe = sizeof(p->listeOperation)/sizeof(OPERATION)-1;
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
      usleep(200000);
      pthread_mutex_lock(&mutex);
		

      if (nbRobotOK < NBROBOT)
	{
	  nbRobotOK++;
	  c = tapis[posTapis];
	  //printf("Recuperation de la case.\n");
	   
	  if (c.t == VIDE) // la case est vide
	    {
		if ((((ROBOT*)r)->enCours) != NULL)
		{
			c.t = PRDT;
			c.contenu.p = *(((ROBOT*)r)->enCours);
			tapis[posTapis]=c;
		}
	    }
	
	  else if (c.t == PRDT) // la case contient un produit
	    {
	    	if (((ROBOT*)r)->enCours == NULL)
	    	{
	    		printf("La case contient un produit\n");
				OPERATION nextOp = opeSuivante(&(c.contenu.p));

				if (nextOp == ((ROBOT*)r)->op)
				{
						((ROBOT*)r)->enCours = &(c.contenu.p);
						addOpe(&(c.contenu.p), nextOp);
						c.t = VIDE;
						tapis[posTapis] = c;
				}
			}
	    }
	  else if (c.t == CMPSNT) // la case contient un composant
	    {
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
	    if (((ROBOT*)r)->enCours == NULL)
	    {
	    	PRODUIT prodTemp;

			
	      switch( ((ROBOT*)r)->op)
			{
			case OP1: 
				 if (((ROBOT*)r)->composant >= NB_COMPOSANT_UN)
				 {
		 	    	printf("Je crée un produit\n");
	    			prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
					(prodTemp.listeOperation)[0] = INIT;
				 	prodTemp.type = P1;
				 	((ROBOT*)r)->enCours = &prodTemp;
				 }
			  break;
			case OP2: 
			  if (((ROBOT*)r)->composant >= NB_COMPOSANT_DEUX)
				 {
				 	 printf("Je crée un produit\n");
					prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
					(prodTemp.listeOperation)[0] = INIT;
					prodTemp.type = P2;
				 	((ROBOT*)r)->enCours = &prodTemp;
				 }
			  break;
			case OP3:
			  if (((ROBOT*)r)->composant >= NB_COMPOSANT_TROIS)
				 {
		 	    	printf("Je crée un produit\n");
    				prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
					(prodTemp.listeOperation)[0] = INIT;
				 	prodTemp.type = P3;
				 	((ROBOT*)r)->enCours = &prodTemp;
				 }
			  break;
			case OP4:
			 if (((ROBOT*)r)->composant >= NB_COMPOSANT_QUATRE)
				 {
		 	    	printf("Je crée un produit\n");
	    			prodTemp.listeOperation = (OPERATION*)malloc(1*sizeof(OPERATION));
					(prodTemp.listeOperation)[0] = INIT;
				 	prodTemp.type = P4;
				 	((ROBOT*)r)->enCours = &prodTemp;
				 }
			  break;
			default: break;
			}


		}
	}
      pthread_mutex_unlock(&mutex);
    }
}
