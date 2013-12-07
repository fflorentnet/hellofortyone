#ifndef COMPOSANT_H
#define COMPOSANT_H

typedef enum {
	C1,
	C2,
	C3,
	C4
} COMPOSANT_TYPE;

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

typedef enum {
	P1,
	P2,
	P3,
	P4
} PRODUIT_TYPE;

typedef struct {
	COMPOSANT_TYPE type;
} COMPOSANT;

typedef struct {
	PRODUIT_TYPE type;
	OPERATION op;
	OPERATION op_next;
} PRODUIT;
typedef enum {
	PRDT,
	CMPSNT
} CASE_TYPE;

typedef struct
{
	union{
		COMPOSANT c;
		PRODUIT d;
	}contenu;
	CASE_TYPE t;
} CASE;

typedef struct {
	OPERATION op;
} ROBOT;
#endif
