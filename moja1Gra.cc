#define _ALE_ZLY_STYL_BIBLIOTEK_
#include "grafika1.cc"

Projektor P(650,650);
Klawiatura K;

int ostatniX, ostatniY;
int ostatniKolor;

void linia(int x0,int y0, int x1, int y1, unsigned int kolor)
{
  P.linia(x0,y0,x1,y1,kolor);
  ostatniX = x1;
  ostatniY = y1;
  ostatniKolor = kolor;
}

void liniaDo(int x, int y, unsigned int kolor)
{
  P.linia(ostatniX, ostatniY, x, y, ostatniKolor);
  ostatniX = x;
  ostatniY = y;
  ostatniKolor = kolor;
}

void liniaDo(int x, int y)
{
  liniaDo(x,y,ostatniKolor);
}


void wypelnionaElipsa(int x, int y, int rx, int ry, double a0, double a1, double a2, unsigned int kolor) {
	int pen1;
	pen1 = P.pioro;	
	P.pisak(8);
	for(int i=1;i<=ry-3;i+=1) {
		P.elipsa3(x,y,rx-4,i,a0,a1,a2,kolor);	
	}
	P.pisak(pen1);
}

int main(int argc, char **argv){
  P.czysc(0xffffff);
  P.wczytajBMP("20201214_102131-Postac-1a1.bmp");
  P.linia(10,10,640,640,0x600060);
  P.pisak(0);

  for(int i=0;i<P.wymiar.y;i+=10)
	P.linia(0,i,P.wymiar.x,i,0xa000);
  for(int j=0;j<P.wymiar.x;j+=10)
	P.linia(j,0,j,P.wymiar.x,0xa000);

  for(int i=0;i<P.wymiar.y;i+=50)
	P.linia(0,i,P.wymiar.x,i,0x80);
  for(int j=0;j<P.wymiar.x;j+=50)
	P.linia(j,0,j,P.wymiar.x,0x80);

  for(int i=0;i<P.wymiar.y;i+=100)
	P.linia(0,i,P.wymiar.x,i,0xa00000);
  for(int j=0;j<P.wymiar.x;j+=100)
	P.linia(j,0,j,P.wymiar.x,0xa00000);

  P.rysujPunkt4(60+90-2,260+105+1-3,0xc04000,27);
//  P.elipsa3(150-2,365-3,29,90,0,180,170,0x602000);	  
  wypelnionaElipsa(150-2,365-3,30-3,92+3,0,180,169,0xa02000);	  
  int Xkolano1, Ykolano1;
  Xkolano1 = 150-2;
  Ykolano1 = 365-3;
  //wypelnionaElipsa(Xkolano1-41,Ykolano1+52,28,70,0,360,55,0xd06000);
  //P.elipsa3(Xkolano1-41+2,Ykolano1+52-1,27,73,0,360,55,0xd06000);
  wypelnionaElipsa(Xkolano1-41+2,Ykolano1+52-1,27,73+4,0,360,55,0xd06000);

  // stopa2
  P.elipsa3(259,455,29,42,0,360,0,0xff00);
  wypelnionaElipsa(259,455,29,42,0,360,0,0xc00060);
  // kolano2
  P.elipsa3(258,445,30,99,0,180,171,0xff00);
  wypelnionaElipsa(258,445,30,99,0,180,171,0xa00030);
  
  // udo2
  P.pisak(50);
  P.linia(202,302,234,344,0x4010);
  P.pisak(46);
  P.linia(202,302,234,344,0xd00070);
  
  // tors
  P.pisak(56);
  // D,C
  linia(155,257,193,257,0xa04080);
  //liniaDo(193,257);
  // B
  liniaDo(195,129);
  // A
  liniaDo(145,134);
  // D
  liniaDo(155,257);

  // D,B:
  P.pisak(46);
  linia(155,257,195,129,0); //0x302010);
  // A+(5,5):
  //P.rysujPunkt4(145,134,0x0,56>>1);
  wypelnionaElipsa(150,139,(56+6)>>1,(56+6)>>1,0,180,110,0); // 0x302010);
  // C+(2,2):
  wypelnionaElipsa(195,259,(56-4)>>1,(56-4)>>1,0,180,290,0); // 0x302010);
  
  //wypelnionaElipsa(145,134,17,26,0,360,30,0); // 0x302010);

  // glowa
  P.rysujPunkt4(171,66,0x802040,37);

  // reka1
  P.rysujPunkt4(65,177,0xff00,30);
  wypelnionaElipsa(65,177,28,65,0,180,31.5,0xa4080);
  wypelnionaElipsa(65+8+3,177-8,25,60,0,180,180+31.5+10,0xa4080);

  // reka2
  punkt reka2(300, 200);
  reka2 = reka2 - punkt(18, 15);
  punkt rk2=reka2;
  punkt rk2piszczel = reka2 + punkt(8+3, 8);
  P.rysujPunkt4(reka2.x,reka2.y,0xff00,28);
  wypelnionaElipsa(rk2.x-5-5, rk2.y-5, 27,80,0,180,41.5+90+15,0xa30a0);
  wypelnionaElipsa(rk2piszczel.x, rk2piszczel.y, 26,65,0,180,180+41.5+10+90,0xa30a0);

  
  P.odswiez();
  K.czekajNaKlawisz();
}

