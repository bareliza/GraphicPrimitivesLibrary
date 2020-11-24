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
// sprawdzic dla PEN=56.0 i R0 = 280!
#define PEN  (48.0)

#ifdef debug11
#define PEN (56.0)
#endif

#define PEN2 (PEN / 2.0)
  
#define O1_R0 (245)

#ifdef debug11
#define O1_R0 (280)
#endif

#define O1_R (RY/2-50)
#define O1_R1 (RY/2-50)
#define O1_Xbase (RX/2)
#define O1_Ybase (RY/2)

#define STEP (7)
#define PEN  (42.0)
#define PEN2 (PEN / 2.0)
  
#define O1_R0 (230)
#define O1_R (RY/2-5)
#define O1_R1 (RY/2-5)
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
      COLOR1 = 0x80ff80-(0xff00*((int)a3))/90;
      COLOR2 = 0xffc080-(0xff0000*((int)a3))/90;
    } else {
      if (a3 >= 0 && a3 <= 45) { 
        d = x * cos(M_PI/2-a3rad) / 2;    
      } else {
        if (a3 > 90 && a3 <= 135) {
          d = x * cos(a3rad) / 2;
        } else {
          if (a3 > 135 && a3 <= 180) {
            d = x * cos(M_PI/2 - a3rad) / 2;
          } else {      
            if (a3 > 180 && a3 <= 225) {
              d = - x * cos(M_PI/2-a3rad) / 2;
            } else {
              if (a3 > 225 && a3 <= 270) {
                d = - x * cos(a3rad) / 2;
              } else {  
                if (a3 > 270 && a3 <= 315) {
                  d = x * cos(a3rad) / 2;
                } else { // 315 .. 360
                  d = x * cos(M_PI/2-a3rad) / 2;
                }
              }
            }
          }
        }
      }
    }

    printf("K@AT a3 = %d; ", (int)(a3) );
    d = 0;
    //if(cos(a4rad)<1) D_R = PEN2 * cos(a4rad) / sqrt( 1 - 1/(cos(a4rad)*cos(a4rad)) );
    //else D_R = 0;
    D_R = 0;
    // printf("%F\n",D_R);
    printf("%d,%d@",(int)d,(int)x);
    P.pisak(x); // PEN);
    P.pisak(PEN); // PEN);     
    /*
    P.linia(O1_X + O1_R0 * sin(a3rad),
	    O1_Y + O1_R0 * cos(a3rad),
	    O1_X + O1_R * sin(a3rad),
	    O1_Y + O1_R * cos(a3rad),
	    0x0); */
    P.linia(O1_X + ( O1_R0 - d ) * sin(a3rad),
	    O1_Y + ( O1_R0 - d ) * cos(a3rad),
	    O1_X + ( O1_R + d /* - D_R */) * sin(a3rad),
	    O1_Y + ( O1_R + d /* - D_R */) * cos(a3rad),
	    COLOR1);
    if(a3>45 && a3 <=90) printf("kat a3 = %d; ", (int)(a3) );
    P.linia(O1_X + ( O1_R0 + d ) * sin(a3rad),
	    O1_Y + ( O1_R0 + d ) * cos(a3rad),
	    O1_X + ( O1_R - d /* - D_R */) * sin(a3rad),
	    O1_Y + ( O1_R - d /* - D_R */) * cos(a3rad),
	    COLOR2);
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
