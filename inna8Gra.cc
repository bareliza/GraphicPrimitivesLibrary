#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#define RX (1200)
#define RY (700)

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
	a = XB / ( X1*X1*( 1.0 + 2.0*AP / ( BP*( 1.0 - AP / BP ) ) ) );
	b = 2.0*a*X1*AP / ( BP*( 1.0 - AP / BP ) );
}

double f(double x) {
//	printf("x = %3.3f f(x) = %3.3f", x, a*x*x + b*x);  

	return a*x*x + b*x + 0.5;
}

double BPdoAP(double x)
{
	return x*(AP-BP)/(X1-1) + BP + 0.5;
}

double rozciagnij(double j, double BAP) {
  return ((double)(BY-1.0))*(j+BAP/2)/BAP + 0.5; 
//    return ((double)(BY    ))*(j+BAP/2)/BAP + 0.5; 
}

void rysuj1(unsigned int *bm, int bx, int by, int xe, int ye, int z) {
  double i, j;
  double fodi;
  for(i = 0; i < X1/*bx*/; ++i)
    for(j = 0; j < by; ++j) {
      fodi = f(i);      
      //if ( j == 0 ) printf( "i == %3.1f, f(i) == %3.3f\n", i, fodi );
      P.prostokat(xe + z*i, ye + z*j, z-1, z-1, bm[((int)j) * by + ((int)fodi)]);
    } 
}


unsigned rgbKrok(int i)
{
  unsigned zielenPlus;
  
  zielenPlus = 0x0;
  if ( i < 0 ) {
    i = -i;
    zielenPlus = 0xff00;
  }
  if ( i == 1 ) return zielenPlus ? zielenPlus : 0xff0000;
  if ( i == 2 ) return 0xf100;
  if ( i == 0 ) return 0xffff;

  return 0xffff00;
}

#define ZOOM (5)

#define ZOOM_X (67)
#define ZOOM_Y (56)

void perspektywa(unsigned int *bm, int bx, int by, double xe, double ye) {
  double i1, i, j, BAP, BAPi, fodi1, fodi, rozc1;
  unsigned rgbKrok1;
  double rozc[2*(int)(BP>AP?BP:AP)][8];
  int MBPAP;
  MBPAP = (int)(BP>AP?BP:AP);
  
  for(i1 = 2; i1 < X1 + 2; ++i1) {
    BAP = BPdoAP(i1);
    fodi1 = f(i1); // skrocenie perspektywiczne
    i = i1 - 2;
    BAPi = BPdoAP(i);
    if ( i > X1 - 3 ) BAP = BAPi;
    fodi = f(i);
    for(j = -BAPi/2; j < BAPi/2; ++j) {
          rozc[(int)(MBPAP+j)][((int)i1)&3] = ((int)(rozciagnij(j,BAP)));
          if ( i < 3 || i > X1 - 3 || j < -BAPi/2 + 3 || j > BAPi/2 - 3 ) rozc1 = ((int)(rozciagnij(j,BAPi)));
          else 
              // A ja bym chcial, zeby dla i = n to byla srednia 
              // nie z: i-3 i-2 i-1 i
              // ale z: i-2 i-1 i   i+1
              // lub z! i-1 i   i+1 i+2
              rozc1 = (rozc[(int)(MBPAP+j)][0]+
                       rozc[(int)(MBPAP+j)][1]+
                       rozc[(int)(MBPAP+j)][2]+
                       rozc[(int)(MBPAP+j)][3]
                       ) / 4.0;
                       /*
                       +
                       rozc[(int)(MBPAP+j)][4]+
                       rozc[(int)(MBPAP+j)][5]+
                       rozc[(int)(MBPAP+j)][6]+
                       rozc[(int)(MBPAP+j)][7]
                       ) / 8.0; */ 
          P.rysujPunkt(xe + i, ye + j, bm[((int)(rozc1))*by         + ((int)fodi)]);
          rgbKrok1 = rgbKrok( ((int)j) % 3 );
	  if ( ((int)j) == 1 ) {
                  rgbKrok1 = 0xffff00;
                  printf( "i == %3.1f, rozciagnij(j,BAP) == %3.3f\n", i, rozc1);//rozciagnij(j,BAP) );
	  }
	  // ten if nizej to bad coding
          if ( rgbKrok1 == 0xff0000 || rgbKrok1 == 0xff7f00 || rgbKrok1 == 0xffff00 || rgbKrok1 == 0xff00 )
                  P.prostokat(RX/2 - BX/2 + ((int)ZOOM*i/*fodi*/)-1, 10 + ((int)(ZOOM*rozc1))-1, ZOOM, ZOOM-2, rgbKrok1 );
    }
//        P.rysujPunkt(xe + i, ye + j, bm[((int)(rozciagnij(j,BAP)))*((by - 1)) + ((int)fodi)]);
  }
}

SDL_Color tloCzcionki = { 0xff, 0xff, 0xff, 0};

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
  
  X1 = 100;
  XB = BX;
  AP = 50;
  BP = 300;

  obliczWspolczynniki();
  
  rysuj1(bmapa, BX, BY, RX/2 - BX/2, 10, ZOOM); // RY/2 - BY/2);
 
  for(double i = 0; i < X1; ++i)
    P.rysujPunkt( RX/2 - BX/2 + f(i), 10, 0xff00);
    
  perspektywa(bmapa, BX, BY, 20.0, 200.0);
  
  P.odswiez();
//  K.czekajNaKlawisz();
  zoom();
}
