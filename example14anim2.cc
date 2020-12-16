#define _ALE_ZLY_STYL_BIBLIOTEK_
#define KLIPOWANIE

#include "grafika1.cc"

#include <iostream>

#include "example-cfg1.hh"

#include <unistd.h>

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

#define STEP (7)

#define STEP (7)
#define PEN  (42.0)
#define PEN2 (PEN / 2.0)
  
#define O1_R0 (230)
#define O1_R (RY/2-35)
#define O1_R1 (RY/2-35)
#define O1_Xbase (RX/2)
#define O1_Ybase (RY/2)
  
#define deg2rad(a)  (M_PI*a/180)  
int main(int argc, char** argv) {
  P.czysc(0xffffff);

#define LESS_CLIPPING (2)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

// #define debug11

  int O1_X,O1_Y,a3start,a3stop,one2speed;
  unsigned int kolor;
  O1_X = O1_Xbase;
  O1_Y = O1_Ybase;
  P.pisak(PEN);
  double a3rad, a4, a4rad, a5, a5rad, D_R, D_RX, D_RY, d, x;
  unsigned int COLOR, COLOR1, COLOR2;
  // dla a3=2 jest slabo, już lepiej
  // dla a3=4 jest slabo, też już lepiej
  if(argc>1)kolor = strtol(argv[1], NULL, 16);
  else kolor=0x7f00ff;
  if(argc>2)a3start = atoi(argv[2]);
  else a3start=0;
  if(argc>3)a3stop = atoi(argv[3]);
  else a3stop=45;
  if(argc>4)one2speed = atoi(argv[4]);
  else one2speed = 10000;// 10ms
  //double a3=0.0;
  for(double a3=a3start;a3<a3stop;a3+=0.10) {
        P.pisak(8);
#define R1 (0)
        P.czysc(0xffffff);
        for(int i=0;i<=8;i++)
	  P.elipsa3(RX/2+R1*cos(deg2rad(a3)), RY/2+R1*sin(deg2rad(a3)), 4*i, RY/3+4*i, 0, 180, a3, 
                  kolor+15*i*0x10000+15*i*0x100-0x1*15*i/* i*0x100 */ /* PINK+R1*i+G1*i-B1*i i:0x4..0x20 */); 
                  // 4*i: 0x04..0x20     
        P.odswiez();
        usleep(one2speed);
  }
  P.odswiez();
  if(argc<=6) K.czekajNaKlawisz();
}
