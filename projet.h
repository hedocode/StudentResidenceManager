#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
} Date;

typedef struct{
	int numero;
	char rue[30];
	int codePostal;
	char ville[30];
} Adresse;

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
	int nbDemande;
} Etudiant;


typedef struct{
	int nbEtu;
	int maxEtu;
	Etudiant ** tabEtu;
}TabEtudiant;

typedef struct{
	int numCite;
	Adresse adresse;
} Cite;

typedef struct{
	int nbCite;
	int maxCite;
	Cite **tabCite;
} TabCite;

typedef struct{
	int numCite;
	int numLogement;
	int dossier;
	Type type;
	Statut etat;
	Booleen Handicap;	
} Logement;

typedef struct{
	int numDem;
	int dossier;
	int numCite;
} Demande;

typedef struct{
	int nbDemande;
	int maxDemande;
	Demande ** tabDemande;
} TabDemande;


//Fonctions de gestion d'affichage du menu
void lignevide(int nombre,int color);
void lastline(int nombre,int color);
int line(int a, char chaine[],int color);
void firstline(int color);
void ombre(void);

//Fonctions d'affichage des parties du menu
void menu(int color,int erreur,int choix);
void demande(int color,int erreur,int choix);
int perso(int color,int erreur,int choix);
void adminmenu(int color,int erreur,int choix);
void chambres(int color,int erreur,int choix);
void creationdemande(int color, int erreur, int  choix, int dossier);
void Sauvegarde(int color,int erreur,int choix);
void notif(int color,char message[],int choix);
void initcolor(int color);
void choixligne(char chaine[],int color);
void affStatut(Statut s);
void affType(Type t);
void affBool(Booleen b);
void menuetu (int color, int erreur, int choix, int dossier);
void affDemEtu (int color, int Dem1, int Dem2, int dossier);
void entreligne (int color);
void pause(int color,int dossier);
int choixdemsuppr(int color);

//Fonctions de connexion
void connexionetu(int color,int erreur,int choix);
void connexionadmin(int color,int erreur,int choix);
void nouvcmpt(int color,int choix);
void idadmin(int color,int erreur,int choix);
Etudiant formulaire(int color,int *erreur);
void idetu(int color,int erreur,int choix);
void creationid(int color, char *id, char *mdp);

//Fonctions de chargement
void demarrage(void);


//Fonctions Etudiant
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

//Fonctions demandes

//MARCHE
Demande 	nouvDemande		(int numDem, int dossier, int numCite);
Demande		chargeDemande		(FILE *flot);
void 		affDemande		(Demande *d);
TabDemande * 	initTabDemande		(void);
void 		chargeTabDemande	(Demande **d, int *nb, int *max,char *nomfic);
int		rechDemande		(int numDem, Demande **tabDemande, int nbDem);
Demande * 	recupDemande		(TabDemande *tab, int rang);
void 		libereTabDemande	(TabDemande *tab);
void		libereDemande		(Demande *demande);
void		sauveTabDemande		(TabDemande *tab,char *nomfic);
void		ajouterDemande 		(TabDemande *tab,int numDem,int dossier,int numCite);
void 		ListeBackupsDem 	(void);
void		supprDemande		(TabDemande *tab, int rang);
void		rechDemandesEtu		(int dossier, Demande **tabDemande,int nb, int *D1, int *D2);
void	affDemCite		(Demande ** tabDemande, int numCite,int nb);

//A FAIRE
void		sauvegardes		(TabDemande *tab);
void		restaurerBackupDem	(TabDemande *tab,char Backup);	

//AUTRES
void		remiseAZero		(void);//TOTALE, SUPPRESION DE TOUT LES FICHIER DE DONNEES


