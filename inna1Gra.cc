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

void rysuj(unsigned int *bm, int bx, int by, int xe, int ye) {
  int i, j;
  for(i = 0; i < bx; ++i)
    for(j = 0; j < by; ++j)
      P.rysujPunkt(xe + i, ye + j, bm[j * by + i]); 
}

int main(int argc, char** argv) {
  P.czysc(0x0060ff);
  P.linia(10,10,90,90,0xff0000);
 
  czysc(bmapa, BX, BY, 0xff00ff);
  paski(bmapa, BX, BY, 8);
  rysuj(bmapa, BX, BY, RX/2 - BX/2, RY/2 - BY/2);
  
  P.odswiez();
  K.czekajNaKlawisz();
}
