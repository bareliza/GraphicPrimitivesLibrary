#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

Projektor P(600,600);
Klawiatura K;

int main(int argc, char** argv) {
  P.czysc(0xffffff);
  P.pisak(64);
  P.linia(100,100,300,300,0xff00,0,0);
  //P.linia(523,146,513,155,0,0,0);
  //P.rysujPunkt4(523,146,0xff00,64);
  P.rysujPunkt4(300,100,0xff,64);
  P.linia(300,100,100,300,0xff0000,0,1);
 
  //P.linia(100,100,300,300,0xff00,0,0);
  //P.linia(523,146,513,155,0,0,0);
  //P.rysujPunkt4(523,146,0xff00,64);
  //P.rysujPunkt4(300,100,0xff,64);
  P.linia(500,250,300,500,0xff0000,0,1);
 

  P.linia(250,400,500,420,    0xff,0,1);
  P.linia(250,330,500,331,    0x7f,0,1);

 
  P.odswiez();
  K.czekajNaKlawisz();
  //P.Zapisz_BMP(
}
