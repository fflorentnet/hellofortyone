#include <composant.h>
//caca
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
	PRODUIT_TYPE type;
	OPERATION op;
};
