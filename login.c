#include "projet.h"


int main(void)
{
	/*
	int D1=-1,D2=-1;
	TabDemande *t=initTabDemande();
	ajouterDemande(t,6,4,278);
	rechDemandesEtu(4, t->tabDemande, t->nbDemande, &D1, &D2);
	int rang1=rechDemande(int numDem, Demande **tabDemande, int nbDem)
	*/
	menu(1,0,0);
	return 0;
}

//Menu Etudiant
void connexionetu(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=0;
	a=line(a,"Etudiant:",color);
	a=line(a,"Connexion",color);
	a=line(a,"Enregistrement",color);
	a=line(a,"Retour",color);
	if (erreur==0)
		lastline(2,color);
	if (erreur==1)
		notif(color,"Erreur : Prénom<30 caractères",choix);
	if (erreur==2)
		notif(color,"Erreur : Nom < 30 caractères",choix);
	if (erreur==3)
		notif(color,"Erreur : 1 < jour < 31",choix);
	if (erreur==4)
		notif(color,"Erreur : 1 < mois < 12",choix);
	if (erreur==5)
		notif(color,"Erreur : 1910 < annee < 2010",choix);
	if (erreur==6)
		notif(color,"Erreur : 0 <= Bourse <= 7",choix);
	if (erreur==7)
		notif(color,"Erreur : Handicap = 0 ou 1",choix);
	if (erreur==8)
		notif(color,"Enregistrement effectue !",choix);
	if (erreur==9)
		notif(color,"Login/Mot de passe incorrect",choix);
	printf("\t");
	scanf("%d",&choix);
	switch (choix){
	case 1:
		idetu(color,0,choix);
		break;
	case 2:
		nouvcmpt(color,choix);
		break;
	case 3:
		menu(color,0,choix);
		break;
	default:
		connexionetu(color,0,4);
	}
}

//Création d'un compte etudiant
void nouvcmpt(int color,int choix)
{
	int a,erreur=0;
	char rep[30];
	FILE *flot;
	Etudiant etu;
	clear();
	couleur(0);
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	TabEtudiant *t=initTabEtudiant("BDD/etudiants.txt");
	etu=formulaire(color,&erreur);
	ajouterEtudiant (t,((t->nbEtu)+1),etu.prenom, etu.nom, etu.naissance, etu.bourse, etu.handicap, etu.id, etu.mdp, 0);
	if (erreur==0)
	{
		sauveTabEtudiant (t,"BDD/etudiants.txt");
		connexionetu(color,8,-1);
	}
	fclose(flot);

}

//Identification étudiant
void idetu(int color,int erreur,int choix)
{
	int i;
	Booleen error=1;
	char id[30];
	char mdp[30];
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	choixligne("Login :",color);
	choixligne("Mot de passe:",color);
	lastline(2,color);
	system("tput cup 6 25");
	scanf("%s",&id);
	system("tput cup 9 33");
	system("stty -echo");
	scanf("%s",&mdp);
	system("stty echo");
	system("tput cup 14 1");
	TabEtudiant *t=initTabEtudiant("BDD/etudiants.txt");
	for (i=0;i<t->nbEtu;i++)
		if (strcmp(t->tabEtu[i]->id,id)==0 && strcmp(mdp,t->tabEtu[i]->mdp)==0)
		{
			printf("%d",t->tabEtu[i]->dossier);
			menuetu(color,0,choix,t->tabEtu[i]->dossier);
			error=0;
		}
	if (error)
		connexionetu(color,9,-1);
	
}

//Identification Administrateur
void idadmin(int color,int erreur,int choix)
{
	char id[30];
	char mdp[30];
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	choixligne("Login :",color);
	choixligne("Mot de passe:",color);
	lastline(2,color);
	system("tput cup 6 25");
	scanf("%s",&id);
	system("tput cup 9 33");
	system("stty -echo");
	scanf("%s",&mdp);
	system("stty echo");
	system("tput cup 14 1");
	if (strcmp(id,"hasbani")==0 && strcmp(mdp,"mdp")==0)
		admin(color,0,choix);
	else
		menu(color,1,-1);
	
}

//Formulaire de création d'un compte
Etudiant formulaire(int color,int *erreur)
{
	int a;
	Etudiant etu;
	char rep;
	char id;
	char mdp;
	clear();
	for (a=0;a<2;a++)
		printf("\n");
	firstline(color);
	choixligne("Nom:",color);
	choixligne("Prenom:",color);
	choixligne("Date de naissance:",color);
	choixligne("Echelon boursié:",color);
	choixligne("Handicap (non=0/oui=1)",color);
	lastline(1,color);
	normal();
	system("tput cup 4 25");
	scanf("%s",&etu.nom);
	system("tput cup 7 25");
	scanf("%s",&etu.prenom);
	system("tput cup 10 41");
	scanf("%d",&etu.naissance.jour);
	system("tput cup 10 42");
	printf("/");
	system("tput cup 10 43");
	scanf("%d",&etu.naissance.mois);
	system("tput cup 10 44");
	printf("/");
	system("tput cup 10 46");
	scanf("%d",&etu.naissance.annee);
	system("tput cup 13 41");
	scanf("%d",&etu.bourse);
	system("tput cup 16 41");
	scanf("%d",&etu.handicap);
	system("tput cup 19 1");
	if (strlen(etu.prenom)>30)
	{
		connexionetu(color,1,-1);
		*erreur=1;
	}
	else
	if (strlen(etu.nom)>30)
	{
		connexionetu(color,2,-1);
		*erreur=1;
	}
	else
	if (etu.naissance.jour>31 || etu.naissance.jour<1)
	{
		connexionetu(color,3,-1);
		*erreur=1;
	}
	else
	if (etu.naissance.mois>12 || etu.naissance.mois<1)
	{
		connexionetu(color,4,-1);
		*erreur=1;
	}	
	else
	if (etu.naissance.annee>2010 || etu.naissance.annee<1910)
	{	
		connexionetu(color,5,-1);
		*erreur=1;
	}
	else
	if (etu.bourse<0 || etu.bourse>7)
	{	
		connexionetu(color,6,-1);
		*erreur=1;
	}
	else
	if (etu.handicap!=1 && etu.handicap!=0)
	{	
		connexionetu(color,7,-1);
		*erreur=1;
	}
	else
	{
		clear();
		for (a=0;a<4;a++)
			printf("\n");
		a=0;
		firstline(color);
		a=line(a,"Création des identifiant",color);
		choixligne("Login :",color);
		choixligne("Mot de passe:",color);
		lastline(2,color);
		system("tput cup 9 25");
		scanf("%s",&etu.id);
		system("tput cup 12 33");
		system("stty -echo");
		scanf("%s",&etu.mdp);
		system("stty echo");
		system("tput cup 14 1");
	}
	return etu;
}
