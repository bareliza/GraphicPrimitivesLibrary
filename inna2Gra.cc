#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#define RX (400)
#define RY (400)

Projektor P(RX,RY);
Klawiatura K;

#define BX (128)
#define BY (128)

unsigned int bmapa[BX*BY];
int i,j;

void czysc(unsigned int *bm, int bx, int by, unsigned int k) {
  for(int i = 0; i < bx*by; ++i) bm[i] = k;
}

#define RAMKA (8)
void paski(unsigned int *bm, int bx, int by, int szer2doM1) {
  int i, j;
  for(i = RAMKA; i < bx - RAMKA; ++i)
    for(j = RAMKA; j < by - RAMKA; ++j)
       bm[j*by + i] = ( (i & szer2doM1) == 0 ) ? 0 : 0xffffff;

}

void paskiPoziome(unsigned int *bm, int bx, int by, int POZIOME_CO, int szerokosc) {
  int i, j;
  for(i = RAMKA; i < bx - RAMKA; ++i)
    for(j = RAMKA; j < by - RAMKA; ++j)
       if((j % POZIOME_CO) < szerokosc) bm[j*by + i] = 0xff;

}

void rysuj(unsigned int *bm, int bx, int by, int xe, int ye) {
  int i, j;
  for(i = 0; i < bx; ++i)
    for(j = 0; j < by; ++j)
      P.rysujPunkt(xe + i, ye + j, bm[j * by + i]); 
}

double X1, XB, AP, BP;

double a, b;
void obliczWspolczynniki(void) {
	a = XB / ( X1*X1*( 1 + 2*AP / ( BP * ( 1 - AP / BP ) ) ) );
	b = 2 * a * X1 * AP / ( BP*( 1 - AP / BP ) );
}

double f(double x) {
	printf("x = %3.3f f(x) = %3.3f", x, a*x*x + b*x);  

	return a*x*x + b*x;
}

double BPdoAP(double x)
{
	return x*(AP-BP)/X1+BP;
}

void perspektywa(unsigned int *bm, int bx, int by, double xe, double ye) {
  double i, j, BAP, fodi;
  for(i = 0; i < X1; ++i) {
    BAP = BPdoAP(i);
    fodi = f(i);
    for(j = -BAP/2; j < BAP/2; ++j)
      P.rysujPunkt(xe + i, ye + j, bm[((int)((BY-1)*(j+BAP/2)/BAP))*by + ((int)fodi)]);
  }
}

int main(int argc, char** argv) {
  P.czysc(0x0060ff);
  P.linia(10,10,90,90,0xff0000);
 
  czysc(bmapa, BX, BY, 0xff00ff);
  paski(bmapa, BX, BY, 8);
  paskiPoziome(bmapa, BX, BY, 16, 3);
  rysuj(bmapa, BX, BY, RX/2 - BX/2, 10); // RY/2 - BY/2);
  
  X1 = 100;
  XB = BX;
  AP = 50;
  BP = 300;
  obliczWspolczynniki();
 
  for(double i = 0; i < X1; ++i)
    P.rysujPunkt( RX/2 - BX/2 + f(i), 10, 0xff00);
    
  perspektywa(bmapa, BX, BY, 50.0, 250.0);
  
  P.odswiez();
  K.czekajNaKlawisz();
}
