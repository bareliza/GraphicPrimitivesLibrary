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
#define PEN  (22.0)
#define PEN2 (PEN / 2.0)
  
#define O1_R0 (100)
#define O1_R (RY/2-50)
#define O1_R1 (RY/2-50)
#define O1_X (RX/2)
#define O1_Y (RY/2)
  
  P.pisak(PEN);
  double a3rad, a4, a4rad, D_R, D_RX, D_RY;
  unsigned int COLOR;
  //                                  .__
  /*    _ _ _              .__        | /    \
       /--__/_ _ . ...  _. |  --__    |/alfa3 )
      /    /--__/  ...  _| |______--__/________.
     /    /    /                     /|--_alfa4|\_ _\ sin(alfa4) / PEN2*cos
    /    /    / r = r - /  ........./<|....--__|/   /
   /    /    /         /  ........./__|........
       /    /            ........./...|.......
           /            ........./....|......
                       ........./alfa5|.....

 /      "<"^2 + sin(a4)^2 = dr^2
 \      dr / "<" = PEN2 / sin(a4)

       "<" = PEN2 * dr / sin(a4)


        ( PEN2^2 * dr^2 / sin(a4)^2 ) + sin(a4)^2 = dr^2
         
         dr^2 = c1 * dr^2 + sin(a4)^2
         dr^2 * (1-c1) = sin^2(a4)
         dr = sin(a4) / sqrt(1-c1) = sin(a4) / sqrt( 1-PEN2^2/sin^2(a4) )

---------------------------------

 /      "<"^2 + PEN2*cos(a4)^2 = dr^2
 \      dr / "<" = PEN2 / PEN2*cos(a4)

       "<" = dr / cos(a4)


        ( dr^2 / cos(a4)^2 ) + cos(a4)^2 = dr^2
         
         dr^2 = c1 * dr^2 + cos(a4)^2
         dr^2 * (1-c1) = cos^2(a4)
         dr = cos(a4) / sqrt(1-c1) = cos(a4) / sqrt( 1-1/cos^2(a4) )

	 Jakis blad... (dr = PEN2 * ... ? czy dr = ... ?)
 
   */
  for(double a3=60;a3<360;a3+=360/13) {
    a3rad = M_PI*a3/180.0;
    /*
      D_RX = PEN2 * cos(a4rad);
      D_RY = PEN2 * sin(a4rad);
    */
    a4 = a3 - 90;
    a4rad = M_PI*a4/180.0;

    if(cos(a4rad)<1) D_R = PEN2 * cos(a4rad) / sqrt( 1 - 1/(cos(a4rad)*cos(a4rad)) );
    else D_R = 0;
    //D_R = 0;
    printf("%F\n",D_R);
    P.pisak(PEN);
    P.linia(O1_X + O1_R0 * sin(a3rad),
	    O1_Y + O1_R0 * cos(a3rad),
	    O1_X + O1_R * sin(a3rad),
	    O1_Y + O1_R * cos(a3rad),
	    0x0);
    P.linia(O1_X + O1_R0 * sin(a3rad),
	    O1_Y + O1_R0 * cos(a3rad),
	    O1_X + (O1_R - D_R) * sin(a3rad),
	    O1_Y + (O1_R - D_R) * cos(a3rad),
	    0x8000);
    P.pisak(1);
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

  /*
  P.pisak(PEN-8);
  for(int r=35;r<=100;r+=STEP) {
    P.elipsa3(RX-RY/3-150, RY/2, 3*r, 3*r, 0, 360, 0,0x60ff, 1);

    P.pisak(PEN);
    P.elipsa3(RX-RY/3-150, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,0xffffff, r>70);
    P.pisak(PEN-4);
    P.elipsa3(RX-RY/3-150, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,r<=70?0xffffa0:0xff9b00, r>70);
    P.pisak(PEN-8);
    P.elipsa3(RX-RY/3-150, RY/2, 3*r-(90+60-r-r/2), 3*r, 0, 360, 0,r<=70?0xffffff:0x00, r>70);
  } 
*/  
  // P.Linia2(60,60,RX-60,RY-60,0xff,11);
  
  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
