#include "logement.h"

Logement nouvLogement (int numCite, int numLogement, int dossier, Type type, Statut etat, Booleen handicap)
{
	Logement l;
	l.numCite=numCite;
	l.numLogement=numLogement;
	l.dossier=dossier;
	l.type=type;
	l.etat=etat;
	l.handicap=handicap;
	return l;
}

void affLogement (Logement *l)
{
	printf("Le numéro de Cite est le : %d\n",l->numCite);
	printf("Le numéro de Logement est le : %d\n",l->numLogement);
	printf("Le numero de  dossier de l'etudiant est : %d\n",l->dossier);
	printf("Type : %d\n",l->type);
	printf("Etat : %d\n",l->etat);
	printf("Handicap : %d\n",l->handicap);
	
}

TabLogement * initTabLogement (char *nomfic)
{
	int nbLogement = 0, maxLogement = 0;
	Logement **tabLogement;
	TabLogement *t;
	t = (TabLogement *)malloc(sizeof(TabLogement));
	tabLogement = (Logement **)malloc(20*sizeof(Logement *));
	if (tabLogement==NULL || t==NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	chargeTabLogement(tabLogement,&nbLogement,&maxLogement,nomfic);
	t->nbLogement=nbLogement;
	t->maxLogement=maxLogement;
	t->tabLogement=tabLogement;
	return t;
}

void chargeTabLogement(Logement **tabLogement, int *nbLogement, int *maxLogement, char *nomfic)
{
	FILE *flot;
	Logement l, **aux, *s;
	flot=fopen(nomfic,"r");
	if (flot==NULL)
	{
		printf("Erreur de lecture du fichier Logement");
		exit(1);
	}
	l=chargeLogement(flot);
	while(!feof(flot))
	{
		if(*nbLogement == *maxLogement)
		{
			(*maxLogement) += 10;
			aux = (Logement **)realloc(tabLogement,(*maxLogement)*sizeof(Logement *));
			if (aux == NULL)
			{
				printf("Problème realloc\n");
				fclose(flot);
				exit(1);
			}
		}
		s = (Logement *)malloc(sizeof(Logement));
		if (s == NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			exit(1);
		}
		*s = l;
		tabLogement[*nbLogement] = s;
		(*nbLogement)++;
		l=chargeLogement(flot);	
	}
	fclose(flot);
}
	
Logement chargeLogement (FILE *flot)
{
	Logement l;
	fscanf(flot, "%d%*c", &l.numCite);
	fscanf(flot, "%d%*c", &l.numLogement);
	fscanf(flot, "%d%*c", &l.dossier);
	fscanf(flot, "%d%*c", &l.type);
	fscanf(flot, "%d%*c", &l.etat);
	fscanf(flot, "%d%*c", &l.handicap);	
	return l;
}

int rechLogement(int numLogement, Logement **tabLogement, int nbLogement)
{
	int inf = 0, m, sup = nbLogement-1;
	if(nbLogement == 0)
	return -1;
	while(inf <= sup)
	{
		m = (inf + sup)/2;
		if(numLogement <= tabLogement[m]->numLogement)
		sup = m - 1;
		else
		inf = m + 1;
	}
	if(inf >= nbLogement)
	return -1;
	if(tabLogement[inf]->numLogement != numLogement)
	return -1;
	return inf;
}

//Récupére une Logement au rang n d'un tableau de Logement
Logement * recupLogement (TabLogement *tab, int rang)
{
	if (rang < 0 || rang >= tab->nbLogement)  
	return NULL;
	return tab->tabLogement[rang];
}

//Tout est dans le titre
void libereTabLogement (TabLogement *tab)
{
	int i;
	for(i = 0; i < tab->nbLogement; i++)
	free(tab->tabLogement[i]);
	free(tab->tabLogement);
	free(tab);
}

//Cherche les Logements d'un etudiant Dx=-1 si pas de Logement
int rechLogementEtu (int dossier, Logement **tabLogement,int nb)
{
	int inf = 0, m, sup = nb-1;
	if(dossier == 0)
	return -1;
	while(inf <= sup)
	{
		m = (inf + sup)/2;
		if(dossier <= tabLogement[m]->dossier)
		sup = m - 1;
		else
		inf = m + 1;
	}
	if(inf >= nb)
	return -1;
	if(tabLogement[inf]->dossier != dossier)
	return -1;
	return inf;	
}

//Sauvegarde les changements de Logements dans un fichier "nomfic"
void sauveTabLogement (TabLogement *tab, char *nomfic)
{
	int i;
	FILE *flot;
	flot = fopen(nomfic,"w");
	if(flot == NULL)
	{
		printf("Erreur d'écriture du fichier %s \n", nomfic);
		exit(1);
	}
	for(i=0; i< tab->nbLogement; i++)
	{
		fprintf(flot,"%.5d %.5d %.5d %d %d %d\n", tab->tabLogement[i]->numCite, tab->tabLogement[i]->numLogement, tab->tabLogement[i]->dossier, tab->tabLogement[i]->type, tab->tabLogement[i]->etat, tab->tabLogement[i]->handicap);
	}
	fclose(flot);
}

void ajouterLogement (TabLogement *tab, int numCite, int numLogement, int dossier, Type type, Statut etat, Booleen handicap)
{
	Logement d, **aux, *s;
	d=nouvLogement(numCite, numLogement, dossier, type, etat, handicap);
	if(tab->nbLogement == tab->maxLogement)
		{
			(tab->maxLogement) += 20;
			aux = (Logement **)realloc(tab->tabLogement,(tab->maxLogement)*sizeof(Logement *));
			if (aux == NULL)
			{
				printf("Problème realloc\n");
				exit(1);
			}
		}
		s = (Logement *)malloc(sizeof(Logement));
		if (s == NULL)
		{
			printf("Problème malloc\n");
			exit(1);
		}
		*s = d;
		tab->tabLogement[tab->nbLogement] = s;
		(tab->nbLogement)++;
}

void supprLogement (TabLogement *tab, int rang)
{
	int i;
	tab->nbLogement -= 1;
	for (i=rang;i<(tab->nbLogement);i++)
		tab->tabLogement[i]=tab->tabLogement[i+1];	
}

void triLogement(Logement **tab, int nb, int tri)
{
	Logement **R, **S;
	if(nb == 1) return;
	R = (Logement **)malloc(nb/2 * sizeof(Logement *));
	S = (Logement **)malloc((nb - nb/2) * sizeof(Logement *));
	if(R == NULL || S == NULL)
	{
		printf("Problème malloc\n");
		exit(1);
	}
	triLogementCopier(tab, 0, nb/2, R);
	triLogementCopier(tab, nb/2, nb, S);
	triLogement(R, nb/2, tri);
	triLogement(S, nb-nb/2, tri);
	triLogementFusion(R, nb/2, S, nb-nb/2, tab, tri);
	free(R);
	free(S);
}

void triLogementCopier(Logement **tab, int i, int j, Logement **R)
{
	int k = 0;
	for(i; i<j; i++)
	{
		R[k] = tab[i];
		k++;
	}
}

void triLogementFusion(Logement **R, int n, Logement **S, int m, Logement **T, int tri)
//Critères de tri : 0 - numéroLogement; 1 - dossier
{
	int i = 0, j = 0, k = 0;
	Booleen verif;
	while(i < n && j < m)
	{
		verif = NON;
		if(tri == 0 && R[i]->numLogement > S[j]->numLogement)
			verif = OUI;
		if(tri == 1 && R[i]->dossier > S[j]->dossier)
			verif= OUI;
		if(verif)
		{
			T[k] = R[i];
			i++;
			k++;
		}
		else
		{
			T[k] = S[j];
			j++;
			k++;
		}
	}
	while(i < n)
	{
		T[k] = R[i];
		i++;
		k++;
	}
	while(j < m)
	{
		T[k] = S[j];
		j++;
		k++;
	}
}
