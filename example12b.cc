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

int main(int argc, char** argv) {
  P.czysc(0xffffff);

#define LESS_CLIPPING (10)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

  for(double a3=0.0/*60.0*/;a3<360.0;a3+=360.0/5.0) {
    P.pisak(22);
    P.elipsa3(RY/4+70, RY/2, RY/3, RY/7, 0, 360, a3, 0xff0000);
    P.pisak(12);
    P.elipsa3(RY/4+70, RY/2, RY/3, RY/7, 0, 360, a3, 0x03f1f);
  }      

  P.pisak(8);
  for(int r=35;r<=100;r+=5) {
    P.elipsa3(RX-RY/3-120, RY/2, 3*r, 3*r, 0, 360, 0,0x60ff);
    P.pisak(16);
    P.elipsa3(RX-RY/3-120, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,0xffffff, r>70);
    P.pisak(12);
    P.elipsa3(RX-RY/3-120, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,r<=70?0xffa080:0xff9b00, r>70);
    P.pisak(8);
    P.elipsa3(RX-RY/3-120, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,r<=70?0xffffff:0x00, r>70);
 }  
  
  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
