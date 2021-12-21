#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#define RX (1000)
#define RY (600)

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
      P.prostokat(xe + 4*i, ye + 4*j, 3, 3, bm[j * by + i]); 
}

double X1, XB, AP, BP;

// Wyjsciowy uklad rownan:
//
// /  f'(0) / f'(X1) = BP / AP (lub odwrotnie, nie pamietam)
// |
// <  f(0) = 0 => c = 0
// |
// \  f(X1) = XB
//
// oraz  f(x) w postaci, f(x) = a*x*x + b*x + c
//

double a, b;
void obliczWspolczynniki(void) {
	a = XB / ( X1*X1*( 1 + 2*AP / ( BP*( 1 - AP / BP ) ) ) );
	b = 2*a*X1*AP / ( BP*( 1 - AP / BP ) );
}

double f(double x) {
	printf("x = %3.3f f(x) = %3.3f", x, a*x*x + b*x);  

	return a*x*x + b*x + 0.5;
}

double BPdoAP(double x)
{
	return x*(AP-BP)/X1 + BP + 0.5;
}

double rozciagnij(double j, double BAP) {
  return ((double)(BY-1.0))*(j+BAP/2)/BAP + 0.5; 
//    return ((double)(BY    ))*(j+BAP/2)/BAP + 0.5; 
}

unsigned rgbKrok(int i)
{
  unsigned zielenPlus;
  
  zielenPlus = 0x0;
  if ( i < 0 ) {
    i = -i;
    zielenPlus = 0x7f00;
  }
  if ( i == 1 ) return 0xff0000 + zielenPlus;
  if ( i == 2 ) return 0xff00;
  if ( i == 0 ) return 0xffff;

  return 0xffff00;
}

void perspektywa(unsigned int *bm, int bx, int by, double xe, double ye) {
  double i, j, BAP, fodi;
  unsigned rgbKrok1;
  for(i = 0; i < X1; ++i) {
    BAP = BPdoAP(i);
    fodi = f(i);
    for(j = -BAP/2; j < BAP/2; ++j) {
          P.rysujPunkt(xe + i, ye + j, bm[((int)(rozciagnij(j,BAP)))*by         + ((int)fodi)]);
          rgbKrok1 = rgbKrok( ((int)j) % 3 );
	  // ten if nizej to bad coding
          if ( rgbKrok1 == 0xff0000 || rgbKrok1 == 0xff7f00 ) P.prostokat(RX/2 - BX/2 + ((int)4.0*fodi)-1, 10 + ((int)(4.0*rozciagnij(j,BAP)))-1, 3, 3, rgbKrok1 );
    }
//        P.rysujPunkt(xe + i, ye + j, bm[((int)(rozciagnij(j,BAP)))*((by - 1)) + ((int)fodi)]);
  }
}

SDL_Color tloCzcionki = { 0xff, 0xff, 0xff, 0};

#define ZOOM (5)
#define ZOOM_X (67)
#define ZOOM_Y (56)

void zoom(void) {
  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0,0,0,16);
  P.forecol = &tloCzcionki;
  while(1) {
    K.odswiez();
    P.prostokat(10,10,30,30,0xffffff);
    P.tekst2(10,10,"%d",&K.mysz.x);

    for(int i=0; i<ZOOM_X; ++i)
      for(int j=0; j<ZOOM_Y; ++j)
         P.prostokat(100 + i*ZOOM, 250 + j*ZOOM, ZOOM-1, ZOOM-1, P.KolorPunktu(K.mysz.x+i, K.mysz.y+j)); 
    P.odswiez();
    //K.sprawdzIWyjdzGdyKlawisz();
    K.wyjdzGdyKlawisz(SDLK_ESCAPE);
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
    
  perspektywa(bmapa, BX, BY, 20.0, 200.0);
  
  P.odswiez();
//  K.czekajNaKlawisz();
  zoom();
}
