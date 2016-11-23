#include "projet.h"

//Initialise les tableau de demandes
TabDemande * initTabDemande(void)
{
	int nbDemande = 0, maxDemande = 0;
	Demande **tabDemande;
	TabDemande *t;
	char nomfic[50]="BDD/demandes.txt";
	t = (TabDemande *)malloc(sizeof(TabDemande));
	tabDemande = (Demande **)malloc(20*sizeof(Demande *));
	if (tabDemande==NULL || t==NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	chargeTabDemande(tabDemande,&nbDemande,&maxDemande,nomfic);
	t->nbDemande=nbDemande;
	t->maxDemande=maxDemande;
	t->tabDemande=tabDemande;
	return t;
}

//Charge les tableaux a partir du fichier demande.txt
void chargeTabDemande(Demande **tabDemande,int *nbDemande,int *maxDemande,char *nomfic)
{
	FILE *flot;
	Demande d, **aux, *s;
	flot=fopen(nomfic,"r");
	if (flot==NULL)
	{
		printf("Erreur de lecture du fichier demande");
		exit(1);
	}
	d=chargeDemande(flot);
	while(!feof(flot))
	{
		if(*nbDemande == *maxDemande)
		{
			(*maxDemande) += 10;
			aux = (Demande **)realloc(tabDemande,(*maxDemande)*sizeof(Demande *));
			if (aux == NULL)
			{
				printf("Problème realloc\n");
				fclose(flot);
				exit(1);
			}
		}
		s = (Demande *)malloc(sizeof(Demande));
		if (s == NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			exit(1);
		}
		*s = d;
		tabDemande[*nbDemande] = s;
		(*nbDemande)++;
		d=chargeDemande(flot);	
	}
	fclose(flot);
}

//Créé une nouvelle demande à partie d'info données
Demande nouvDemande(int numDem, int dossier, int numCite)
{
	Demande d;
	d.numDem=numDem;
	d.dossier=dossier;
	d.numCite=numCite;
	return d;
}

//Charge une demande depuis le flot
Demande chargeDemande (FILE *flot)
{
	Demande d;
	fscanf(flot, "%d%*c", &d.numDem);
	fscanf(flot, "%d%*c", &d.dossier);
	fscanf(flot, "%d%*c", &d.numCite);
	return d;
}

//Recherche une demande et retourne son rang
int rechDemande(int numDem, Demande **tabDemande, int nbDem)
{
	int inf = 0, m, sup = nbDem-1;
	if(nbDem == 0)
	return -1;
	while(inf <= sup)
	{
		m = (inf + sup)/2;
		if(numDem <= tabDemande[m]->numDem)
			sup = m - 1;
		else
			inf = m + 1;
	}
	return inf;
}

//Récupére une demande au rang n d'un tableau de demande
Demande * recupDemande	(TabDemande *tab, int rang)
{
	if (rang < 0 || rang >= tab->nbDemande)  
	return NULL;
	return tab->tabDemande[rang];

}

//Tout est dans le titre
void libereTabDemande(TabDemande *tab)
{
	int i;
	for(i = 0; i < tab->nbDemande; i++)
	free(tab->tabDemande[i]);
	free(tab->tabDemande);
	free(tab);
}

//idem
void libereDemande (Demande *demande)
{
	free(demande);
}

//Affiche une demande
void affDemande (Demande *d)
{
	if (d == NULL) 
		printf("\nErreur : Accès à une case incorrecte du tableau.\n");
	else
	{
		printf("Numéro de Demande : %d\n", d->numDem);
		printf("Numéro de Dossier : %d\n", d->dossier);
		printf("Numéro du Batiment : %d\n ", d->numCite);
		printf("\n");
	}
}

//Sauvegarde les changements de Demandes dans un fichier "nomfic"
void sauveTabDemande (TabDemande *tab, char *nomfic)
{
	int i;
	FILE *flot;
	flot = fopen(nomfic,"w");
	if(flot == NULL)
	{
		printf("Erreur d'écriture du fichier %s \n", nomfic);
		exit(1);
	}
	for(i=0; i< tab->nbDemande; i++)
	{
		fprintf(flot,"%.5d %.5d %.5d\n", tab->tabDemande[i]->numDem,tab->tabDemande[i]->dossier, tab->tabDemande[i]->numCite);
	}
	fclose(flot);
}

void ajouterDemande (TabDemande *tab,int numDem,int dossier,int numCite)
{
	Demande d, **aux, *s;
	d=nouvDemande(numDem,dossier,numCite);
	if(tab->nbDemande == tab->maxDemande)
		{
			(tab->maxDemande) += 20;
			aux = (Demande **)realloc(tab->tabDemande,(tab->maxDemande)*sizeof(Demande *));
			if (aux == NULL)
			{
				printf("Problème realloc\n");
				exit(1);
			}
		}
		s = (Demande *)malloc(sizeof(Demande));
		if (s == NULL)
		{
			printf("Problème malloc\n");
			exit(1);
		}
		*s = d;
		tab->tabDemande[tab->nbDemande] = s;
		(tab->nbDemande)++;
}

void ListeBackupsDem (void)
{
	char backup[50];
	int nb=1;
	FILE *flot;
	flot=fopen("BDD/bkpdem.txt","r");
	if (flot==NULL)
	{
		printf("Erreur de lecture du fichier backups.txt\n");
		exit(1);
	}
	fscanf(flot, "%s%*c", &backup);
	while(!feof(flot))
	{
		printf("Backup n°%d:%s\n",nb,backup);
		nb++;
		fscanf(flot, "%s%*c", &backup);
	}
	fclose(flot);
}

void supprDemande (TabDemande *tab, int rang)
{
	int i;
	tab->nbDemande -= 1;
	for (i=rang;i<(tab->nbDemande);i++)
		tab->tabDemande[i]=tab->tabDemande[i+1];	
}

//Cherche les demandes d'un etudiant Dx=-1 si pas de demande
void rechDemandesEtu (int dossier, Demande **tabDemande,int nb, int *D1, int *D2)
{
	int i;
	for(i=0;i<nb;i++)
	{
		if (tabDemande[i]->dossier==dossier && *D1==-1)
		{	*D1=i;
			printf("%d",i);
		}
		else
		if(tabDemande[i]->dossier==dossier)
			*D2=i;
	}
}

void affDemCite (Demande **tabDemande, int numCite,int nb)
{
	int i;
	for(i=0;i<nb;i++)
		if(tabDemande[i]->numCite==numCite)
			affDemande (tabDemande[i]);
}


