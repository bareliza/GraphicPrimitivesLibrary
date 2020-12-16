#define _ALE_ZLY_STYL_BIBLIOTEK_
#include "grafika1.cc"

Projektor P(650,650);
Klawiatura K;

int ostatniX, ostatniY;
int ostatniKolor;

void linia(int x0,int y0, int x1, int y1, unsigned int kolor) {
  P.linia(x0,y0,x1,y1,kolor);
  ostatniX = x1;
  ostatniY = y1;
  ostatniKolor = kolor;
}
void linia(punkt a, punkt b, unsigned int kolor) {
	linia(a.x, a.y, b.x, b.y, kolor);
}
// do pomyslenia, jak to sie powinno scalic
void liniaOPCJE(punkt a, punkt b, unsigned int kolor, int dluzej) {
	P.linia(a.x, a.y, b.x, b.y, kolor, dluzej);
}
void liniaOPCJE(punkt a, punkt b, unsigned int kolor, int dluzej, int kropki) {
	P.linia(a.x, a.y, b.x, b.y, kolor, dluzej, kropki);
}
void liniaDo(int x, int y, unsigned int kolor) {
  P.linia(ostatniX, ostatniY, x, y, ostatniKolor);
  ostatniX = x;
  ostatniY = y;
  ostatniKolor = kolor;
}
void liniaDo(punkt p, unsigned int kolor) {
	liniaDo(p.x, p.y, kolor);
}
void liniaDo(int x, int y) {
  liniaDo(x, y, ostatniKolor);
}
void liniaDo(punkt p) {
  liniaDo(p.x, p.y);
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

void wypelnionaElipsa(punkt p, int rx, int ry, double a0, double a1, double a2, unsigned int kolor) {
	wypelnionaElipsa(p.x, p.y, rx, ry, a0, a1, a2, kolor);
}

void wypelnionyOkrag(punkt p, int r, unsigned int kolor) {
	// kolor <-> r
	P.rysujPunkt4(p.x, p.y, kolor, r);
}

void wypelnionyOkrag(int x, int y, int r, unsigned int kolor) {
	// kolor <-> r
	P.rysujPunkt4(x, y, kolor, r);
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

  punkt punkty[30];

  int Xkolano1, Ykolano1;
  Xkolano1 = 150-2;
  Ykolano1 = 365-3;
  punkt& kolano1 = punkty[0];
  kolano1 = punkt(150-2,365-3+1);  
  punkt& udo1 = punkty[1];
  udo1 = kolano1 + punkt(0,-1);
  punkt& lydka1 = punkty[2];
  lydka1 = kolano1 + punkt(-41+2,52-1-1);

  // kolano1
  wypelnionyOkrag(kolano1, 27,0xc04000); // 27
//  P.elipsa3(150-2,365-3,29,90,0,180,170,0x602000);	  
  // udo1
  wypelnionaElipsa(udo1, 30-3,92+3,0,180,169,0xa02000);	  
  //wypelnionaElipsa(Xkolano1-41,Ykolano1+52,28,70,0,360,55,0xd06000);
  //P.elipsa3(Xkolano1-41+2,Ykolano1+52-1,27,73,0,360,55,0xd06000);
  // lydka1
  wypelnionaElipsa(lydka1 ,27,73+4,0,360,55,0xd06000);

  punkt& kolano2 = punkty[3];
  kolano2 = punkt(258,445);
  punkt& lydka2 = punkty[4];
  lydka2 = kolano2 + punkt(1,10);

  // lydka2
  P.elipsa3(lydka2.x,lydka2.y, 29,42,0,360,0,0xff00);
  wypelnionaElipsa(lydka2, 29,42,0,360,0,0xc00060);
  // kolano2
  P.elipsa3(kolano2.x,kolano2.y ,30,99,0,180,171,0xff00);
  wypelnionaElipsa(kolano2, 30,99,0,180,171,0xa00030);
  
  punkt& udo2A = punkty[5];
  punkt& udo2B = punkty[6];
  udo2A = punkt(202,302);
  udo2B = punkt(234,344);

  // udo2
  P.pisak(50);
  linia(udo2A,udo2B, 0x4010);
  P.pisak(46);
  linia(udo2A,udo2B, 0xd00070);
  
  punkt& torsD = punkty[7];
  punkt& torsC = punkty[8];
  punkt& torsB = punkty[9];
  punkt& torsA = punkty[10];  
  torsD = punkt(155,257);
  torsC = punkt(193,257);
  torsB = punkt(195,129);
  torsA = punkt(145,134);

  // tors
  P.pisak(56);
  // D,C
  linia(torsD,torsC,0xa04080);
  liniaDo(torsB);
  liniaDo(torsA);
  liniaDo(torsD);

  // wzor na torsie

  /* */
  punkt& wzorA = punkty[11];
  punkt& wzorC = punkty[12];
  wzorA = torsA + punkt(5,5);
  wzorC = torsC + punkt(2,2);
  // D,B:
  P.pisak(46);
  linia(torsD,torsB,0); //0x302010);
  // A+(5,5):
  //P.wypelnionyOkrag(145,134,0x0,56>>1);
  wypelnionaElipsa(wzorA,(56+6)>>1,(56+6)>>1,0,180,110,0); // 0x302010);
  // C+(2,2):
  wypelnionaElipsa(wzorC,(56-4)>>1,(56-4)>>1,0,180,290,0); // 0x302010);
  /* */
  //wypelnionaElipsa(145,134,17,26,0,360,30,0); // 0x302010);

  punkt& glowa = punkty[13];
  glowa = punkt(171,66);
  // glowa
  wypelnionyOkrag(glowa, 37,0x802040);

  punkt& reka1 = punkty[14];
  reka1 = punkt(65,177);
  punkt& ramie1 = punkty[15];
  ramie1 = reka1 + punkt(8+3, -8);

#define KOLOROWY (0)
  // reka1
  wypelnionyOkrag(reka1, 30,0xff00);
  wypelnionaElipsa(reka1, 28,65,0,180,31.5,KOLOROWY ? 0xa4080 : 0xa00050);
  wypelnionaElipsa(ramie1 , 25,60,0,180,180+31.5+10,KOLOROWY ? 0xff0000 : 0xd00070); //0xa4080);

  punkt& reka2 = punkty[16];
  reka2 = punkt(300,200) - punkt(18, 15);
  punkt& strzalkowa2 = punkty[17];
  strzalkowa2 = reka2 + punkt(8+3, 8);
  punkt& ramie2 = punkty[18];
  ramie2 = reka2 + punkt(-5-5,-5);

  // reka2
  wypelnionyOkrag(reka2, 28,0xff00);
  wypelnionaElipsa(ramie2, 27,80,0,180,41.5+90+15,KOLOROWY ? 0xff0000 :  0xa06030); //0xa30a0);
  wypelnionaElipsa(strzalkowa2, 26,65,0,180,180+41.5+10+90,KOLOROWY ? 0xa30a0 : 0xd08040 );

  
  P.odswiez();
  K.czekajNaKlawisz();
}

