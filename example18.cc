#define _ALE_ZLY_STYL_BIBLIOTEK_

#include <stdlib.h>

#include "grafika1.cc"

#define RX (1350)
#define RY (700)

Projektor P(RX, RY);
Klawiatura K;

int main(int argc, char** argv) {
  P.czysc(0xffffff);
  int i = 10000, x0, y0, dx, dy, r, g, b, pen;
  while(i) {
  	x0 = RX * random() / RAND_MAX;
  	y0 = RY * random() / RAND_MAX;
  	dx = -200 + 400 * random() / RAND_MAX;
  	dy = -200 + 400 * random() / RAND_MAX;
  	r = 0xff * random() / RAND_MAX;
  	g = 0xff * random() / RAND_MAX;
  	b = 0xff * random() / RAND_MAX;
  	pen = 4 * 71 * random() / RAND_MAX;
  	
  	P.pisak(pen);
  	P.linia(x0,y0,x0+dx,y0+dy,(r<<16)|(g<<8)|b);
  	P.odswiez();
  	i--;
  	if((i % 100) == 0)printf("%d\n",i);  	
  }
  K.czekajNaKlawisz();
}
