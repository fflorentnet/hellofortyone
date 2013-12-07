#ifndef PRODUIT_H
#define PRODUIT_H



enum CASE_TYPE{
	PRODUIT,
	COMPOSANT
};
enum COMPOSANT_TYPE {
	C1,
	C2,
	C3,
	C4
};
enum OPERATION {
	INIT,
	OP1,
	OP2,
	OP3,
	OP4,
	OP5,
	OP6,
	FINI
};
enum PRODUIT_TYPE {
	P1,
	P2,
	P3,
	P4
};
struct COMPOSANT {
	COMPOSANT_TYPE type;
};
struct PRODUIT {
	PRODUIT_TYPE type; // Indique le type de produit en création
	OPERATION op; // Dernière opération effectuée sur le produit
};
struct case
{
	union{
		COMPOSANT c;
		PRODUIT d;
	}contenu;
	CASE_TYPE t;
};
#endif
