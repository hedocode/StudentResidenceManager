#include "projet.h"


//parametres
/*	
	si x=3 texte, si x=4 fond
	x0=Noir
	x1=Rouge
	x2=Vert
	x3=Jaune
	x4=Bleu
	x5=Magenta
	x6=Cyan
	x7=Blanc
*/

void clear(void)
{
	printf("\033[H\033[2J");
}

void couleur(int color)
{
	printf("\033[%dm",color);
}

void normal(void)
{
	printf("\033[0;0m");
}

void bold(void)
{
	printf("\033[01;37m");
}

void blue(void)
{
	couleur(44);
	couleur(37);
}

void green(void)
{
	couleur(42);
	couleur(37);
}

void yellow(void)
{
	couleur(43);
	couleur(37);
}

void cyan(void)
{
	couleur(46);
	couleur(37);
}

void dark(void)
{
	couleur(40);
	couleur(31);
}

void red(void)
{
	couleur(41);
	couleur(37);
}

void shadow(void)
{
	couleur(40);
	couleur(30);
}
