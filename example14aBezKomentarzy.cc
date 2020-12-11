#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#include <iostream>

#include "example-cfg1.hh"


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
  
  
int main(int argc, char** argv) {
  P.czysc(0xffffff);

#define LESS_CLIPPING (2)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

// #define debug11

  int O1_X,O1_Y,a3start,a3stop;
  O1_X = O1_Xbase;
  O1_Y = O1_Ybase;
  P.pisak(PEN);
  double a3rad, a4, a4rad, a5, a5rad, D_R, D_RX, D_RY, d, x;
  unsigned int COLOR, COLOR1, COLOR2;
  // dla a3=2 jest slabo, już lepiej
  // dla a3=4 jest slabo, też już lepiej
  if(argc>1)a3start = atoi(argv[1]);
  else a3start=0;
  if(argc>2)a3stop = atoi(argv[2]);
  else a3stop=a3start;
  for(int start =a3start; start<=a3stop; start+=1) { 
  for(double a3=start;a3<360;a3+=360/30) {
    a3rad = M_PI*a3/180.0;
    a4 = a3 - 90;
    a4rad = M_PI*a4/180.0;
    a5 = 90 - a3;
    a5rad = M_PI*a5/180.0;
    
    if((a3 > 45 && a3 <=135) || (a3 > 45+180 && a3 <= 135+180)) {
      COLOR1 = 0xff8080;
      COLOR2 = COLOR1;
    } else {
      COLOR1 = 0x8080ff;
      COLOR2 = COLOR1;
    }

    if(a3 > 45 && a3 <= 90) {
      COLOR1 = 0x80ff80-(0xff00*((int)a3))/90;
      COLOR2 = 0xffc080-(0xff0000*((int)a3))/90;
    }
    
    d = 0;
    P.pisak(PEN);     
    P.linia(O1_X + ( O1_R0 - d ) * sin(a3rad),
	    O1_Y + ( O1_R0 - d ) * cos(a3rad),
	    O1_X + ( O1_R + d /* - D_R */) * sin(a3rad),
	    O1_Y + ( O1_R + d /* - D_R */) * cos(a3rad),
	    COLOR1, 20, argc>3);
    if(a3>45 && a3 <=90) printf("kat a3 = %d; ", (int)(a3) );
    P.linia(O1_X + ( O1_R0 + d ) * sin(a3rad),
	    O1_Y + ( O1_R0 + d ) * cos(a3rad),
	    O1_X + ( O1_R - d /* - D_R */) * sin(a3rad),
	    O1_Y + ( O1_R - d /* - D_R */) * cos(a3rad),
	    COLOR2, 5, argc>3);
    P.pisak(0);
    P.linia(O1_X + O1_R0 * sin(a3rad),
	    O1_Y + O1_R0 * cos(a3rad),
	    O1_X + O1_R1 * sin(a3rad),
	    O1_Y + O1_R1 * cos(a3rad),
	    0xff00ff);

    if(abs(sin(a3rad)) > abs(cos(a3rad))) COLOR = 0xff;
    else COLOR = 0xff0000;
    P.linia(O1_X + O1_R1 * sin(a3rad) - PEN2 * sin(a4rad),
	    O1_Y + O1_R1 * cos(a3rad) - PEN2 * cos(a4rad),
	    O1_X + O1_R1 * sin(a3rad) + PEN2 * sin(a4rad),
	    O1_Y + O1_R1 * cos(a3rad) + PEN2 * cos(a4rad),
	    COLOR);
    P.linia(O1_X + O1_R0 * sin(a3rad) - PEN2 * sin(a4rad),
	    O1_Y + O1_R0 * cos(a3rad) - PEN2 * cos(a4rad),
	    O1_X + O1_R0 * sin(a3rad) + PEN2 * sin(a4rad),
	    O1_Y + O1_R0 * cos(a3rad) + PEN2 * cos(a4rad),
	    COLOR);
  }
  O1_X-=0;
  O1_Y+=0;      
  }
  
  P.odswiez();
  if(argc<=5) K.czekajNaKlawisz();
}
