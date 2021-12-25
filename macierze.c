#include <stdio.h>
#include <stdlib.h>

#define n (3)

struct _macierz {
	double a[n+1][n+1];
	double wyznacznik;
};

typedef struct _macierz macierz;

void przepiszDoMacierzy(macierz *m, double (*a)[n][n]) {
	int i,j;

	for ( i = 1; i <= n; ++i )
		for ( j = 1; j <= n; ++j )
			m->a[i][j] = (*a)[i-1][j-1];
}

void wypiszMacierz(macierz *m) {
	int i,j;

	for ( i = 1; i <= n; ++i ) {
		for ( j = 1; j <= n; ++j ) {
			printf( "m->a[%d][%d] = %3.3f ; ", i, j, m->a[i][j] );
		}
		printf("\n");
	}
}

void wypiszWektor(double w[n]) {
	int i;

	for ( i = 1; i <= n; ++i ) printf("w[%d] = %3.3f ; ", i,  w[i-1]);

	printf("\n");
}


void zamienKolumne(macierz *wej, double kolumna[n], int nrKolumny) {
	int i;
	
	for( i = 0; i < n; ++i ) wej->a[i+1][nrKolumny] = kolumna[i];	
}

void policzWyznacznik(macierz *m) {
	if ( n == 3 ) {
		m->wyznacznik = m->a[1][1]*m->a[2][2]*m->a[3][3] + m->a[2][1]*m->a[3][2]*m->a[1][3] + m->a[3][1]*m->a[1][2]*m->a[2][3] 
		              - m->a[2][1]*m->a[1][2]*m->a[3][3] - m->a[1][1]*m->a[3][2]*m->a[2][3] - m->a[3][1]*m->a[2][2]*m->a[1][3];
	}
	else {
		printf("Brak algorytmu liczenia wyznacznika dla macierzy wymiaru %d.\n", n);
		exit(1);
	} 
}

void pomnozMacierzPrzezWektor(macierz *m, double w1[n], double w[n])
{
	int i, j;
	
	for ( i = 1; i <= n; ++i ) {
		w[i-1] = 0;
		for ( j = 1; j <= n; ++j )
			w[i-1] += m->a[i][j] * w1[j-1];
	}
}

double a[3][3] = {
	{2,3,4},
	{4,5,7},
	{7,8,11}
};

double b[3][3] = {
	{2,3,4},
	{0,5,6},
	{0,0,9}
};

double c[3][3] = {
	{2,0,0},
	{0,5,0},
	{0,0,9}
};

double d[3][3] = {
	{3,2,3},
	{3,5,6},
	{2,8,9}
};

double wektor[n] = { 3, 3, 3 };
double wektor1[n] = { 1, 3, 0 };
double wektor2[n];
double wektor3[n];


int main(int argc, char **argv) {
	macierz A,B,C,D,E,D1,D2,D3;
	
	przepiszDoMacierzy(&A, &a);	
	przepiszDoMacierzy(&B, &b);	
	przepiszDoMacierzy(&C, &c);	
	przepiszDoMacierzy(&D, &d);	
	przepiszDoMacierzy(&E, &d);	

	wypiszMacierz(&A);printf("\n");
	wypiszMacierz(&B);printf("\n");
	wypiszMacierz(&C);printf("\n");
	wypiszMacierz(&D);printf("\n");

	policzWyznacznik(&A);	
	policzWyznacznik(&B);	
	policzWyznacznik(&C);	
	policzWyznacznik(&D);	

	printf("det(A) = |A| = %3.3f\n", A.wyznacznik);
	printf("det(B) = |B| = %3.3f\n", B.wyznacznik);
	printf("det(C) = |C| = %3.3f\n", C.wyznacznik);
	printf("det(D) = |D| = %3.3f\n\n", D.wyznacznik);

        zamienKolumne( &A, wektor, 1 );
        zamienKolumne( &B, wektor, 2 );
        zamienKolumne( &C, wektor, 3 );
        zamienKolumne( &D, wektor1, 1 );
        zamienKolumne( &E, wektor, 1 );

	wypiszMacierz(&A);printf("\n");
	wypiszMacierz(&B);printf("\n");
	wypiszMacierz(&C);printf("\n");
	wypiszMacierz(&D);printf("\n");
	wypiszMacierz(&E);printf("\n");

	policzWyznacznik(&A);	
	policzWyznacznik(&B);	
	policzWyznacznik(&C);	
	policzWyznacznik(&D);	
	policzWyznacznik(&E);	

	printf("det(A) = |A| = %3.3f\n", A.wyznacznik);
	printf("det(B) = |B| = %3.3f\n", B.wyznacznik);
	printf("det(C) = |C| = %3.3f\n", C.wyznacznik);
	printf("det(D) = |D| = %3.3f\n\n", D.wyznacznik);
	printf("det(E) = |E| = %3.3f\n\n", E.wyznacznik);

	printf("Uklad rownan zadany jest macierza D i wektorem wektor1\n");
	printf("Rozwiazac ten uklad rownan z uzyciem wzorow Cramera.\n\n");
	
	printf("Macierz D:\n\n");

	przepiszDoMacierzy(&D, &d);	

	wypiszMacierz(&D);printf("\n");
	
	printf("Macierze D1, D2, D3, majace w porownaniu z D w i-tej kolumnie wektor wektor1:\n\n");

	przepiszDoMacierzy(&D1, &d);	
	przepiszDoMacierzy(&D2, &d);	
	przepiszDoMacierzy(&D3, &d);	

        zamienKolumne( &D1, wektor1, 1 );
        zamienKolumne( &D2, wektor1, 2 );
        zamienKolumne( &D3, wektor1, 3 );

	wypiszMacierz(&D1);printf("\n");
	wypiszMacierz(&D2);printf("\n");
	wypiszMacierz(&D3);printf("\n");

	policzWyznacznik(&D);	
	policzWyznacznik(&D1);	
	policzWyznacznik(&D2);	
	policzWyznacznik(&D3);	

	printf("det(D) = |D| = %3.3f\n", D.wyznacznik);
	printf("det(D1) = |D1| = %3.3f\n", D1.wyznacznik);
	printf("det(D2) = |D2| = %3.3f\n", D2.wyznacznik);
	printf("det(D3) = |D3| = %3.3f\n\n", D3.wyznacznik);

	printf("Rozwiazanie to: |D1|/|D| = %3.3f ; |D2|/|D| = %3.3f ; |D3|/|D| = %3.3f ; \n\n",
	D1.wyznacznik / D.wyznacznik, D2.wyznacznik / D.wyznacznik, D3.wyznacznik / D.wyznacznik); 	

	printf("Sprawdzenie: Rozwiazanie: \n\n");
	wektor2[0] = D1.wyznacznik / D.wyznacznik;
	wektor2[1] = D2.wyznacznik / D.wyznacznik;
	wektor2[2] = D3.wyznacznik / D.wyznacznik;
	wypiszWektor(wektor2);

	pomnozMacierzPrzezWektor(&D, wektor2, wektor3);

	printf("\n\nPo pomnozeniu D przez powyzszy wektor otrzymano wektor: \n\n");

	wypiszWektor(wektor3);

	printf("\n\n CBDO. Nie uwzgledniono sytuacji, gdy |D| = 0.");
}


