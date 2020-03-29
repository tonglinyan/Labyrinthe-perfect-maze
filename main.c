#include "fcts.h"

void main()
{	laby l1,l2,l;
	int x1,y1,x2,y2,n,choix,i,j;
	srand((unsigned)time(NULL));
	long d,f,m;
	do 
	{	
		printf ("saisissez la dimension du labyrinthe (nombre impaire): ");
		scanf ("%d",&n);
	}
	while ((n%2 == 0)||(n > TAILLE));
	d = clock();
	printf("\n");
	printf("*********************************************************\n");
	printf("               méthode division récursive                \n");
	printf("*********************************************************\n");
	l1 = initialisation(n);
	l1 = division(l1,0,0,l1.dim-1,l1.dim-1);
	affichage1(l1);
	m = clock();
	printf("\n");
	printf("*********************************************************\n");
	printf("                 eller's algorithme                      \n");
	printf("*********************************************************\n");
	l2 = initialisation(n);
	l2 = eller(l2);
	affichage1(l2);
	f = clock();
	printf("la méthode division récusive prend %ld ms.\n",m-d);
	printf("eller's algorithme prend %ld ms.\n",f-m);

	do
	{
		printf("Quelle résolution voulez-vous voir ? (1 ou 2)\n");
		scanf("%d", &choix);
	}
	while (choix!=1 && choix!=2);
	if (choix == 1) l = l1;
	else l = l2;
	do 
	{
		printf("choisissez un point pour commencer (entre 1 et %d)\n",l.dim-2);
		scanf("%d%d",&x1,&y1);
	}
	while ((x1>=l.dim)||(y1>=l.dim)||(l.c[x1][y1]==MUR));
	do 
	{	
		printf("choisissez un point pour terminer (entre 1 et %d)\n",l.dim-2);
		scanf("%d%d",&x2,&y2);
	}
	while ((x2>=l.dim)||(y2>=l.dim)||(l.c[x2][y2]==MUR));
	l = resolve(l,x1,y1,x2,y2);
	l = chemin(l,x1,y1,x2,y2);
	affichage1(l);
	affichage(l);
}
