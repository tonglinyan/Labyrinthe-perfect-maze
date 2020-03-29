#include "fcts.h"


laby initialisation(int n)
{
	int i, j;
	laby l;
	l.dim = n;
	for (i=1;i<l.dim-1;i++)
		for (j=1;j<l.dim-1;j++)
			l.c[i][j] = 0;
	for (i=0;i<l.dim;i++)
	{
		l.c[0][i] = MUR;
		l.c[l.dim-1][i] = MUR;
		l.c[i][0] = MUR;
		l.c[i][l.dim-1] = MUR;
	}
	return l;
}


void affichage(laby l)
{
	int i,j;
	printf("\n");
	for (i=0;i<l.dim;i++)
	{
		for (j=0;j<l.dim;j++)
		{	
			if (l.c[i][j] == MUR) printf("# ");
			else 	if (l.c[i][j] == 1) printf("O ");
				else printf("  ");
		}
		printf("\n");
	}
}


void affichage1(laby l)
{
	int i,j;
	printf("\n");
	for (i=0;i<l.dim;i++)
	{
		for (j=0;j<l.dim;j++)
		{	
			if (l.c[i][j] == MUR) printf("# ");
			else printf("  ");
		}
		printf("\n");
	}
}


/******************************* méthode division récursive ********************************/

int divi(int borneH,int borneG,int borneB,int borneD)
/*vérifier si division est possible 
0 pour impossible, 1 pour possible*/
{	int res;
	if ((borneB-borneH) == 2 || (borneD-borneG) == 2) res = 0;
	else res = 1;
	return res;
}


laby division(laby l,int borneH,int borneG,int borneB,int borneD)
{	
	int booleen;
	int lig,col,i;
	int h,b,g,d;
	int ferme;
	booleen = divi(borneH,borneG,borneB,borneD);
	if (booleen == 1) 
	{
		lig = 2 * (rand()%((borneB-borneH-1)/2)+1)+borneH;
		col = 2*(rand()%((borneD-borneG-1)/2)+1)+borneG;
		h = 2*(rand()%((lig-borneH)/2))+1+borneH;
		b = 2*(rand()%((borneB-lig)/2))+lig+1;	
		g = 2*(rand()%((col-borneG)/2))+1+borneG;
		d = 2*(rand()%((borneD-col)/2))+col+1;
		ferme = rand()%4;
		switch (ferme)
		{
			case 0:h = TAILLE-1;break;
			case 1:b = TAILLE-1;break;
			case 2:g = TAILLE-1;break;
			case 3:d = TAILLE-1;break;
		}
		for (i=borneH+1;i<borneB;i++)
			if ((i != h) && (i != b)) l.c[i][col] = MUR;
		for (i=borneG+1;i<borneD;i++)
			if ((i != g) && (i != d)) l.c[lig][i] = MUR;
		l = division(l,borneH,borneG,lig,col);
		l = division(l,lig,borneG,borneB,col);
		l = division(l,borneH,col,lig,borneD);
		l = division(l,lig,col,borneB,borneD);
	}	
	return l;
}


/************************************** solution ******************************************/

int direction(laby l, int lig, int col)
/*renvoie la direction
	En bas 1
	A droite 2
	En haut 3
	A gauche 4*/
{	
	int t[4] = {l.c[lig+1][col],l.c[lig][col+1],l.c[lig-1][col],l.c[lig][col-1]};
	int indice = 0,i;
	for (i=1;i<4;i++)
		if (t[i]<t[indice]) indice = i;
	return indice;
}


int auFond(laby l,int lig,int col,int indice)
{
	int t[4] = {l.c[lig+1][col],l.c[lig][col+1],l.c[lig-1][col],l.c[lig][col-1]};
	int somme = 0,i,res;
	for (i=0;i<4;i++)
		if (i!=indice) somme += t[i];
	if (somme == 3*MUR) return 1;
	else return 0;
}


int estArrive(int x1,int y1,int x2,int y2)
{
	if (x1 == x2 && y1 == y2) return 1;
	else return 0;
}


laby resolve(laby l,int lig,int col,int x2,int y2)
{	int direc;
	if (estArrive(lig,col,x2,y2) == 0)
	{
		direc = direction(l,lig,col);
		if (auFond(l,lig,col,direc) == 1) l.c[lig][col] += 2;
		else l.c[lig][col] += 1;
		switch (direc)
		{
			case 0: l = resolve(l,lig+1,col,x2,y2); break;
			case 1: l = resolve(l,lig,col+1,x2,y2); break;
			case 2: l = resolve(l,lig-1,col,x2,y2); break;
			case 3: l = resolve(l,lig,col-1,x2,y2); break;
		}
	}
	return l;
}


int estChemin(laby l,int lig,int col)
{	
	int t[4] = {l.c[lig+1][col],l.c[lig][col+1],l.c[lig-1][col],l.c[lig][col-1]};
	int res = 0,i;
	for (i=0;i<4;i++)
		if (t[i] == 1) res += t[i];
	return res;
}


laby chemin(laby l,int x1,int y1,int x2,int y2)
{
	int i,j;
	l.c[x1][y1] = 1;
	l.c[x2][y2] = 1;
	for (i=1;i<l.dim-1;i++)
		for (j=1;j<l.dim-1;j++)
			if ((l.c[i][j] > 1)&&(l.c[i][j] < MUR))
				if (estChemin(l,i,j) > 1) 
					l.c[i][j] = 1;
				else l.c[i][j] = 0;
	return l;
}


/****************************** méthode eller's *******************************************/

laby preLigne(laby l,int lig)
{	
	int i,col,addmur,dep = 1,set = 1;
	for (i=2;i<l.dim-1;i+=2)
	{
		addmur = rand()%2;
		if (addmur == 1)
		{
			for (col=dep;col<i;col++)
				l.c[lig][col] = set;
			l.c[lig][i] = MUR;
			set++;
			dep = i+1;
		}
	}
	for (col=dep;col<i;col++)
		l.c[lig][col] = set;
	return l;
}


laby lignePair(laby l,int lig)
{	
	int i,col,nbblc,w,t,arv,dep=1,set=1,blc[l.dim];
	for (i=1;i<l.dim-1;i++)
		l.c[lig][i]=MUR;
	while (dep < l.dim-1)	
	{
		arv = dep+2;
		while ((arv < l.dim-1)&&(l.c[lig-1][arv] == l.c[lig-1][dep]))
			arv += 2;
		nbblc = rand()%((arv-dep)/2)+1;
		{
			for (i=0;i<((arv-dep)/2);i++)
					blc[i] = i+1;	
			for (i=0;i<nbblc;i++)
			{
				w = rand()%((arv-dep)/2-i)+i;
				t = blc[i];
				blc[i] = blc[w];
				blc[w] = t;	
				col = 2*(blc[i]-1)+dep;
				l.c[lig][col] = l.c[lig-1][col];	
			}
		}	
		dep = arv;
	}	
	return l;
}


laby ligneImpair(laby l,int lig)
{	int i,j,k,col,addmur,r,set = 1,m = 0,mur[TAILLE];
	for (i=1;i<l.dim-1;i+=2)
		if (l.c[lig-1][i] != MUR)
			l.c[lig][i] = l.c[lig-1][i];
	for (i=2;i<l.dim-1;i+=2)
	{	
		addmur = rand()%2;
		if (addmur == 0) l.c[lig][i] = MUR;
	}
	for (i=1;i<l.dim-1;i+=2)
	{		
		j = i+2;
		while (((l.c[lig-1][i] != l.c[lig-1][j]) || (l.c[lig][i] == MUR)) && (j<l.dim-1))
			j += 2;
		if (l.c[lig-1][i] == l.c[lig-1][j] && l.c[lig-1][i] != MUR)
		{	
			col = 2*(rand()%((j-i)/2))+i+1;
			mur[m] = col;
			m++;
			for (k=i+1;k<j;k++)
				l.c[lig][k] = 0;
		}
	}
	printf("\n");
	for (i=1;i<l.dim-1;i++)
		if (l.c[lig][i] != MUR)
			if (l.c[lig][i-1] != MUR) 
				l.c[lig][i] = l.c[lig][i-1];
			else
			{
				l.c[lig][i] = set;
				set++;
			}
	for (i=0;i<m;i++)
		l.c[lig][mur[i]] = MUR;
	return l;
}


laby derLigne(laby l,int lig)
{
	int i,j,col;
	for (i=1;i<l.dim-1;i+=2)
		if (l.c[lig-1][i]!=MUR)
			l.c[lig][i] = l.c[lig-1][i];
	for (i=1;i<l.dim-2;i+=2)
	{	
		j = i+2;
		while ((l.c[lig][i] != l.c[lig][j] || l.c[lig][i] == 0) && (j<l.dim-1))
			j += 2;
		if (l.c[lig][i] == l.c[lig][j] && l.c[lig][i] != 0)
		{
			col = 2*(rand()%((j-i)/2))+i+1;
			l.c[lig][col] = MUR;
		}
	}
	return l;
}


laby eller(laby l)
{	
	int i,j;
	l = preLigne(l,1);
	for (i=2;i<l.dim-2;i++)
	{
		if (i%2 == 0)
		{		
			l = lignePair(l,i);
		}
		else
			l = ligneImpair(l,i);
	}
	l = derLigne(l,l.dim-2);
	for (i=0;i<l.dim-1;i++)
		for (j=0;j<l.dim-1;j++)
			if (l.c[i][j] != MUR)
				l.c[i][j] = 0;
	return l;
}

