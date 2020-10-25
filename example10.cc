#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika.cc"

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

int main(int argc, char** argv) {
  P.czysc(0xffffff);

#define LESS_CLIPPING (10)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

  P.pisak(10);
  for(int a3=60;a3<360;a3+=360/5)
    P.elipsa3(RY/3+40, RY/2, RY/3, RY/6, 0, 360, a3, 0xff0000);

  P.pisak(3);
  for(int r=35;r<=100;r+=5) {
    P.elipsa3(RX-RY/3-150, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,0xff00);
    P.elipsa3(RX-RY/3-150, RY/2, 3*r, 3*r, 0, 360, 0,0xffff);
  }  
  P.Linia2(60,60,RX-60,RY-60,0xff,11);
  
  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
