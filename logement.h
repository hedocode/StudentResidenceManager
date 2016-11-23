#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Enumérations
typedef enum{
	OUI,
	NON
} Booleen;

typedef enum{
	TRAVAUX,
	OCCUPEE,
	LIBRE
} Statut;

typedef enum{
	CHAMBRE,
	STUDIO,
	T1,
	T2
} Type;

//Structures
typedef struct{
	int jour;
	int mois;
	int annee;
}Date;

typedef struct{
	int numCite;
	int numLogement;
	int dossier;
	Type type;
	Statut etat;
	Booleen handicap;	
} Logement;

typedef struct{
	int nbLogement;
	int maxLogement;
	Logement ** tabLogement;
} TabLogement;

//MARCHE
Logement 	nouvLogement		(int numCite, int numLogement, int dossier, Type type, Statut etat, Booleen handicap);
Logement 	chargeLogement 		(FILE *flot);
void		affLogement 		(Logement *l);
void		chargeTabLogement	(Logement **tabLogement, int *nbLogement, int *maxLogement, char *nomfic);
TabLogement * 	initTabLogement 	(char *nomfic);
int 		rechLogement		(int numLogement, Logement **tabLogement, int nbLogement);
Logement * 	recupLogement 		(TabLogement *tab, int rang);
void 		libereTabLogement 	(TabLogement *tab);
int 		rechLogementEtu 	(int dossier, Logement **tabLogement,int nb);
void 		sauveTabLogement	(TabLogement *tab, char *nomfic);
void 		ajouterLogement 	(TabLogement *tab, int numCite, int numLogement, int dossier, Type type, Statut etat, Booleen handicap);
void 		affLogement 		(Logement *l);
void		supprLogement 		(TabLogement *tab, int rang);
void		triLogementFusion	(Logement **R, int n, Logement **S, int m, Logement **T, int tri);
void 		triLogementCopier	(Logement **tab, int i, int j, Logement **R);
void 		triLogement		(Logement **tab, int nb, int tri);
//MARCHE PAS


//A FAIRE



 

