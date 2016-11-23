#include "projet.h"

Etudiant nouvEtudiant (int dossier,char prenom[], char nom[], Date naissance, int bourse, Booleen handicap, char id[], char mdp[], Booleen locataire)
{
	Etudiant e;
	e.dossier=dossier;
	strcpy(e.prenom,prenom);
	strcpy(e.nom,nom);
	e.naissance=naissance;
	e.bourse=bourse;
	e.handicap=handicap;
	strcpy(e.id,id);
	strcpy(e.mdp,mdp);
	return e;
}

Etudiant chargeEtudiant (FILE *flot)
{
	Etudiant e;
	Date d;
	char poubelle; 
	fscanf(flot, "%d%*c", &e.dossier);
	fscanf(flot, "%s%*c", &e.prenom);
	fscanf(flot, "%s%*c", &e.nom);
	fscanf(flot, "%d/%d/%d%*c", &d.jour, &d.mois, &d.annee);
	e.naissance=d;
	fscanf(flot, "%d%*c", &e.bourse);
	fscanf(flot, "%d%*c", &e.handicap);
	fscanf(flot, "%s%*c", &e.id);
	fscanf(flot, "%s%*c", &e.mdp);
	fscanf(flot, "%d%*c", &e.locataire);
	return e;
}

void affEtudiant (Etudiant *e)
{
	printf("Numéro de Dossier : %d\n", e->dossier);
	printf("Nom de l'étudiant : %s\n", e->prenom);
	printf("Prénom  : %s\n", e->nom);
	printf("Né le : %d/%d/%d\n", e->naissance.jour,e->naissance.mois,e->naissance.annee);
	printf("Echelon boursier : %d\n", e->bourse);
	printf("Handicap: %d\n", e->handicap);
	printf("Identifiant : %s\n", e->id);
	printf("Mot de passe : %s\n", e->mdp);
	printf("Locataire : %d\n", e->locataire);
	printf("\n");
}

TabEtudiant * initTabEtudiant (char *nomfic)
{
	Etudiant **tabEtudiant;
	TabEtudiant *t;
	t = (TabEtudiant *)malloc(sizeof(TabEtudiant));
	t->tabEtu = (Etudiant **)malloc(20*sizeof(Etudiant *));
	t->nbEtu=0;
	t->maxEtu=0;
	if (t->tabEtu==NULL || t==NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	chargeTabEtudiant(t->tabEtu,&(t->nbEtu),&(t->maxEtu),nomfic);
	return t;
}

void chargeTabEtudiant (Etudiant **e, int *nb, int *max,char *nomfic)
{
	FILE *flot;
	int tl,i;
	Etudiant d, **aux, *s;
	flot=fopen(nomfic,"r");
	if (flot==NULL)
	{
		printf("Erreur de lecture du fichier Etudiant\n");
		exit(1);
	}
	fscanf(flot,"%d",&tl);
	for(i=0;i<tl;i++)
	{
		d=chargeEtudiant(flot);
		if(*nb == *max)
		{
			(*max) += 10;
			aux = (Etudiant **)realloc(e,(*max)*sizeof(Etudiant *));
			if (aux == NULL)
			{
				printf("Problème realloc\n");
				fclose(flot);
				exit(1);
			}
			e=aux;
		}
		s = (Etudiant *)malloc(sizeof(Etudiant));
		if (s == NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			exit(1);
		}
		*s = d;
		e[*nb] = s;
		(*nb)++;
	}
	fclose(flot);
}

int rechEtudiant (int dossier, Etudiant **tabEtudiant, int nbEtu)
{
	int inf = 0, m, sup = nbEtu-1;
	if(nbEtu == 0)
	return -1;
	while(inf <= sup)
	{
		m = (inf + sup)/2;
		if(dossier <= tabEtudiant[m]->dossier)
		sup = m - 1;
		else
		inf = m + 1;
	}
	if(inf >= nbEtu)
	return -1;
	if(tabEtudiant[inf]->dossier != dossier)
	return -1;
	return inf;
}

Etudiant * recupEtudiant (TabEtudiant *tab, int rang)
{
	if (rang < 0 || rang >= tab->nbEtu)  
	return NULL;
	return tab->tabEtu[rang];

}

void libereTabEtudiant (TabEtudiant *tab)
{
	int i;
	for(i = 0; i < tab->nbEtu; i++)
	free(tab->tabEtu[i]);
	free(tab->tabEtu);
	free(tab);
}

void libereEtudiant (Etudiant *Etudiant)
{
	free(Etudiant);
}

void sauveTabEtudiant (TabEtudiant *tab,char *nomfic)
{
	int i;
	FILE *flot;
	flot = fopen(nomfic,"w");
	if(flot == NULL)
	{
		printf("Erreur d'écriture du fichier %s \n", nomfic);
		exit(1);
	}
	fprintf(flot,"%d\n",tab->nbEtu);
	for(i=0; i< tab->nbEtu; i++)
	{
		fprintf(flot,"%d\n%s\n%s\n%d/%d/%d\n%d\n%d\n%s\n%s\n%d\n", tab->tabEtu[i]->dossier, tab->tabEtu[i]->prenom, tab->tabEtu[i]->nom, tab->tabEtu[i]->naissance.jour, tab->tabEtu[i]->naissance.mois, tab->tabEtu[i]->naissance.annee, tab->tabEtu[i]->bourse, tab->tabEtu[i]->handicap, tab->tabEtu[i]->id, tab->tabEtu[i]->mdp, tab->tabEtu[i]->locataire);
	}
	fclose(flot);
}

void ajouterEtudiant (TabEtudiant *tab,int dossier,char prenom[], char nom[], Date naissance, int bourse, Booleen handicap, char id[], char mdp[], Booleen locataire)
{
	Etudiant e, **aux, *s;
	e=nouvEtudiant(dossier, prenom, nom, naissance, bourse, handicap, id, mdp,locataire);
	if(tab->nbEtu == tab->maxEtu)
	{
		(tab->maxEtu) += 20;
		aux = (Etudiant **)realloc(tab->tabEtu,(tab->maxEtu)*sizeof(Etudiant *));
		if (aux == NULL)
		{
			printf("Problème realloc\n");
			exit(1);
		}
		tab->tabEtu=aux;
	}
	s = (Etudiant *)malloc(sizeof(Etudiant));
	if (s == NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	*s = e;
	tab->tabEtu[tab->nbEtu] = s;
	(tab->nbEtu)++;
}

void supprEtudiant (TabEtudiant *tab, int rang)
{
	int i;
	tab->nbEtu -= 1;
	for (i=rang;i<(tab->nbEtu);i++)
		tab->tabEtu[i]=tab->tabEtu[i+1];
	
}

