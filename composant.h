#ifndef COMPOSANT_H
#define COMPOSANT_H

typedef enum {
	TRUE,
	FALSE
} boolean;


// Enum Composant_Type : liste les types de composants
typedef enum {
	C1,
	C2,
	C3,
	C4
} COMPOSANT_TYPE;

// Enum Operation : liste les etats d'un produit
// et correspond a l'operation qu'effectue un robot
typedef enum {
	INIT,
	OP1,
	OP2,
	OP3,
	OP4,
	OP5,
	OP6,
	FINI
} OPERATION;

// Enum Produit_Type : liste les produits
typedef enum {
	P1,
	P2,
	P3,
	P4
} PRODUIT_TYPE;

// Struct Composant : contient le type du composant
typedef struct COMPOSANT {
	COMPOSANT_TYPE type;
} COMPOSANT;

// Struct Produit : contient le type du produit,
// sa derniere operation ainsi que l'operation a venir
typedef struct PRODUIT {
	PRODUIT_TYPE type;
	OPERATION operation;
	int rangOperation;
} PRODUIT;

// Enum Case_Type : contient l'etat de la case
typedef enum {
	PRDT,
	CMPSNT,
	VIDE
} CASE_TYPE;

// Struct Case : contient l'etat de la case,
// ainsi que le produit OU le composant sur la case
typedef struct CASE
{
	union{
		COMPOSANT c;
		PRODUIT p;
	}contenu;
	CASE_TYPE t;
} CASE;

// Struct Robot : liste les opérations des robots
typedef struct ROBOT {
	OPERATION op;
	int pos;
	int composant;
	PRODUIT enCours;
	boolean produitEnCours;
} ROBOT;

#endif
