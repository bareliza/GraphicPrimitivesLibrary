#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#include <iostream>

#include "example-cfg.hh"

Projektor P(RX, RY);
Klawiatura K;

// (0,0) -> (0,0)
// (-1,0) -> (-1,0)
// (-.5,0) -> (-.75,0)

// (0,0) -> (0,0)
// (1,0) -> (1,0)
// (.5,0) -> (.75,0)

// ogolnie:
// kolo o promieniu:
//    0.5 w elipse (0.5, 0.5 + e=.25) e=.25 -> e=0 dla r=0.5 -> r=1
//    0.5 + d:=0.3 w elipse (
//    1   w elipse (1,   1)
// NARYSUJ TE ELIPSY.

punkt funkcjaR2wR2(punkt p0)
{
  punkt pOut;

  return pOut;
}

int PISAKI[3] = {18, 14, 10};
int KOLORY[3] = {0xff0000, 0x0000ff, 0x000000};

int main(int argc, char** argv) {
  P.czysc(0xffffff); // ffffff);

#define LESS_CLIPPING (10)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

  // for(int a3=60;a3<360;a3+=360/7) {
  int a3 = 0;
  for(int dry = RY/2-40; dry >=0; dry -= 50)
  //int dry = 3*RY/9; // Delta RY. DRY 
  {
    for(int i=0;i<3;++i) {
    	P.pisak(PISAKI[i]);
	P.mmm=1; 
   	P.elipsa3(RX/2, RY/2, RY/2-20-dry, RY/2-20, 0, 360, a3, KOLORY[i]);
    	P.elipsa3(RX/2, RY/2, RY/2-20, RY/2-20-dry, 0, 360, a3, KOLORY[i]);
    }
  }
  // }      
 
  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
