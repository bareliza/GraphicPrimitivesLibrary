#define _ALE_ZLY_STYL_BIBLIOTEK_

#include "grafika1.cc"

Projektor P(600,600);
Klawiatura K;

class Edytor {
    public:
	int Punktow;
	int edytowanyPunkt;
	punkt punkty[2];
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
		Punktow = 2;
  		paa.x = 15;
  		paa.y = 15;
  		pbb.x = 7;
  		pbb.y = 7;
	}
	
	// do refaktoryzacji?: Choc wydajnosc to juz nie moj konik [...]
	void rysujPunkty(Projektor* p1) {
  		(*p1).pisak(8);
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
	p1->ramka(E.punkty[0], E.punkty[1]-E.punkty[0],0xff00ff);
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

  int i1;

  E.punkty[0] = punkt(100,100);
  E.punkty[1] = punkt(200,200);

  E.rysujPunkty(&P);
  P.odswiez();

  P.otworzCzcionke("TerminusTTF-4.46.0.ttf", 0, 0, 1, 32);
  E.setOdrysuj(&rysujEkran);
  (*E.odrysuj)(&P);
  
  while(K.klawisz != SDLK_ESCAPE) {
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
  			E.punkty[E.edytowanyPunkt] = mysz1;
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
	P.pisak(2);
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

  K.czekajNaKlawisz();
}
