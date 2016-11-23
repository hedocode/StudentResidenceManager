#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Enumérations
typedef enum{
	OUI,
	NON
} Booleen;

typedef enum{
	CHAMBRE,
	STUDIO,
	T1,
	T2
} Type;

typedef enum{
	TRAVAUX,
	OCCUPEE,
	LIBRE
} Statut;


//Structures
typedef struct{
	int jour;
	int mois;
	int annee;
} Date;

typedef struct{
	int numero;
	char rue[30];
	int codePostal;
	char ville[40];
} Adresse;


typedef struct{
	int numCite;
	Adresse adresse;
} Cite;


typedef struct{
	int dossier;
	char prenom[30];
	char nom[30];
	Date naissance;
	int bourse;
	Booleen handicap;
	char id[30];
	char mdp[30];
	Booleen locataire;
} Etudiant;


typedef struct{
	int nbEtu;
	int maxEtu;
	Etudiant ** tabEtu;
}TabEtudiant;

typedef struct{
	Cite cite;
	int numLogement;
	Type type;
	Statut etat;
	Booleen Handicap;	
} Logement;

//MARCHE
TabEtudiant * 	initTabEtudiant		(char *nomfic);
Etudiant 	nouvEtudiant		(int dossier,char prenom[], char nom[], Date naissance, int bourse, Booleen handicap, char id[], char mdp[], Booleen locataire);
void 		ajouterEtudiant 	(TabEtudiant *tab,int dossier,char prenom[], char nom[], Date naissance, int bourse, Booleen handicap, char id[], char mdp[], Booleen locataire);
Etudiant	chargeEtudiant		(FILE *flot);
void 		chargeTabEtudiant	(Etudiant **e, int *nb, int *max,char *nomfic);
void 		affEtudiant 		(Etudiant *e);
int		rechEtudiant		(int numDem, Etudiant **tabEtudiant, int nbDem);
Etudiant * 	recupEtudiant		(TabEtudiant *tab, int rang);
void 		libereTabEtudiant	(TabEtudiant *tab);
void		libereEtudiant		(Etudiant *Etudiant);
void 		sauveTabEtudiant 	(TabEtudiant *tab,char *nomfic);

//MARCHE PAS
void		supprEtudiant		(TabEtudiant *tab, int rang);
void		affEtuCite		(Etudiant ** tabEtudiant, int numCite,int nb);

//AUTRES
void		remiseAZero		(void);//TOTALE, SUPPRESION DE TOUT LES FICHIER DE DONNEES
