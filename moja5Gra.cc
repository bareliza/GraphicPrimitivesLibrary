#define _ALE_ZLY_STYL_BIBLIOTEK_
//#define _SLABE_SZYBSZE_ELIPSY_
#include "grafika1.cc"

#include <unistd.h>

Projektor P(720,660);
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
void linia(punkt a, punkt b) {
	linia(a.x, a.y, b.x, b.y, ostatniKolor);
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

int trybEdycji = 0;

void wypelnionaElipsa(int x, int y, int rx, int ry, double a0, double a1, double a2, unsigned int kolor) {
	int pen1;
	pen1 = P.pioro;	

	if(trybEdycji) {
		P.pisak(1);
		P.elipsa3(x,y,rx-4,ry-3,a0,a1,a2,kolor);
	} else {
		P.pisak(8);
		for(int i=ry-3;i>0;i-=6) {
			P.elipsa3(x,y,rx-4,i,a0,a1,a2,kolor);	
		}
	}
	P.pisak(pen1);
}
void wypelnionaElipsa(punkt p, int rx, int ry, double a0, double a1, double a2, unsigned int kolor) {
	wypelnionaElipsa(p.x, p.y, rx, ry, a0, a1, a2, kolor);
}
void wypelnionaElipsa(punkt p, punkt r, double a0, double a1, double a2, unsigned int kolor) {
	wypelnionaElipsa(p.x, p.y, r.x, r.y, a0, a1, a2, kolor);
}

void wypelnionyOkrag(punkt p, int r, unsigned int kolor) {
	// kolor <-> r
	P.rysujPunkt4(p.x, p.y, kolor, r);
}

void wypelnionyOkrag(int x, int y, int r, unsigned int kolor) {
	// kolor <-> r
	P.rysujPunkt4(x, y, kolor, r);
}

#define PUNKTOW (40)
/* skradajacy sie
  punkt punkty[PUNKTOW][2] = 
  {
    { punkt( 411, 370 ), punkt (  27,   0 ) }, { punkt( 414, 365 ), punkt (  27,  95 ) }, 
    { punkt( 435, 460 ), punkt (  28,  94 ) }, { punkt( 494, 443 ), punkt (  30,  99 ) }, 
    { punkt( 496, 444 ), punkt (  29,  42 ) }, { punkt( 496, 274 ), punkt (  50,  46 ) }, 
    { punkt( 476, 355 ), punkt (   0,   0 ) }, { punkt( 451, 258 ), punkt (  56,   0 ) }, 
    { punkt( 493, 257 ), punkt (   0,   0 ) }, { punkt( 489, 128 ), punkt (   0,   0 ) }, 
    { punkt( 445, 134 ), punkt (   0,   0 ) }, { punkt( 450, 139 ), punkt (  46,  50 ) }, 
    { punkt( 495, 259 ), punkt (  31,  26 ) }, { punkt( 471,  66 ), punkt (  37,   0 ) }, 
    { punkt( 387, 188 ), punkt (  28,  65 ) }, { punkt( 395, 176 ), punkt (  25,  60 ) }, 
    { punkt( 550, 180 ), punkt (  30,  28 ) }, { punkt( 552, 185 ), punkt (  28,  75 ) }, 
    { punkt( 551, 181 ), punkt (  27,  80 ) }, { punkt( 291, 222 ), punkt (   8,   0 ) }, 
    { punkt( 311, 228 ), punkt (   0,   0 ) }, { punkt( 333, 212 ), punkt (   0,   0 ) }, 
    { punkt( 565, 199 ), punkt (   0,   0 ) }, { punkt( 318,   5 ), punkt (   0,   0 ) }, 
    { punkt( 335,  20 ), punkt (   0,   0 ) }, { punkt( 435,  63 ), punkt (   4,   0 ) }, 
    { punkt( 435,  86 ), punkt (   0,   0 ) }, { punkt( 507,  63 ), punkt (   0,   0 ) }, 
    { punkt( 507,  86 ), punkt (   0,   0 ) }, { punkt( 414, 488 ), punkt (  15,  10 ) }, 
    { punkt( 438, 480 ), punkt (   0,   0 ) }, { punkt( 487, 479 ), punkt (   0,   0 ) }, 
    { punkt( 486, 494 ), punkt (   0,   0 ) }, { punkt( 525, 496 ), punkt (   0,   0 ) }, 
    { punkt( 519, 479 ), punkt (   0,   0 ) }, { punkt( 437, 465 ), punkt (  28,  28 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }
  };
  double katy[PUNKTOW] = 
  {
    0.00, -163.03, -193.16, -200.56, -38.85, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 72.39, 
    -154.16, 0.00, -42.09, -200.22, 0.00, 
    35.22, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    55.00, 0.00, 0.00, 0.00, 0.00
  };*/

/* "skuteczny bramkarz". */ 
  // Przyjemnie by bylo rozne takie fazy ruchu miec "enkapsu@lowane" w obiekcie / obiektach
#define PUNKTOW (40)
  punkt punkty[PUNKTOW][2] = 
  {
    { punkt( 442, 365 ), punkt (  27,   0 ) }, { punkt( 443, 365 ), punkt (  27,  95 ) }, 
    { punkt( 377, 417 ), punkt (  28,  94 ) }, { punkt( 555, 417 ), punkt (  30,  99 ) }, 
    { punkt( 548, 410 ), punkt (  29,  42 ) }, { punkt( 502, 302 ), punkt (  50,  46 ) }, 
    { punkt( 505, 360 ), punkt (   0,   0 ) }, { punkt( 451, 258 ), punkt (  56,   0 ) }, 
    { punkt( 493, 257 ), punkt (   0,   0 ) }, { punkt( 495, 129 ), punkt (   0,   0 ) }, 
    { punkt( 445, 134 ), punkt (   0,   0 ) }, { punkt( 450, 139 ), punkt (  46,  50 ) }, 
    { punkt( 495, 259 ), punkt (  31,  26 ) }, { punkt( 471,  66 ), punkt (  37,   0 ) }, 
    { punkt( 384, 197 ), punkt (  28,  65 ) }, { punkt( 395, 176 ), punkt (  25,  60 ) }, 
    { punkt( 550, 180 ), punkt (  30,  28 ) }, { punkt( 552, 187 ), punkt (  28,  75 ) }, 
    { punkt( 553, 189 ), punkt (  27,  80 ) }, { punkt( 346, 266 ), punkt (   8,   0 ) }, 
    { punkt( 360, 256 ), punkt (   0,   0 ) }, { punkt( 381, 255 ), punkt (   0,   0 ) }, 
    { punkt( 559, 251 ), punkt (   0,   0 ) }, { punkt( 318,   5 ), punkt (   0,   0 ) }, 
    { punkt( 335,  20 ), punkt (   0,   0 ) }, { punkt( 435,  63 ), punkt (   4,   0 ) }, 
    { punkt( 435,  86 ), punkt (   0,   0 ) }, { punkt( 507,  63 ), punkt (   0,   0 ) }, 
    { punkt( 507,  86 ), punkt (   0,   0 ) }, { punkt( 344, 425 ), punkt (  15,  10 ) }, 
    { punkt( 361, 446 ), punkt (   0,   0 ) }, { punkt( 552, 442 ), punkt (   0,   0 ) }, 
    { punkt( 560, 447 ), punkt (   0,   0 ) }, { punkt( 583, 441 ), punkt (   0,   0 ) }, 
    { punkt( 580, 433 ), punkt (   0,   0 ) }, { punkt( 374, 418 ), punkt (  28,  28 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }
  };
  double katy[PUNKTOW] = 
  {
    0.00, -180.67, -119.16, -225.00, -34.99, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 4.01, 
    -172.33, 0.00, -6.01, -194.83, 0.00, 
    35.22, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    -40.24, 0.00, 0.00, 0.00, 0.00
  };/* */


/*

#define PUNKTOW (40)
//  punkt punkty[PUNKTOW][2];
  // na bacznosc / wyjsciowa
  punkt punkty[PUNKTOW][2] = 
  {
    { punkt( 440, 367 ), punkt (  27,   0 ) }, { punkt( 443, 365 ), punkt (  27,  95 ) }, 
    { punkt( 439, 449 ), punkt (  28,  94 ) }, { punkt( 503, 451 ), punkt (  30,  99 ) }, 
    { punkt( 504, 433 ), punkt (  29,  42 ) }, { punkt( 502, 302 ), punkt (  50,  46 ) }, 
    { punkt( 505, 360 ), punkt (   0,   0 ) }, { punkt( 451, 258 ), punkt (  56,   0 ) }, 
    { punkt( 493, 257 ), punkt (   0,   0 ) }, { punkt( 495, 129 ), punkt (   0,   0 ) }, 
    { punkt( 445, 134 ), punkt (   0,   0 ) }, { punkt( 450, 139 ), punkt (  46,  50 ) }, 
    { punkt( 495, 259 ), punkt (  31,  26 ) }, { punkt( 471,  66 ), punkt (  37,   0 ) }, 
    { punkt( 384, 197 ), punkt (  28,  65 ) }, { punkt( 395, 176 ), punkt (  25,  60 ) }, 
    { punkt( 550, 180 ), punkt (  30,  28 ) }, { punkt( 552, 187 ), punkt (  28,  75 ) }, 
    { punkt( 553, 189 ), punkt (  27,  80 ) }, { punkt( 346, 266 ), punkt (   8,   0 ) }, 
    { punkt( 360, 256 ), punkt (   0,   0 ) }, { punkt( 381, 255 ), punkt (   0,   0 ) }, 
    { punkt( 559, 251 ), punkt (   0,   0 ) }, { punkt( 318,   5 ), punkt (   0,   0 ) }, 
    { punkt( 335,  20 ), punkt (   0,   0 ) }, { punkt( 435,  63 ), punkt (   4,   0 ) }, 
    { punkt( 435,  86 ), punkt (   0,   0 ) }, { punkt( 507,  63 ), punkt (   0,   0 ) }, 
    { punkt( 507,  86 ), punkt (   0,   0 ) }, { punkt( 421, 491 ), punkt (  15,  10 ) }, 
    { punkt( 452, 491 ), punkt (   0,   0 ) }, { punkt( 487, 479 ), punkt (   0,   0 ) }, 
    { punkt( 486, 494 ), punkt (   0,   0 ) }, { punkt( 525, 496 ), punkt (   0,   0 ) }, 
    { punkt( 519, 479 ), punkt (   0,   0 ) }, { punkt( 440, 448 ), punkt (  28,  28 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }, 
    { punkt( 300,   0 ), punkt (   0,   0 ) }, { punkt( 300,   0 ), punkt (   0,   0 ) }
  };
  double katy[PUNKTOW] = 
  {
    0.00, -180.67, -179.20, -178.67, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 4.01, 
    -172.33, 0.00, -6.01, -194.83, 0.00, 
    35.22, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    0.00, 0.00, 0.00, 0.00, 0.00, 
    55.00, 0.00, 0.00, 0.00, 0.00
  };
*/

//  punkt biegunowe[PUNKTOW];
/*  
  double katy[PUNKTOW] = {
    0, 169, 55+180, 171,    0,           0, 0,             0,          0, 0,
    0,   0,  0,       0, 31.5, 180+31.5+10, 0, 180+41.5+5+90, 41.5+90+15, 0,
    0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 55, 0, 0, 0, 0
  };
*/
  const punkt pz = punkt(0,0);

/* NIE-Przestarzale: promienie sa teraz w punkty[i][1] czy to prawda, chyba nie... */
  punkt promienie[PUNKTOW] = {
    pz, punkt(30-3,92+3), punkt(28,90+4), punkt(30,99), punkt(29,42),   
    pz, pz,               pz,             pz,           pz,
    
    pz,           pz,           pz,           pz, punkt(28,65),
    punkt(25,60), pz, punkt(28,75), punkt(27,80), pz,
    
    pz, pz, pz, pz, pz, pz, pz, pz, pz, pz,
    pz, pz, pz, pz, pz, punkt(28,28), pz, pz, pz, pz
  };
/* */

  int toElipsa[PUNKTOW] = {
    0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0
  };

  punkt& kolano1 = punkty[0][0];
  punkt& udo1 = punkty[1][0];
  punkt& lydka1 = punkty[2][0];
  punkt& kolano1rozm = punkty[0][1];
  punkt& udo1rozm = punkty[1][1];
  punkt& lydka1rozm = punkty[2][1];

#define OST (35)
#define OSTATNI_PUNKT (OST)
  punkt& lydka01 = punkty[OSTATNI_PUNKT][0];
  punkt& lydka01rozm = punkty[OST][1]; 

  punkt& kolano2 = punkty[3][0];
  punkt& lydka2 = punkty[4][0];
  punkt& kolano2rozm = punkty[3][1];
  punkt& lydka2rozm = punkty[4][1];

  punkt& udo2A = punkty[5][0];
  punkt& udo2B = punkty[6][0];
  punkt& udo2ABrozm = punkty[5][1];

  punkt& torsD = punkty[7][0];
  punkt& torsC = punkty[8][0];
  punkt& torsB = punkty[9][0];
  punkt& torsA = punkty[10][0];  

  punkt& torsRozm = punkty[7][1];

  /* */
  punkt& wzorA = punkty[11][0];
  punkt& wzorC = punkty[12][0];
  punkt& torsDBrozm = punkty[11][1];
  punkt& torsACrozm = punkty[12][1];

  punkt& glowa = punkty[13][0];
  punkt& glowaRozm = punkty[13][1];

  punkt& reka1 = punkty[14][0];
  punkt& ramie1 = punkty[15][0];
  punkt& reka1rozm = punkty[14][1];
  punkt& ramie1rozm = punkty[15][1];
  punkt& receRozm = punkty[16][1];

  punkt& reka2 = punkty[16][0];
  punkt& strzalkowa2 = punkty[17][0];
  punkt& ramie2 = punkty[18][0];
  punkt& strzalkowa2rozm = punkty[17][1];
  punkt& ramie2rozm = punkty[18][1];

  /* */
  punkt& dlon1A = punkty[19][0];
  punkt& dlon1B = punkty[20][0];
  punkt& dlon1C = punkty[21][0];
  punkt& dlon2A = punkty[22][0];
  punkt& dlon2B = punkty[23][0];
  punkt& dlon2C = punkty[24][0];
  punkt& dlonieRozm = punkty[19][1];

  punkt& ucho1A = punkty[25][0];
  punkt& ucho1B = punkty[26][0];
  punkt& ucho2A = punkty[27][0];
  punkt& ucho2B = punkty[28][0];
  punkt& uszyRozm = punkty[25][1];

  punkt& stopa1A = punkty[29][0];
  punkt& stopa1B = punkty[30][0];
  punkt& stopa2A = punkty[31][0];
  punkt& stopa2B = punkty[32][0];
  punkt& stopa2C = punkty[33][0];
  punkt& stopa2D = punkty[34][0];
  punkt& stopyRozm = punkty[29][1];


void ustalLudka(void) {
  int Xkolano1, Ykolano1;
  Xkolano1 = 150-2;
  Ykolano1 = 365-3;

  kolano1 = punkt(150-2,365-3+1);  
  udo1 = kolano1 + punkt(0,-1);
  lydka1 = kolano1 + punkt(-41+2, 52-1-1) + punkt(-20, 20) - punkt(5,5);
  kolano1rozm = punkt(27,0);
  udo1rozm = punkt(30-3,92+3);
  lydka1rozm = punkt(28,90+4);

  lydka01 = punkt(80, 432); // - punkt(250+50, 0);
  lydka01rozm = punkt(28, 28);
  
  kolano2 = punkt(258,445);
  lydka2 = kolano2 + punkt(1,10);
  kolano2rozm = punkt(30,99);
  lydka2rozm = punkt(29,42);

  udo2A = punkt(202,302);
  udo2B = punkt(234,344);
  udo2ABrozm = punkt(50,46); 

  torsD = punkt(155,257);
  torsC = punkt(193,257);
  torsB = punkt(195,129);
  torsA = punkt(145,134);
  torsRozm = punkt(56,0);

  /* */
  wzorA = torsA + punkt(5,5);
  wzorC = torsC + punkt(2,2);
  torsDBrozm = punkt (46,50);
  torsACrozm = punkt((56+6)>>1,(56-4)>>1);

  glowa = punkt(171,66);
  glowaRozm = punkt(37,0);

  reka1 = punkt(65,177);
  ramie1 = reka1 + punkt(8+3, -8);
  reka1rozm = punkt(28,65);
  ramie1rozm = punkt(25,60);

  receRozm = punkt(30,28);

  reka2 = punkt(300,200) - punkt(18, 15);
  strzalkowa2 = reka2 + punkt(8+3-3-3, 8+3-3);
  ramie2 = reka2 + punkt(-5-5,-5-7);
  strzalkowa2rozm = punkt(28,75);
  ramie2rozm = punkt(27,80);

  /* */
  dlon1A = punkt(30,220);
  dlon1B = dlon1A + punkt(5,18);
  dlon1C = dlon1B + punkt(10,10);
  dlon2A = punkt(330,235);
  dlon2B = punkt(18,5);
  dlon2C = punkt(35,20);
  dlonieRozm = punkt(8,0);
  
  ucho1A = punkt(135,63); 
  ucho1B = ucho1A + punkt(0,23); 
  ucho2A = punkt(207,63); 
  ucho2B = ucho2A + punkt(0,23); 
  uszyRozm = punkt(4,0); 

  stopa1A = punkt(50,450);
  stopa1B = punkt(70,480);
  stopa2A = punkt(247,497);
  stopa2B = punkt(245,505);
  stopa2C = punkt(285,508);
  stopa2D = punkt(270,498);
  stopyRozm = punkt(15,10);

  ////////////////////////////////////////////
  // skalowanie:
  ////////////////////////////////////////////
//#define S wektor2wR(1.3,1.3)
//#define S1 wektor2wR(1.3,1.3)
//#define S wektor2wR(1.1,1.1)
//#define S1 wektor2wR(1.1,1.1)
//#define S wektor2wR(0.5, 0.5)
//#define S1 wektor2wR(0.5, 0.5)
//#define S wektor2wR(0.8, 0.8)
//#define S1 wektor2wR(0.8, 0.8)
#define S wektor2wR(1, 1)
#define S1 wektor2wR(1, 1)

  for(int i=0;i<PUNKTOW;++i) {
      punkty[i][0] = S * punkty[i][0] + punkt(250 + 50, 0); // + punkt(200,-30);
      punkty[i][1] = S1 * punkty[i][1];
  }
}

double alfa0strz2;

void rysujLudka(void) {
  P.czysc(0xffffff);
  ////////////////////////////////////////////
  // rysowanie:
  ////////////////////////////////////////////

  // kolano1
  wypelnionyOkrag(kolano1, kolano1rozm.x, 0xc04000); // 27
//  P.elipsa3(150-2,365-3,29,90,0,180,170,0x602000);	  
  // udo1
  wypelnionaElipsa(udo1, promienie[1] /* udo1rozm */, 0,180,katy[1],0xa02000);	  
  //wypelnionaElipsa(Xkolano1-41,Ykolano1+52,28,70,0,360,55,0xd06000);
  //P.elipsa3(Xkolano1-41+2,Ykolano1+52-1,27,73,0,360,55,0xd06000);
  // lydka1
  wypelnionaElipsa(lydka01, promienie[35] /* lydka01rozm */, 0,360,katy[35],0xc04000);
  wypelnionaElipsa(lydka1 , promienie[2] /* lydka1rozm */, 0,180,katy[2],0xd06000);
                    // punkty[2][0]
  // lydka2
  //P.elipsa3(lydka2.x,lydka2.y, 29,42,0,360,0,0xff00);
  wypelnionaElipsa(lydka2, promienie[4] /* lydka2rozm */, 0,360,katy[4],0xc00060);
  // kolano2
  //P.elipsa3(kolano2.x,kolano2.y ,30,99,0,180,171,0xff00);
  wypelnionaElipsa(kolano2, promienie[3] /* kolano2rozm */, 0,180,katy[3],0xa00030);
                     // punkty[3][0]
  // udo2
  P.pisak(udo2ABrozm.x);
  linia(udo2A,udo2B, 0x4010);
  P.pisak(udo2ABrozm.y);
  linia(udo2A,udo2B, 0xd00070);
  
  // tors
  P.pisak(torsRozm.x);
  linia(torsD,torsC,0xa04080);
  liniaDo(torsB);
  liniaDo(torsA);
  liniaDo(torsD);

  // wzor na torsie:
  P.pisak(torsDBrozm.y);
  linia(torsD,torsB,0);
  wypelnionaElipsa(wzorA, torsACrozm.x,torsACrozm.x, 0,180,110,0);
  wypelnionaElipsa(wzorC, torsACrozm.y,torsACrozm.y, 0,180,290,0);

  // glowa
  wypelnionyOkrag(glowa, glowaRozm.x,0x802040);

#define CZERWONY (0xff0000)

#define KOLOROWY (1)
#define REKA1KOLOR       (KOLOROWY ? 0x0a4080 : 0xa00050)
#define RAMIE1KOLOR      (KOLOROWY ? CZERWONY : 0xd00070)
#define RAMIE2KOLOR      (KOLOROWY ? CZERWONY : 0xa02000)
#define STRZALKOWA2KOLOR (KOLOROWY ? 0x0a30a0 : 0xf06000)
  // reka1
  wypelnionyOkrag(reka1, receRozm.x, 0xff00);
  wypelnionaElipsa(reka1,  promienie[14] /* reka1rozm */, 0,180, katy[14], REKA1KOLOR);
  wypelnionaElipsa(ramie1 , promienie[15] /* ramie1rozm */, 0,180, katy[15], RAMIE1KOLOR); //0xa4080);

  // reka2
  wypelnionyOkrag(reka2, receRozm.y, 0xff00);
  wypelnionaElipsa(ramie2, promienie[18] /* ramie2rozm */, 0,180, katy[18], RAMIE2KOLOR); //0xa30a0);
  // alfa0strz2 = 180+41.5+5+90;
  wypelnionaElipsa(strzalkowa2, promienie[17] /* strzalkowa2rozm */, 0,180, katy[17], STRZALKOWA2KOLOR );

  // dlonie:
  P.pisak(dlonieRozm.x);
  linia(dlon1A,dlon1B,0xff);
  liniaDo(dlon1C);
  P.pisak(dlonieRozm.x);
  linia(dlon2A,dlon2A+punkt(18,5),0xff0000);
  liniaDo(dlon2A+punkt(35,20));
//  linia(dlon2A,dlon2A+dlon2B,0xff);
//  liniaDo(dlon2A+dlon2C);

  // uszy:
  P.pisak(uszyRozm.x);
  linia(ucho1A,ucho1B,0xff0000);
  linia(ucho2A,ucho2B,0xff);

  // stopy:
  P.pisak(stopyRozm.x);
  linia(stopa1A,stopa1B,0xff);

  P.pisak(stopyRozm.y);
  linia(stopa2A,stopa2B,0xff);
  liniaDo(stopa2C);
  liniaDo(stopa2D);
  liniaDo(stopa2A);
  linia(stopa2A,stopa2C);
  linia(stopa2B,stopa2D);
}

int main(int argc, char **argv){
  P.czysc(0xffffff);
//  P.wczytajBMP("20201214_102131-Postac-1a1.bmp");
  P.wczytajBMP("Postac-swobodna.bmp");
  P.linia(10,10,640,640,0x600060);
  P.pisak(0);

  for(int i=0;i<P.wymiar.y;i += S.x * 10.0)
	P.linia(0,i,P.wymiar.x,i,0xa000);
  for(int j=0;j<P.wymiar.x;j += S.y * 10.0)
	P.linia(j,0,j,P.wymiar.x,0xa000);

  for(int i=0;i<P.wymiar.y;i += S.x * 50.0)
	P.linia(0,i,P.wymiar.x,i,0x80);
  for(int j=0;j<P.wymiar.x;j += S.y * 50.0)
	P.linia(j,0,j,P.wymiar.x,0x80);

  for(int i=0;i<P.wymiar.y;i += S.x * 100.0)
	P.linia(0,i,P.wymiar.x,i,0xa00000);
  for(int j=0;j<P.wymiar.x;j += S.y * 100.0)
	P.linia(j,0,j,P.wymiar.x,0xa00000);

  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0, 0, 1, 32);
  
  int myszx, myszy;
  myszx = 999;
  myszy = 888;

  P.tekst2(15, 2, "%d", &myszx);
  P.tekst2(85, 2, "%d", &myszy);

//  ustalLudka();
  rysujLudka();

  ////////////////////////////////////////////
  // punkty do edycji:
  ////////////////////////////////////////////

  punkt paa,pbb,pee;
  paa.x = 15;
  paa.y = 15;
  pbb.x = 7;
  pbb.y = 7;
  P.pisak(8);

#define DEG2RAD(deg) (M_PI * ((double)deg) / 180.0)
  for(int i=0;i<PUNKTOW;++i) {
      P.ramka(punkty[i][0]-pbb, paa, toElipsa[i] ? 0x00009f : 0xff8080);
      if(toElipsa[i]) {
	pee = punkt(cos(DEG2RAD(katy[i]+90)) * promienie[i].y, sin(DEG2RAD(katy[i]+90)) * promienie[i].y);
	P.ramka(punkty[i][0]+pee-pbb, paa, 0xffff00);
      }
  }
  P.odswiez();             


  ///////////////////////////////////////
  // wskaznik myszy: 
  ///////////////////////////////////////


  P.pisak(0);

  for(int i=0;i<P.wymiar.y;i += S.x * 10.0)
	P.linia(0,i,P.wymiar.x,i,0xa000);
  for(int j=0;j<P.wymiar.x;j += S.y * 10.0)
	P.linia(j,0,j,P.wymiar.x,0xa000);

  for(int i=0;i<P.wymiar.y;i += S.x * 50.0)
	P.linia(0,i,P.wymiar.x,i,0x80);
  for(int j=0;j<P.wymiar.x;j += S.y * 50.0)
	P.linia(j,0,j,P.wymiar.x,0x80);

  for(int i=0;i<P.wymiar.y;i += S.x * 100.0)
	P.linia(0,i,P.wymiar.x,i,0xa00000);
  for(int j=0;j<P.wymiar.x;j += S.y * 100.0)
	P.linia(j,0,j,P.wymiar.x,0xa00000);


  punkt mysz0, mysz1;
 
  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0, 0, 1, 32);

  int miarkaAktywna = 0;
  int edycjaPromienia = 0;
  punkt miarkaStart, delta;
  punkt miarkaStart0, delta0, deltaA;

  SDL_Surface *tmpSurface = SDL_ConvertSurface(P.screen, P.screen->format, SDL_SWSURFACE);
  SDL_Rect from, to;
  int nrPunktu, edycjaElipsy;
  
  while(K.klawisz != SDLK_ESCAPE) {
	delta0=deltaA;
  	K.odswiez();
  	if(K.event.type == SDL_MOUSEBUTTONDOWN) {
  		if ( miarkaAktywna ) {
  			miarkaAktywna = 0;
			edycjaPromienia = 0;
			trybEdycji = 0;
			rysujLudka();

			from.x = miarkaStart0.x-2;
			from.y = miarkaStart0.y-2;
			if(delta.x<0) from.x = miarkaStart0.x+delta.x-2;
			if(delta.y<0) from.y = miarkaStart0.y+delta.y-2;			
			from.w = abs(delta.x)+4;
			from.h = abs(delta.y)+4;
			to = from;
			//printf("from = ( %d, %d ); \n", to.x, to.y); 
			SDL_BlitSurface(tmpSurface, &from, P.screen, &to);

  		} else {
  			miarkaAktywna = 1;
 			//if(((SDL_MouseButtonEvent *)(&(K.event)))->button == SDL_BUTTON_LEFT)
 			// obecnie jest to wersja dla leworecznych ;)
 			if(((SDL_MouseButtonEvent *)(&(K.event)))->button == SDL_BUTTON_RIGHT)
 				edycjaPromienia = 1;
  		}
  		
  		if(miarkaAktywna){
			miarkaStart = mysz1;
			miarkaStart0 = mysz1;
		}
  	}
  	if(K.event.type == SDL_MOUSEMOTION && 
  	   ( (K.mysz.x != mysz0.x) || (K.mysz.y != mysz0.y) )
  	   ) {
  		//printf("mysz x: %d y: %d\n", K.mysz.x, K.mysz.y);
		mysz0 = K.mysz;
                 mysz1 = K.mysz;
                 if ( mysz1.x >= 300 ) mysz1.x -= 300;

  		P.prostokat(0, 0, 300, 80, 0xff80ff);
  		P.tekst2(15, 2, "%d", &(mysz1.x) );
  		P.tekst2(75, 2, "%d", &(mysz1.y) );
  		P.tekst2(155, 42, "%d", &(miarkaAktywna) );
  		P.tekst2(225, 42, "%d", &(nrPunktu) );
  		P.odswiez(0,0,300,40);
  		if(miarkaAktywna) {
  			delta = mysz1 - miarkaStart;
			deltaA = mysz0 - miarkaStart;
  			P.tekst2(155, 2, "%d", &(delta.x) );
  			P.tekst2(225, 2, "%d", &(delta.y) );
  			P.tekst2(15, 42, "%d", &(edycjaPromienia) );
  			P.pisak(0);
// #include "SDL.h"
// int SDL_BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect);
			from.x = miarkaStart0.x-2;
			from.y = miarkaStart0.y-2;
			if(delta0.x<0) from.x = miarkaStart0.x+delta0.x-2;
			if(delta0.y<0) from.y = miarkaStart0.y+delta0.y-2;			
			from.w = abs(delta0.x)+4;
			from.h = abs(delta0.y)+4;
			to = from;
			//printf("from = ( %d, %d ); \n", to.x, to.y); 
			SDL_BlitSurface(tmpSurface, &from, P.screen, &to);
			P.linia(miarkaStart, mysz1, 0xff0000);
  			//P.odswiez();
  		}
  		//P.odswiez();				
	}
	K.zeruj();
	P.rysujPunkt(mysz0.x, mysz0.y, 0x0ff00ff);
	P.odswiez(mysz0.x, mysz0.y,1,1);
        
	if(miarkaAktywna == 0) {
		nrPunktu = -1;
		edycjaElipsy = -1;
		int i1;
		for(i1=0;i1<PUNKTOW;i1++) {
			punkt pcc;
			pcc = mysz0-punkty[i1][0];
			if((abs(pcc.x) < 10) && (abs(pcc.y) < 10)) {
				P.pisak(2);
				P.ramka(punkty[i1][0] - pbb, paa, 0x00ff00);
				//P.odswiez();//punkty[i1][0]-pbb, paa);
				nrPunktu = i1;
			} else {
				P.pisak(2);
				P.ramka(punkty[i1][0] - pbb, paa, toElipsa[i1] ? 0x00009f : 0xffff80);
      				if(toElipsa[i1]) {
					pee = punkt(cos(DEG2RAD(katy[i1]+90)) * promienie[i1].y,
					      sin(DEG2RAD(katy[i1]+90)) * promienie[i1].y);
					P.ramka(punkty[i1][0]+pee-pbb, paa, 0xffff00);
      				}
				//P.odswiez();//punkty[i1][0]-pbb, paa);
			}
			if(toElipsa[i1]) {
				pee = punkt(cos(DEG2RAD(katy[i1]+90)) * promienie[i1].y,
				      sin(DEG2RAD(katy[i1]+90)) * promienie[i1].y);				
				pcc = mysz0 - (punkty[i1][0] + pee);
				if((abs(pcc.x) < 10) && (abs(pcc.y) < 10)) {
					P.pisak(2);
					P.ramka(punkty[i1][0]+pee-pbb, paa, 0x00ff00);
					//P.odswiez();//punkty[i1][0]-pbb, paa);
					nrPunktu = i1;
					edycjaElipsy = 1;
				}				
			}
		}		
	}
	
	if( miarkaAktywna && (nrPunktu != -1) && (edycjaElipsy == -1) ) {
		trybEdycji = 1;
		punkty[nrPunktu][0] = mysz0;
		rysujLudka();
	}
	if( miarkaAktywna && (nrPunktu != -1) && (edycjaElipsy == 1) ) {
		trybEdycji = 1;
                 if( edycjaPromienia ) {
                 	pee = mysz0 - punkty[nrPunktu][0];
                 	promienie[nrPunktu].y = sqrt( pee.x*pee.x + pee.y*pee.y );
                         // katy[nrPunktu] = 0;
                         //
                         //
                         //  90 ----*
                         //         |
                         //         |
                         //         |
                         //         |
                         //
                         //         0
                         
                 } else {
			pee = mysz0 - punkty[nrPunktu][0];
			katy[nrPunktu] = RAD2DEG(atan2(pee.y, pee.x) - M_PI / 2);
		}
                 rysujLudka();	
	}
	
	
	P.odswiez();
	// usleep(10000); // 40 ms => 25 razy na sekunde; 10ms => 100 x na sekunde 
  }
  SDL_FreeSurface(tmpSurface);

//  punkt punkty[PUNKTOW][2];
  printf ("  punkt punkty[PUNKTOW][2] = \n");
  printf ("  {\n    ");
  for(int i=0;i<PUNKTOW;i++) {
    printf("{ punkt( %3d, %3d ), punkt ( %3d, %3d ) }", 
           punkty[i][0].x, punkty[i][0].y, punkty[i][1].x, punkty[i][1].y); 
    if (i < PUNKTOW - 1) printf (", ");
    if ( ((i % 2) == 1) && (i < PUNKTOW - 1)  ) printf("\n    ");
  }
  printf ("\n  };\n");

  printf ("  double katy[PUNKTOW] = \n");
  printf ("  {\n    ");
  for(int i=0;i<PUNKTOW;i++) {
    printf("%3.2f", katy[i]);
    if (i < PUNKTOW - 1) printf (", ");
    if ( ((i % 5) == 4) && (i < PUNKTOW - 1)  ) printf("\n    ");
  }
  printf ("\n  };\n");
/*
  double katy[PUNKTOW] = {
    0, 169, 55+180, 171,    0,           0, 0,             0,          0, 0,
    0,   0,  0,       0, 31.5, 180+31.5+10, 0, 180+41.5+5+90, 41.5+90+15, 0,
    0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 55, 0, 0, 0, 0
  };

  const punkt pz = punkt(0,0);

  punkt promienie[PUNKTOW] = {
    pz, punkt(30-3,92+3), punkt(28,90+4), punkt(30,99), punkt(29,42),   
    ...
  };
  */

  ///////////////////////////////////////
  // animacja: 
  ///////////////////////////////////////


#define ANIM_STEP (1.0-delta)
#define ddelta (.3/5)
// animacji kat bazowy
#define AN_KAT_B (-katy[17])
// animacji zakres 
#define AN_ZAKR (5)
#define ROZM_ANIM (strzalkowa2rozm.y + 39)

 for(int i=0;i<100;i+=1) {
  double delta = 3;
  //if(i>2)P.mmm=3;
  for(double alfaStrz2=alfa0strz2-AN_ZAKR-AN_KAT_B; alfaStrz2<alfa0strz2+AN_ZAKR-AN_KAT_B;alfaStrz2 += ANIM_STEP) {
//    wypelnionaElipsa(strzalkowa2, strzalkowa2rozm + punkt(2,2), 0,360,alfaStrz2-ANIM_STEP, 0xffffff ); 
    wypelnionyOkrag(strzalkowa2 + punkt(10,0), ROZM_ANIM, 0xffffff);

  // tors
  P.pisak(torsRozm.x);
  linia(torsD,torsC,0xa04080);
  liniaDo(torsB);
  liniaDo(torsA);
  liniaDo(torsD);

  // wzor na torsie:
  P.pisak(torsDBrozm.y);
  linia(torsD,torsB,0);
  wypelnionaElipsa(wzorA, torsACrozm.x,torsACrozm.x, 0,180,110,0);
  wypelnionaElipsa(wzorC, torsACrozm.y,torsACrozm.y, 0,180,290,0);


    if(alfaStrz2<alfa0strz2-AN_KAT_B) delta -= ddelta; // 60 / 4 = 15, 15*.1 = 1.5
    else delta += ddelta;
    wypelnionyOkrag(reka2, receRozm.y, 0xff00);
    wypelnionaElipsa(ramie2, ramie2rozm, 0,180,41.5+90+15, RAMIE2KOLOR);
//    wypelnionaElipsa(strzalkowa2, strzalkowa2rozm, 0,180,alfaStrz2, STRZALKOWA2KOLOR );
    wypelnionaElipsa(strzalkowa2, promienie[17], 0,180,alfaStrz2, STRZALKOWA2KOLOR );

#define deg2rad(alfa) (M_PI*(alfa)/180)
    dlon2A = strzalkowa2 + 
		punkt( ((double)strzalkowa2rozm.y) * cos(deg2rad(90.0+alfaStrz2)), 
                       ((double)strzalkowa2rozm.y) * sin(deg2rad(90.0+alfaStrz2)));
    P.pisak(dlonieRozm.x);
//    linia(dlon2A,dlon2A+dlon2B,0xff);
//    liniaDo(dlon2A+dlon2C);
    linia(dlon2A,dlon2A+punkt(18,5),0xff);
    liniaDo(dlon2A+punkt(35,20));

    P.odswiez();
    K.sprawdzIWyjdzGdyKlawisz();
  }
  delta = 3;
  for(double alfaStrz2=alfa0strz2+AN_ZAKR-AN_KAT_B; alfaStrz2>alfa0strz2-AN_ZAKR-AN_KAT_B;alfaStrz2 -= ANIM_STEP) {
//    wypelnionaElipsa(strzalkowa2, strzalkowa2rozm + punkt(2,2), 0,360,alfaStrz2+ANIM_STEP, 0xffffff ); 
    wypelnionyOkrag(strzalkowa2 + punkt(10,0), ROZM_ANIM, 0xffffff);

  // tors
  P.pisak(torsRozm.x);
  linia(torsD,torsC,0xa04080);
  liniaDo(torsB);
  liniaDo(torsA);
  liniaDo(torsD);

  // wzor na torsie:
  P.pisak(torsDBrozm.y);
  linia(torsD,torsB,0);
  wypelnionaElipsa(wzorA, torsACrozm.x,torsACrozm.x, 0,180,110,0);
  wypelnionaElipsa(wzorC, torsACrozm.y,torsACrozm.y, 0,180,290,0);


    if(alfaStrz2>alfa0strz2-AN_KAT_B) delta -= ddelta; // 60 / 4 = 15, 15*.1 = 1.5
    else delta += ddelta;
    wypelnionyOkrag(reka2, receRozm.y, 0xff00);
    wypelnionaElipsa(ramie2, ramie2rozm, 0,180,41.5+90+15, RAMIE2KOLOR );
//    wypelnionaElipsa(strzalkowa2, strzalkowa2rozm, 0,180,alfaStrz2, STRZALKOWA2KOLOR );
    wypelnionaElipsa(strzalkowa2, promienie[17], 0,180,alfaStrz2, STRZALKOWA2KOLOR );

    dlon2A = strzalkowa2 + 
		punkt( ((double)strzalkowa2rozm.y) * cos(deg2rad(90.0+alfaStrz2)), 
                       ((double)strzalkowa2rozm.y) * sin(deg2rad(90.0+alfaStrz2)));
    P.pisak(dlonieRozm.x);
//    linia(dlon2A,dlon2A+dlon2B,0xff);
//    liniaDo(dlon2A+dlon2C);
    linia(dlon2A,dlon2A+punkt(18,5),0xff);
    liniaDo(dlon2A+punkt(35,20));
 
    P.odswiez();
    K.sprawdzIWyjdzGdyKlawisz();
  }
 }

  P.odswiez();
  K.czekajNaKlawisz();
}

