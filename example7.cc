#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika.cc"

#include <iostream>

#include "example-cfg.hh"

Projektor P(RX, RY);
Klawiatura K;

int main(int argc, char** argv) {
  P.czysc(0xffffff);
  // P.linia(10,10,90,90,0xff0000);
  int STEP=0;
  int REFRESH_STEP=0;
  
  if(argc>1) STEP=atoi(argv[1]);
  if(STEP==0) STEP=50;
  if(argc>2) REFRESH_STEP=atoi(argv[2]);
  if(REFRESH_STEP==0) REFRESH_STEP=16;

  std::cout << STEP << std::endl;
  
  for(int i = 10; i <= RX-10; i = i + 4) {
    P.linia(i,10, i,RY-10, i+(i<<8)+(i<<16) );
  }
  for(int j = 10; j <= RY-10; j = j + 4) {
    P.linia(10,j, RX-10,j, j+(j<<8)+(j<<16) );
  }
  for(int i = 14; i <= RX-14; i = i + 2*STEP) {
    for(int j = 14; j <= RY-14; j = j + 2*STEP) {
      P.Linia2(RX >> 1, 12,i,j,i+(j<<8)+((i+i)<<16),1 );
      P.Linia2(12, RY >> 1,i,j,i+(j<<8)+((i+i)<<16),0 );
      P.Linia2(RX >> 1, RY - 12,i,j,i+(j<<8)+((i+i)<<16),2 );
      P.Linia2(RX - 12, RY >> 1,i,j,i+(j<<8)+((i+i)<<16),5 );

      P.Linia2(i+STEP,j+STEP,RX >> 1, 12,i+(j<<8)+((i+i)<<16),1 );
      P.Linia2(i+STEP,j+STEP,12, RY >> 1,i+(j<<8)+((i+i)<<16),0 );
      P.Linia2(i+STEP,j+STEP,RX >> 1, RY - 12,i+(j<<8)+((i+i)<<16),3 );
      P.Linia2(i+STEP,j+STEP,RX - 12, RY >> 1,i+(j<<8)+((i+i)<<16),11 );
    }
    if( (i-10) % ( REFRESH_STEP * STEP ) == 0 ) P.odswiez();
  }

  P.odswiez();
  if(argc<=3) K.czekajNaKlawisz();
}
