#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika.cc"

Projektor P(100,100);
Klawiatura K;

int main(int argc, char** argv) {
  P.czysc(0xffffff);
  P.linia(10,10,90,90,0xff0000);
  P.odswiez();
  K.czekajNaKlawisz();
}
