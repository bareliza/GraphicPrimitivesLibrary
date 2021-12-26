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

void przepiszDoMacierzy1(macierz *m, double (*a)[n+1][n+1]) {
	int i,j;

	for ( i = 1; i <= n; ++i )
		for ( j = 1; j <= n; ++j )
			m->a[i][j] = (*a)[i][j];
}

void przepiszZMacierzyDoMacierzy(macierz *m1, macierz *m2) {
	przepiszDoMacierzy1(m2, &(m1->a));
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

void rozwiazUkladRownan(macierz *m, double w[n], double wyj[n]) {
	macierz m1, m2, m3;
	
	policzWyznacznik(m);
	
	// Brzydki kod, ladniej byloby tablice macierzy: macierz m1[3] i petla.
	// Ta wersja jednak tez dobrze dziala, przynajmniej dla n = 3.
	przepiszZMacierzyDoMacierzy(m, &m1);
	zamienKolumne(&m1, w, 1);
	policzWyznacznik(&m1);
	przepiszZMacierzyDoMacierzy(m, &m2);
	zamienKolumne(&m2, w, 2);
	policzWyznacznik(&m2);
	przepiszZMacierzyDoMacierzy(m, &m3);
	zamienKolumne(&m3, w, 3);
	policzWyznacznik(&m3);

	if( m->wyznacznik == 0 ) printf("Brak rozwiazan ukladu rownan\n");
	else {
		wyj[0] = m1.wyznacznik / m->wyznacznik;
		wyj[1] = m2.wyznacznik / m->wyznacznik;
		wyj[2] = m3.wyznacznik / m->wyznacznik; 
	}
}

// P[unktow]A[proksymacji]
#define PkAp (100)

double xDoP(double x, int p) {
	double pom;
	if ( p == 0 ) return 1;
	if ( p == 1 ) return x;
	if ( p == 2 ) return x*x;
	if ( p == 3 ) return x*x*x;
	if ( p == 4 ) return xDoP(xDoP(x,2),2); // x*x*x*x;
	if ( p >  4 ) return x*xDoP(x,p-1);
	if ( p <  0 ) return 1 / xDoP(x,-p);
	return 1;
}

double suma(double x[PkAp], int p, int ile) {
	int i;
	double odp;
	
	odp = 0;
	for( i = 0; i < ile ; ++i ) odp += xDoP(x[i], p);
	
	return odp; 
}

double suma2(double y[PkAp], double x[PkAp], int p, int ile) {
	int i;
	double odp;
	
	odp = 0;
	for( i = 0; i < ile ; ++i ) odp += y[i] * xDoP(x[i], p);
	
	return odp;
}

void aproksymacjaWielomianemStopniaDwa(double x[PkAp], double y[PkAp], double odp[n]) {
	macierz m;
	double w[n];
	
	// https://pl.wikipedia.org/wiki/Aproksymacja_wielomianowa
	//
	// ze wzoru [4] :
	//
	// n = PkAp - 1
	// m = 2
	//
	// a0 * (n+1)             + a1 * suma(x0..xn)      + a2 * suma(x0^2..xn^2) = suma(y0..yn)
	// a0 * suma(x0..xn)      + a1 * suma(x0^2..xn^2)  + a2 * suma(x0^3..xn^3) = suma(y0*x0..yn*xn)
	// a0 * suma(x0^2..xn^2)  + a1 * suma(x0^3..xn^3)  + a2 * suma(x0^4..xn^4) = suma(y0*x0^2..yn*xn^2)
	//
	// odp[i] = a[i], i = 0..2

	m.a[1][1] = PkAp;
	m.a[1][2] = suma(x,1,PkAp);
	m.a[1][3] = suma(x,2,PkAp);

	m.a[2][1] = m.a[1][2]; // suma(x,1,PkAp);
	m.a[2][2] = m.a[1][3]; // suma(x,2,PkAp);
	m.a[2][3] = suma(x,3,PkAp);

	m.a[3][1] = m.a[2][2]; // suma(x,2,PkAp);
	m.a[3][2] = m.a[2][3]; // suma(x,3,PkAp);
	m.a[3][3] = suma(x,4,PkAp);
	
	w[0] = suma2(y, x, 0, PkAp);
	w[1] = suma2(y, x, 1, PkAp);
	w[2] = suma2(y, x, 2, PkAp);

	rozwiazUkladRownan(&m, w, odp);
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

double wektor4[n];
double wektor5[n];

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

	printf("\n\n    CBDO. Nie uwzgledniono sytuacji, gdy |D| == 0.\n\n\n");
	
	rozwiazUkladRownan(&D, wektor1, wektor4);
	
	printf("To samo rozwiazanie z jednym wywolaniem procedury:\n\n");
	
	wypiszWektor(wektor4);	
	
	pomnozMacierzPrzezWektor(&D, wektor4, wektor5);
	
	printf("\n\nSprawdzenie 2: Po pomnozeniu D przez powyzszy wektor otrzymano wektor: \n\n");

	wypiszWektor(wektor5);
	
	printf("\n\n    CBDO 2. Tu juz badam, czy |D| == 0.\n\n\n");
}


