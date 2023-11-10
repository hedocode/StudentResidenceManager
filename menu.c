#include "projet.h"

//Affiche le menu principal
void menu(int color,int erreur,int choix)
{
	int a;
	clear();
	couleur(0);
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=0;
	a=line(a,"Menu Principal",color);
	a=line(a,"Etudiant",color);
	a=line(a,"Administrateurs",color);
	a=line(a,"Personnalisation",color);
	a=line(a,"Quitter",color);
	switch (erreur){
	case 0:
		lastline(2,color);
		break;
	case 1:
		notif(color,"Login/Mot de passe incorrect",choix);
		break;
	default:
		notif(color,"est un choix incorrect.",choix);
	}
	printf("    ");
	scanf("%d%*c",&choix);
	switch (choix){
	case 1:
		connexionetu(color,0,choix);
		break;
	case 2:
		idadmin(color,0,choix);
		break;
	case 3:
		color=perso(color,0,choix);
		break;
	case 4:
		printf("fin");
		break;
	default:
		menu(color,2,choix);
	}
	couleur(0);
	clear();
	printf("Au revoir !\n");
}

//Affiche le menu administrateur
void admin(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=1;
	lignevide(1,color);
	a=line(a,"Demandes",color);
	a=line(a,"Etudiants",color);
	a=line(a,"Logements",color);
	a=line(a,"Sauvegarde",color);
	a=line(a,"Quitter",color);
	if (erreur==0)
		lastline(2,color);
	else
		notif(color,"est un choix incorrect.",choix);
	printf("    ");
	scanf("%d%*c",&choix);
	switch (choix){
	case 1:
		demande(color,0,choix);
		break;
	case 2:
		demande(color,0,choix);
		break;
	case 3:
		chambres(color,0,choix);;
		break;
	case 4:
		Sauvegarde(color,0,choix);
		break;
	case 5:
		menu(color,0,choix);
		break;
	default:
		admin(color,1,choix);
	}		
}

void menuetu (int color, int erreur, int choix, int dossier)
{
	int rang, nsupp;
	TabDemande *t=initTabDemande();
	int Dem1=-1,Dem2=-1;
	int a,i;
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=1;
	lignevide(1,color);
	a=line(a,"Vos demandes",color);
	a=line(a,"Faire une demande",color);
	a=line(a,"Supprimer une demande",color);
	a=line(a,"Quitter",color);
	if (erreur==0)
		lastline(2,color);
	else
	if (erreur==1)
		notif(color,"Vous avez dejà 2 demandes !",-1);
	else
		notif(color,"est un choix incorrect.",choix);
	printf("    ");
	scanf("%d%*c",&choix);
	switch (choix){
	case 1:
		rechDemandesEtu (dossier, t->tabDemande, t->nbDemande, &Dem1, &Dem2);
		affDemEtu(color, Dem1, Dem2, dossier);
		pause(color,dossier);
		break;
	case 2:
		creationdemande(color,0,choix,dossier);
		break;
	case 3:
		rechDemandesEtu (dossier, t->tabDemande, t->nbDemande, &Dem1, &Dem2);
		affDemEtu(color,Dem1, Dem2, dossier);
		nsupp=choixdemsuppr(color);
		if (nsupp!=1 && nsupp!=2)
			menuetu(color,-1,nsupp,dossier);
		else
			if (nsupp==1)
			{			
				supprDemande (t, Dem1);
				for(i=0;i<t->nbDemande;i++)
					if(t->tabDemande[i]->numDem > i)
						t->tabDemande[i]->numDem=i;
				sauveTabDemande (t, "BDD/demandes.txt");
			}			
			else
			{
				supprDemande (t, Dem2);
				for(i=0;i<t->nbDemande;i++)
					if(t->tabDemande[i]->numDem > i)
						t->tabDemande[i]->numDem=i;
				sauveTabDemande (t, "BDD/demandes.txt");
			}
		menuetu(color,0,nsupp,dossier);
		break;
	case 4:
		menu(color,0,choix);
		break;
	default:
		admin(color,1,choix);
	}		
}

void entreligne (int color)
{
	ombre();
	printf("    ");
	bold();
	initcolor(color);
}

void affDemEtu (int color, int Dem1, int Dem2, int dossier)
{
	TabDemande *t=initTabDemande();
	int a;
	int rang1,rang2;
	Demande *d1=recupDemande(t,Dem1);
	Demande *d2=recupDemande(t,Dem2);
	clear();
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	lignevide(1,color);
	printf("    ");
	bold();
	initcolor(color);
	if(Dem1==-1)
	{
		printf("    Numéro de Demande 1: VIDE            ");
		entreligne(color);
		printf("    Numéro cité demandée: VIDE            ");
	}
	else
	{
		printf("    Numéro de Demande 1: %.5d            ", t->tabDemande[Dem1]->numDem);
		entreligne(color);
		printf("    Numéro cité demandée: %.5d            ", d1->numCite);
	}
	ombre();
	lignevide(1,color);
	printf("    ");
	initcolor(color);
	bold();
	if(Dem2==-1)
	{
		printf("    Numéro de Demande 2: VIDE            ");
		entreligne(color);
		printf("    Numéro cité demandée: VIDE            ");
	}
	else
	{
		printf("    Numéro de Demande 2: %.5d            ", t->tabDemande[Dem2]->numDem);
		entreligne(color);
		printf("    Numéro cité demandée: %.5d            ", d2->numCite);
	}
	ombre();	
	
}
void pause(int color, int dossier)
{
	lignevide(1,color);
	printf("    ");
	initcolor(color);
	bold();
	printf("    Appuyer sur entrée pour revenir au menu.    ");
	ombre();
	lastline(2,color);
	getchar();
	menuetu(color,0,0,dossier);
}

int choixdemsuppr(int color)
{
	int c;
	lignevide(1,color);
	printf("    ");
	initcolor(color);
	bold();
	printf("    Numéro de la demande à supprimée :        ");
	ombre();
	lastline(2,color);
	scanf("%d",&c);
	
}

//Menu des locataires
void creationdemande(int color, int erreur, int  choix, int dossier)
{
	int Dem1=-1,Dem2=-1,a,numCite;
	TabDemande *t=initTabDemande();
	rechDemandesEtu (dossier, t->tabDemande, t->nbDemande, &Dem1, &Dem2);
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=1;
	choixligne("N° de Cite demandée :",color);
	lastline(2,color);
	printf("    ");
	system("tput cup 6 37");
	scanf("%d%*c",&numCite);
	if (Dem1==-1 || Dem2==-1)
	{			
		ajouterDemande (t,t->nbDemande,dossier, numCite);
		sauveTabDemande (t, "BDD/demandes.txt");
		menuetu(color,0,choix,dossier);
	}	
	else
		menuetu(color,1,choix,dossier);
}

//Menu des chambres
void chambres(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=1;
	a=line(a,"Retour",color);
	lastline(2,color);
	printf("    ");
	scanf("%d%*c",&choix);
	if (choix==1)
		admin(color,0,choix);
	else
		chambres(color,1,choix);
}

void Sauvegarde(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");	
	firstline(color);
	a=1;
	a=line(a,"Retour",color);
	lastline(2,color);
	printf("    ");
	scanf("%d%*c",&choix);
	if (choix==1)
		admin(color,0,choix);
	else
		Sauvegarde(color,0,1);
}

//Menu des demandes
void demande(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	a=0;
	a=line(a,"Etudiant :",color);
	a=line(a,"Retourner au menu",color);
	lastline(2,color);
	printf("    ");
	scanf("%d%*c",&choix);
	if (choix==1)
		admin(color,0,choix);
	else
		demande(color,1,choix);
}

//Menu de personnalisations
int perso(int color,int erreur,int choix)
{
	int a;
	clear();
	for (a=0;a<4;a++)
		printf("\n");
	firstline(color);
	a=0;
	a=line(a,"Personnalisation :",color);
	a=line(a,"Bleu",color);
	a=line(a,"Vert",color);
	a=line(a,"Noir",color);
	a=line(a,"Jaune",color);
	a=line(a,"Retour au menu",color);
	if (erreur==0)
		lastline(2,color);
	else
		notif(color,"est un choix incorrect.",choix);
	printf("    ");
	scanf("%d%*c",&choix);
	if (choix >=1 && choix<=5)
	{
		if (choix==1)
		{
			color=1;
			perso(color,0,choix);
		}
		if (choix==2)
		{
			color=2;
			perso(color,0,choix);
		}
		if (choix==3)
		{
			color=3;
			perso(color,0,choix);
		}
		if (choix==4)
		{
			color=4;
			perso(color,0,choix);
		}
		if (choix==5)
		{
			menu(color,0,choix);
		}
	}
	else
		perso(color,1,choix);
}

//Initialise le menu avec la couleur choisie
void initcolor(int color)
{
	if (color==1)blue();
	if (color==2)green();
	if (color==3)dark();
	if (color==4)yellow();
}

//Créé un espace vide de couleur noire et \n
void ombre(void)
{
	shadow();
	printf(" ");
	couleur(0);
	printf("\n");
}

//Créé une ligne vide de couleur choisie SANS ombre
void firstline(int color)
{
	printf("    ");
	initcolor(color);
	printf("                                       ");
	couleur(0);
	printf("\n");
	
}

//Créé une ligne vide de couleur choisie AVEC ombre
void lignevide(int nombre,int color)
{
	int i;
	for (i=0;i<nombre;i++)
	{
		printf("    ");
		initcolor(color);
		printf("                                       ");
		ombre();
	}
}

//Créé une ligne avec un message choisi
int line(int a, char chaine[],int color)
{
	int taille=strlen(chaine);
	lignevide(1,color);
	printf("    ");
	bold();
	initcolor(color);
	int windowSize = 32;
	if (a>0)
	{
		printf("    %d) %s",a,chaine);
	}
	else
	{
		printf("    %s",chaine);
		windowSize += 3;
	}

	for (int i = 0; i < windowSize - taille; i ++) {
		printf(" ");
	}

	shadow();
	printf(" ");
	couleur(0);
	printf("\n");
	lignevide(1,color);
	normal();
	a++;
	return a;
}

//Fonction pour créer une ligne avec un message et une réponse
void choixligne(char chaine[],int color)
{
	int windowSize = 32;
	int taille=strlen(chaine);
	lignevide(1,color);
	printf("    ");
	bold();
	initcolor(color);
	printf("    %s    ",chaine);
	couleur(0);
	printf("        ");
	initcolor(color);

	for (int i = 0; i < windowSize - taille - 9; i ++) {
		printf(" ");
	}

	shadow();
	printf(" ");
	couleur(0);
	printf("\n");
	lignevide(1,color);
	normal();
}

//Fonction pour créer une ligne vide de couleur choisie sans ombre
void lastline(int nombre, int color)
{
	int i;
	for (i=0;i<nombre;i++)
	{
		lignevide(1,color);
	}
	printf("     ");
	shadow();
	printf("                                       ");
	couleur(0);
	printf("\n");
	
}

//Affiche le statut
void affStatut(Statut s)
{
	switch(s){
		case 0:
		printf("En travaux");
		break;
		case 1:
		printf("Occupée");
		break;
		case 2:
		printf("Libre");
		break;
	}
}

//Affiche la catégorie
void affType(Type t)
{
	switch(t){
		case 0:
		printf("Chambre");
		break;
		case 1:
		printf("Studio");
		break;
		case 2:
		printf("T1");
		break;
		case 3:
		printf("T2");
		break;
	}
}

//Affiche un booléen
void affBool(Booleen b)
{
	switch(b){
		case 0:
		printf("Non");
		break;
		case 1:
		printf("Oui");
		break;
	}
}

//Créé une alerte rouge sous le menu
void notif(int color,char message[],int choix)
{
	int taille=strlen(message);
	lignevide(1,color);
	printf("     ");
	shadow();
	printf("            ");
	red();
	printf("                ");
	ombre();
	couleur(0);
	printf("                ");
	red();
	if (choix!=-1)
	printf("  %d %s",choix,message);
	else
	printf("  %s",message);
	if (taille>21)
		printf("    ");
	else
	{
		if (taille>13)
			printf("        ");
		else
			printf("        ");
	}
	ombre();
	couleur(0);
	printf("                ");
	red();
	printf("                ");
	ombre();
	printf("                 ");
	shadow();
	printf("                 ");
	couleur(0);

}
