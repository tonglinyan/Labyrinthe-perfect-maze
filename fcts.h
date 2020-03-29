#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAILLE 100
#define MUR 100

typedef struct labyrinthe
{
	int dim;
	int c[TAILLE][TAILLE];
}laby;

/***************** fonctions communes ****************************/
laby initialisation();
void affichage1(laby l);
void affichage(laby l);

/***************** division recursive ****************************/
int divi(int borneH,int borneG,int borneB,int borneD);
laby division(laby l,int borneH,int borneG,int borneB,int borneD);

/***************** eller's algorithme ****************************/
laby preLigne(laby l,int lig);
laby lignePair(laby l,int lig);
laby ligneImpar(laby l,int lig);
laby derLigne(laby l,int lig);
laby eller(laby l);

/*********************** solution ********************************/
int estArrive(int x1,int y1,int x2,int y2);
int auFond(laby l,int lig,int col,int indice);
int direction(laby l,int x,int y);
laby resolve(laby l,int lig,int col,int x2,int y2);
int estChemin(laby l,int lig,int col);
laby chemin(laby l,int x1,int y1,int x2,int y2);

