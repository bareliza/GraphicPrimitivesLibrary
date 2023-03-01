#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

Projektor P(600,600);
Klawiatura K;

#define PUNKTOW (6)

class Edytor {
    public:
	int Punktow;
	int edytowanyPunkt;
	punkt punkty[PUNKTOW];
	int constraint[PUNKTOW][2];
  	punkt paa, pbb;
	
	Projektor *mojP;
	
	int i;

	void (*odrysuj)(Projektor*);

	void setProjektor(Projektor* p) {
		mojP = p;
	}

	void setOdrysuj(void (*o)(Projektor*)) {
		odrysuj=o;
	}
	
	Edytor(void) {
		edytowanyPunkt = -1;
		Punktow = PUNKTOW;
  		paa.x = 15;
  		paa.y = 15;
  		pbb.x = 7;
  		pbb.y = 7;
	}
	
	void obliczEkstraPunkty(void) {
		punkt zeroDoDwa = punkty[0]-punkty[2];
		printf("zeroDoDwa.x = %d, zeroDoDwa.y = %d\n", zeroDoDwa.x, zeroDoDwa.y);
		punkty[4].x = punkty[0].x;
		punkty[4].y = ( punkty[0].y + punkty[2].y ) / 2;
		punkty[5].x = punkty[1].x;
		punkty[5].y = punkty[1].y + 2 * abs ( punkty[1].y - punkty[4].y );
	}
	
	// do refaktoryzacji?: Choc wydajnosc to juz nie moj konik [...]
	void rysujPunkty(Projektor* p1) {
		obliczEkstraPunkty();
	
  		//(*p1).pisak(8);
		(*p1).pisak(2);
		for(i=0;i<Punktow;++i) {
		      (*p1).ramka(punkty[i]-pbb, paa, 0xffff80);
		}
	}

	void rysujPunkty(void) {
		rysujPunkty(mojP);
	}
};

Edytor E;

void rysujEkran(Projektor* p1) {
  	p1->czysc(0xffffff);
	p1->pisak(40);
	//p1->ramka(150,150,100,100,0xff00ff);
	//p1->ramka(E.punkty[0], E.punkty[1]-E.punkty[0],0xff00ff);
	p1->pisak(0);
	p1->linia(0,E.punkty[4].y,p1->wymiar.x,E.punkty[4].y,0xff);
	
	p1->linia(E.punkty[0],E.punkty[1],0xff0000,0,0);
	p1->linia(E.punkty[1],E.punkty[5],0xff0000,0,0);
	p1->linia(E.punkty[5],E.punkty[2],0xff0000,0,0);
	p1->linia(E.punkty[2],E.punkty[0],0xff0000,0,0);
}

SDL_Color tloCzcionki = { 0xff, 0xff, 0xff, 0};

#define ZOOM (5)
#define ZOOM_X (27)
#define ZOOM_Y (26)

void zoom(void) {
  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0,0,0,16);
  P.forecol = &tloCzcionki;
  while(1) {
    K.odswiez();
    P.prostokat(10,10,30,30,0xffffff);
    P.tekst2(10,10,"%d",&K.mysz.x);

    for(int i=0; i<ZOOM_X; ++i)
      for(int j=0; j<ZOOM_Y; ++j)
         P.prostokat(400 + i*ZOOM, 450 + j*ZOOM, ZOOM-1, ZOOM-1, P.KolorPunktu(K.mysz.x+i, K.mysz.y+j)); 
    P.odswiez();
    //K.sprawdzIWyjdzGdyKlawisz();
    K.wyjdzGdyKlawisz(SDLK_ESCAPE);
  }
}


int main(int argc, char** argv) {
  P.czysc(0xffffff);
  P.linia(10,10,90,90,0xff0000);
  P.odswiez();

  punkt mysz0, mysz1;
  mysz0.x = 0;
  mysz0.y = 0;
  mysz1.x = 0;
  mysz1.y = 0;
  
  int nrPunktu;
  nrPunktu = -1;

  int i1,i2;

  E.punkty[0] = punkt(100,100);
  E.punkty[1] = punkt(200,100);
  E.punkty[2] = punkt(100,200);
  E.punkty[3] = punkt(200,200);

  E.punkty[4] = punkt(250,250);
  E.punkty[5] = punkt(270,270);

  E.constraint[0][0]=0;
  E.constraint[1][0]=0;

  E.constraint[2][0]=2; // ten sam x co punktu ponizej
  E.constraint[2][1]=0; // z ktorego punktu druga wspolrzedna

  E.constraint[3][0]=2; // ten sam x co punktu ponizej
  E.constraint[3][1]=1; // jw. (z ktorego punktu itp...)

  E.rysujPunkty(&P);
  P.odswiez();

  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0, 0, 1, 32);
  E.setOdrysuj(&rysujEkran);
  (*E.odrysuj)(&P);
  
  while(K.klawisz != SDLK_z) {
	// TODO: poprawic odswiezanie w czasie edycji punktu
 	P.odswiez();
  	K.odswiez();
  	//rysujEkran(&P); 
  	// -> (*E.odrysuj)(&P);
  	
  	if(K.event.type == SDL_MOUSEMOTION && 
  	   ( (K.mysz.x != mysz0.x) || (K.mysz.y != mysz0.y) )
  	   ) {
  		//printf("mysz x: %d y: %d\n", K.mysz.x, K.mysz.y);
		mysz0 = K.mysz;
                 mysz1 = K.mysz;

  		if( E.edytowanyPunkt != -1 ) {
  		    switch( E.constraint[E.edytowanyPunkt][0] ) {
  		      case 0:
  			E.punkty[E.edytowanyPunkt] = mysz1;
  			for(i2=0;i2<E.Punktow;++i2)
  			  if(E.constraint[i2][1] == E.edytowanyPunkt) {
  			  	if(E.constraint[i2][0] == 1) E.punkty[i2].y = E.punkty[E.edytowanyPunkt].y; 
  			  	if(E.constraint[i2][0] == 2) E.punkty[i2].x = E.punkty[E.edytowanyPunkt].x;
  			  }
  			break;
  	              case 1:
			E.punkty[E.edytowanyPunkt].x = mysz1.x;
			break;
  	              case 2:
			E.punkty[E.edytowanyPunkt].y = mysz1.y;
			break;
		    }
  	              
  	            (*E.odrysuj)(&P);
  		    E.rysujPunkty(&P);
  			//P.odswiez();
  		}

  		P.prostokat(0, 0, 300, 80, 0xff80ff);
  		P.tekst2(15, 2, "%d", &(mysz1.x) );
  		P.tekst2(75, 2, "%d", &(mysz1.y) );
  		P.tekst2(75, 42, "%d", &(E.edytowanyPunkt) ); 
  		P.tekst2(225, 42, "%d", &(nrPunktu) );
  		//P.odswiez(0,0,300,40);  		
	}
  	if( (K.event.type == SDL_MOUSEBUTTONDOWN) && (nrPunktu != -1) ) {
		if( E.edytowanyPunkt == -1 ) {
			E.edytowanyPunkt = nrPunktu;
			K.zeruj();
		}
	}
	if( (K.event.type == SDL_MOUSEBUTTONDOWN) && E.edytowanyPunkt != -1) 
		E.edytowanyPunkt = -1;
	K.zeruj();

	nrPunktu = -1;
	P.pisak(0);
	for(i1=0;i1<E.Punktow;i1++) {
		punkt pcc;
		pcc = mysz0 - E.punkty[i1];
		if((abs(pcc.x) < 10) && (abs(pcc.y) < 10)) {
			P.ramka(E.punkty[i1] - E.pbb, E.paa, 0x00ff00);
			nrPunktu = i1;
		} else {
			P.ramka(E.punkty[i1] - E.pbb, E.paa, 0x0080ff);
		}
	}		
 }

  // K.czekajNaKlawisz();

  zoom();
}
