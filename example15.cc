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

#define STEP (7)
#define PEN  (42.0)
#define PEN2 (PEN / 2.0)
  
#define O1_R0 (250)
#define O1_R (RY/2-20)
#define O1_R1 (RY/2-20)
#define O1_X (RX/2)
#define O1_Y (RY/2)
  
  P.pisak(PEN);
  double a3rad, a4, a4rad, a5, a5rad, D_R, D_RX, D_RY, d, x;
  unsigned int COLOR, COLOR1, COLOR2;
  for(double a3=00;a3<360;a3+=360/30) {
    a3rad = M_PI*a3/180.0;
    /*
      D_RX = PEN2 * cos(a4rad);
      D_RY = PEN2 * sin(a4rad);
    */
    a4 = a3 - 90;
    a4rad = M_PI*a4/180.0;
    a5 = 90 - a3;
    a5rad = M_PI*a5/180.0;
    
    // if( 1 ) { // a3 >= 0 && a3 <= 45 ) {
    if((a3 > 45 && a3 <=135) || (a3 > 45+180 && a3 <= 135+180)) {
      x = abs(PEN / cos(a5rad));
      // d = 0;
      COLOR1 = 0xff8080;
      COLOR2 = COLOR1;
    } else {
      x = abs(PEN / cos(a3rad)); // f(0) = 1/2; f(45) = sqrt(2)/2 
      // d = 0; // x / (2 * cos(a3rad));
      COLOR1 = 0x8080ff;
      COLOR2 = COLOR1;
    }
    if(a3 > 45 && a3 <= 90) {
      d = x * cos(a3rad) / 2;
      COLOR1 = 0x80ff80;
      COLOR2 = 0xffc080;
    } else {
      d = 0;
    }
    //if(cos(a4rad)<1) D_R = PEN2 * cos(a4rad) / sqrt( 1 - 1/(cos(a4rad)*cos(a4rad)) );
    //else D_R = 0;
    D_R = 0;
    printf("%F\n",D_R);
    P.pisak(x); // PEN);
    P.pisak(PEN); // x);
    P.pisak(((int)(PEN)) >> 1); // x);

    P.linia1(O1_X + ( O1_R0 - d ) * sin(a3rad),
	     O1_Y + ( O1_R0 - d ) * cos(a3rad),
	     O1_X + ( O1_R + d /* - D_R */) * sin(a3rad),
	     O1_Y + ( O1_R + d /* - D_R */) * cos(a3rad),
	     COLOR1);
    P.linia1(O1_X + ( O1_R0 + d ) * sin(a3rad),
	     O1_Y + ( O1_R0 + d ) * cos(a3rad),
	     O1_X + ( O1_R - d /* - D_R */) * sin(a3rad),
	     O1_Y + ( O1_R - d /* - D_R */) * cos(a3rad),
	     COLOR2);
    P.pisak(1);
    P.linia1(O1_X + O1_R0 * sin(a3rad),
	     O1_Y + O1_R0 * cos(a3rad),
	     O1_X + O1_R1 * sin(a3rad),
	     O1_Y + O1_R1 * cos(a3rad),
	     0xff00ff);

    if(abs(sin(a3rad)) > abs(cos(a3rad))) COLOR = 0xff;
    else COLOR = 0xff0000;
    P.linia1(O1_X + O1_R1 * sin(a3rad) - PEN2 * sin(a4rad),
	     O1_Y + O1_R1 * cos(a3rad) - PEN2 * cos(a4rad),
	     O1_X + O1_R1 * sin(a3rad) + PEN2 * sin(a4rad),
	     O1_Y + O1_R1 * cos(a3rad) + PEN2 * cos(a4rad),
	     COLOR);
    P.linia1(O1_X + O1_R0 * sin(a3rad) - PEN2 * sin(a4rad),
	     O1_Y + O1_R0 * cos(a3rad) - PEN2 * cos(a4rad),
	     O1_X + O1_R0 * sin(a3rad) + PEN2 * sin(a4rad),
	     O1_Y + O1_R0 * cos(a3rad) + PEN2 * cos(a4rad),
	     COLOR);

    COLOR1=COLOR2=0xffffff;
    P.pisak(x-4); // PEN);
    P.linia (O1_X + ( O1_R0 - d ) * sin(a3rad),
	     O1_Y + ( O1_R0 - d ) * cos(a3rad),
	     O1_X + ( O1_R + d /* - D_R */) * sin(a3rad),
	     O1_Y + ( O1_R + d /* - D_R */) * cos(a3rad),
	     COLOR1);
    P.linia (O1_X + ( O1_R0 + d ) * sin(a3rad),
	     O1_Y + ( O1_R0 + d ) * cos(a3rad),
	     O1_X + ( O1_R - d /* - D_R */) * sin(a3rad),
	     O1_Y + ( O1_R - d /* - D_R */) * cos(a3rad),
	     COLOR2);
    P.pisak(1);
    P.linia (O1_X + O1_R0 * sin(a3rad),
	     O1_Y + O1_R0 * cos(a3rad),
	     O1_X + O1_R1 * sin(a3rad),
	     O1_Y + O1_R1 * cos(a3rad),
	     0xff00ff);

    if(abs(sin(a3rad)) > abs(cos(a3rad))) COLOR = 0xff;
    else COLOR = 0xff0000;
    COLOR=0xffffff;
    P.linia (O1_X + O1_R1 * sin(a3rad) - PEN2 * sin(a4rad),
	     O1_Y + O1_R1 * cos(a3rad) - PEN2 * cos(a4rad),
	     O1_X + O1_R1 * sin(a3rad) + PEN2 * sin(a4rad),
	     O1_Y + O1_R1 * cos(a3rad) + PEN2 * cos(a4rad),
	     COLOR);
    P.linia (O1_X + O1_R0 * sin(a3rad) - PEN2 * sin(a4rad),
	     O1_Y + O1_R0 * cos(a3rad) - PEN2 * cos(a4rad),
	     O1_X + O1_R0 * sin(a3rad) + PEN2 * sin(a4rad),
	     O1_Y + O1_R0 * cos(a3rad) + PEN2 * cos(a4rad),
	     COLOR);

  }      

  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
