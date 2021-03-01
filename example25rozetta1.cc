#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

#include <iostream>

#include "example-cfg2.hh"

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

punktR funkcjaR2wR2(punktR p)
{
  punktR pOut;
  // r
  double r = sqrt(p.x*p.x+p.y*p.y);
  pOut.y = p.y;
  pOut.x = p.x * r;

  printf("Px = %f, Py = %f, r = %f ", p.x, p.y, r);
  printf("POUTx = %f, POUTy = %f ", pOut.x, pOut.y);
  return pOut;
}

//  RX/2, RY/2 -> 0,0
//
//  RX/2 - RY/2 + 20, RY/2 -> -1, 0
//  RX/2 + RY/2 - 20, RY/2 ->  1, 0
//  RX/2, RY - 20 -> 0, 1
//  RX/2, 20      -> 0, -1  
punkt fR2wR2(punkt p0)
{
  punktR p(p0.x, p0.y);
  p = p - punktR(RX/2, RY/2);
  p.x = p.x / (RY/2 - 20); 
  p.y = p.y / (RY/2 - 20);

  punktR p1 = funkcjaR2wR2(p);

  p1.x = p1.x * (RY/2 - 20);
  p1.y = p1.y * (RY/2 - 20);
  p1 = p1 + punktR(RX/2, RY/2);

  punkt p2 = punkt(p1.x, p1.y);

  printf("P0x = %d, P0y = %d ", p0.x, p0.y);
  printf("P2x = %d, P2y = %d \n", p2.x, p2.y);
  return p2; 
}

int DELTA1=0;
int KROPKI1=1;
#define KROKOW (80.0)
void okrag(int ox, int oy, int r, unsigned int kolor)
{
	for(double i=1.0;i<=KROKOW;++i) {
		punkt p0(ox+r*sin(i*2.0*M_PI/KROKOW), oy+r*cos(i*2.0*M_PI/KROKOW));
		punkt p1(ox+r*sin((i+1)*2.0*M_PI/KROKOW), oy+r*cos((i+1)*2.0*M_PI/KROKOW));
		P.linia(fR2wR2(p0),fR2wR2(p1),kolor, DELTA1, KROPKI1);	
	}
} 

punktR obroc(punktR o, punktR p, int obrot)
{
	punktR v = p - o;
	double r = sqrt(v.x*v.x + v.y*v.y);
	// v.x = v.x / r;
        // v.y = v.y / r;
        //v = v / r;
	double alfa0 = atan2(v.x, v.y);
	double alfa1 = alfa0 + 2.0*M_PI*obrot/360;
	v.x = o.x + r * sin(alfa1);
	v.y = o.y + r * cos(alfa1);
        //v = v * r;

	punktR pOut(v.x, v.y);

	return pOut;
}

void elipsa(int ox, int oy, int rx, int ry, int obrot, unsigned int kolor)
{
	punktR O(ox,oy);
	for(double i=1.0;i<=KROKOW;++i) {
		punktR p0(ox+rx*sin(i*2.0*M_PI/KROKOW), oy+ry*cos(i*2.0*M_PI/KROKOW));
		punktR p1(ox+rx*sin((i+1)*2.0*M_PI/KROKOW), oy+ry*cos((i+1)*2.0*M_PI/KROKOW));
		punktR p0obr = obroc(O, p0, obrot);
		punktR p1obr = obroc(O, p1, obrot);
		punkt p0obr1(p0obr.x, p0obr.y);		
		punkt p1obr1(p1obr.x, p1obr.y);		
//		P.linia(p0obr1,p1obr1,kolor);			
		P.linia(fR2wR2(p0obr1),fR2wR2(p1obr1),kolor,DELTA1,KROPKI1);	
	}
} 


int PISAKI[3] = {18, 14, 12};
int KOLORY[3] = {0x0000ff, 0xff0000, 0xffffff};

int main(int argc, char** argv) {
  P.czysc(0xdfdfdf); // ffffff);

#define LESS_CLIPPING (10)  
  P.xc0 = LESS_CLIPPING;
  P.xc1 = LESS_CLIPPING;
  P.yc0 = LESS_CLIPPING;
  P.yc1 = LESS_CLIPPING;

  //for(int a3=0;a3<350;a3+=360/9) {
  // int a3 = 0;
  // for(int dry = RY/2-40; dry >=0; dry -= 50) {
  //int dry = RY/4;
  //int dry = 3*RY/9; // Delta RY. DRY 
  //  for(int i=0;i<3;++i) {
  //  	P.pisak(PISAKI[i]);
  // 	P.mmm=1; 
  // 	P.elipsa3(RX/2, RY/2, RY/2-20-dry, RY/2-20, 0, 360, a3, KOLORY[i]);
    	// P.elipsa3(RX/2, RY/2, RY/2-20, RY/2-20-dry, 0, 360, a3, KOLORY[i]);
  //  }
  // }
  //}      
  P.pisak(18);
  unsigned int kolor = 0;//0xff00;
  unsigned int kolor1 = 0xffffff;//0xd0d0d0;
  int r = RY/2 - 30;
  for (int obrot = 0; obrot < 350;obrot += 360 / 5) { // , kolor -= 0xf00, kolor1 -= 0x40404) {
  //for (int r = RY/2 -20; r>150; r-=20, kolor -= 0xf00)
	DELTA1=0;
	KROPKI1=1;	
	P.pisak(80);
  	elipsa(RX/2,RY/2,r,r*100/150,obrot,kolor); 
	DELTA1=0;
	KROPKI1=1;	
	P.pisak(78);
  	elipsa(RX/2,RY/2,r,r*100/150,obrot,kolor1); 
  }
  
  int x, y;
  for (x = 50, y=50; x < RX - 100; x+=100,y+=35) {
	P.pisak(18);
	//P.linia(x,y,x+100,y+35,0xff00ff);
	P.pisak(12);
	//P.linia(x,y+100,x+100,y+135,0xffb0ff);
  }

  DELTA1=0;
  KROPKI1=1;
  P.pisak(12);
  //okrag (RX/2,RY/2,300,0xff00ff);
  P.pisak(8);
  DELTA1=1;
  KROPKI1=0;
  //okrag (RX/2,RY/2,300,0xffb0ff);

  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
  if(K.klawisz==SDLK_s) P.zapiszBMP("tiruriru.bmp");
}
