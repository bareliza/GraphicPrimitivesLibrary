#ifdef _ALE_ZLY_STYL_BIBLIOTEK_
//#undef __cplusplus
#include "SDL/SDL.h"
//#define __cplusplus
#include <stdio.h>
#include <stdlib.h>
//#include <io.h>

#include <math.h>

//#include <windows.h>
//#include <winuser.h>

//#define M_PI 3.1415927
//#include <iostream.h>
// const static funkcja - co to mog³oby znaczyæ... 
// patrz error, gdy struct rysunek poprzedzimy const static
struct rysunek{
	int	 x;
	int	 y;
	int	 Bpp; /* 3:RGB, 4:RGBA */ 
	unsigned char 	 punkty[404 * 523 * 3 + 1];
};
struct wektor2w{
	int x, y;
	wektor2w(){}
	wektor2w(int xp, int yp){x=xp;y=yp;}
};
wektor2w operator +(const wektor2w& w1, const wektor2w& w2){
	return wektor2w(w1.x+w2.x,w1.y+w2.y);
}
wektor2w operator -(const wektor2w& w1, const wektor2w& w2){
	return wektor2w(w1.x-w2.x,w1.y-w2.y);
}
typedef wektor2w punkt;
typedef unsigned int kolor;

template <class A> class Stos{
	A* tresc;
	int rozmiarMinus1, poziom; 
public:	
	Stos(int rozmiar){
		tresc=new A[rozmiar];rozmiarMinus1=rozmiar-1;poziom=0;}
	~Stos(){if(tresc)delete[] tresc;}
	A zdejmij(){if(!poziom){printf("Pusty stos!\n");exit(-1);}
		return tresc[poziom--];}
	void wloz(A p){if(poziom<rozmiarMinus1){tresc[++poziom]=p;}
		else{printf("Pe³ny stos!\n");exit(-1);}}
	int pusty(){return !poziom;}
};
struct Klawiatura{
	SDL_Event event;
	int klawisz;

	void sprawdzIWyjdzGdyKlawisz(void){
		SDL_PollEvent( &event );
		switch( event.type ){
            case SDL_KEYDOWN:printf( "Key press detected\n" );exit(0);
            case SDL_MOUSEBUTTONDOWN:printf( "mouse press detected\n" );exit(0);
            case SDL_KEYUP:printf( "Key release detected\n" );break;
			default:break;
		}
	}
	void wyjdzGdyKlawisz(int klawisz0){
        if(klawisz0==klawisz)exit(0);
	}
	int sprawdzIzwroc1GdyKlawisz(void){
		SDL_WaitEvent( &event );
		klawisz=event.key.keysym.sym;
		switch( event.type ){
			case SDL_KEYDOWN:printf( "Key press detected\n" );return 1;
			case SDL_MOUSEBUTTONDOWN:printf( "mouse press detected\n" );return 1;
            case SDL_KEYUP:printf( "Key release detected\n" );return 1;
			default:return 0;
		}
	}
	
	void czekajNaKlawisz(void){
		while(!sprawdzIzwroc1GdyKlawisz());		
	}
	
	void odswiez(void){
		SDL_PollEvent( &event );
		if(event.type==SDL_KEYDOWN){ klawisz=event.key.keysym.sym; printf("EEE\n"); }
		if(event.type==SDL_KEYUP){klawisz=-1;printf("BLABLABLA\n");}
//		if(event.type==SDL_MOUSEMOVE)printf( "Mouse move\n");
	}
};

const int szerokosc_czcionki=6;
const int wysokosc_czcionki=20;

Stos<punkt> stos_punktow(512000);
class Projektor{
public:
	void initialize(int wymiar_x, int wymiar_y){
		printf("Program aktualnie obs³uguje tylko 32 bity\n");
		pioro=1;
		wymiar.x=wymiar_x;
		wymiar.y=wymiar_y; 
                // klipowanie, najwra@zliwsze, a zatem jest, ale podwojnie. 
                // Mo@zna tam, gdzie zahardkodowane kolory w kodzie klipowania wstawic return-y,
                // Co da wzrost wydajnosci, ale tylko dla istotnych procentowo przyci@e@c odcink@ow  
                xc0 = 5;
                yc0 = 5;
                xc1 = 5;
                yc1 = 5; // dalszy kod konstruktora zapozyczony z dokumentacji SDL
                
		/* Initialize the SDL library */
 		if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
			fprintf(stderr,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
			exit(1);
		}
		atexit(SDL_Quit);/* Clean up on exit */
		// Initialize the display in a 640x480 32-bit requesting a software surface 
		screen = SDL_SetVideoMode(wymiar.x, wymiar.y, 32,
		SDL_SWSURFACE);
		if ( screen == NULL ) {
			fprintf(stderr, "Couldn't set %d x %d x32 video mode: %s\n", 
            wymiar.x, wymiar.y,
			SDL_GetError());
			exit(1);
		}		
		//		if((czcionka = SDL_LoadBMP("C:\\Documents and Settings\\jarek\\Moje Dokumenty\\prg\\font.bmp")) == NULL) {
		//	fprintf(stderr, "Couldn't load font font.bmp: %s\n",
		//	SDL_GetError());
			//exit(1);
        }
//    
// Microsoft only:
//        HWND uchwytOkna=GetActiveWindow();
//        SetWindowPos(uchwytOkna,0,16,-6,0,0,1);
//
//	}
// public:
	SDL_Surface *screen, *czcionka;
	wektor2w wymiar; // wymiar malowanej powierzchni;
	Klawiatura* K;
	int pioro;

    char t[256];
	
	Projektor(void){} // initialize(512, 512);}
	Projektor(int wymiar_x, int wymiar_y){initialize(wymiar_x, wymiar_y);}
	Projektor(int wymiar_x, int wymiar_y, Klawiatura* K){
		initialize(wymiar_x, wymiar_y);
		this->K=K;
	}
	Projektor(int wymiar_x, int wymiar_y, Klawiatura& K){
		initialize(wymiar_x, wymiar_y);
		this->K=&K;
	}
	void tekst(int x, int y, char* format, void* ptr){
         int i,j,k;
         char c;
         
         i=0;
         while(format[i]!='%' && format[i]!=0)i++;
         if(format[i]=='%'){
             while(format[i]!='f' && format[i]!='d' && format[i]!=0)i++;
             if(format[i]=='f')sprintf(t, format, (double *)ptr);
             if(format[i]=='d')sprintf(t, format, (int *)ptr);
         }else sprintf(t, format);
         
         for(i=0;i<strlen(t);i++){
             c=t[i];
             if(t[i]>=97)c-=97;
             if(t[i]>=43)c-=43;
             if(c==32)c=0;
             for(j=0;j<wysokosc_czcionki;j++)
                 for(k=0;k<szerokosc_czcionki;k++)
                     rysujPunkt(x+i*szerokosc_czcionki+k, y+j,
                         ((char *)czcionka->pixels)
                             [szerokosc_czcionki*t[i]+k+j*czcionka->w]);
         }
        }
	void tekst(int x, int y, char* t){
         int i,j,k;
         char c;
         
         i=0;
         
         for(i=0;i<strlen(t);i++){
             c=t[i];
             if(c>=97)c-=97;
             if(c>65)c-=65;
             if(c>=43)c-=43;
             if(c==32)c=-1;
             for(j=0;j<wysokosc_czcionki;j++)
                 for(k=0;k<szerokosc_czcionki;k++)
                     rysujPunkt(x+i*szerokosc_czcionki+k, y+j,
                         czcionka_czytajPunkt(szerokosc_czcionki*(c+7)+k,j)
                     );
         }
        }

	void pisak(int i){pioro=i;}
	void czysc(){prostokat(0,0,wymiar.x-1,wymiar.y-1,0);}
	void czysc(int c){prostokat(0,0,wymiar.x-1,wymiar.y-1,c);}
	void odswiez(int x, int y, int xe, int ye){SDL_UpdateRect(screen,x,y,xe,ye);}
	void odswiez(void){SDL_UpdateRect(screen,0,0,wymiar.x,wymiar.y);}
	void wyswietl(void){SDL_UpdateRect(screen,0,0,wymiar.x,wymiar.y);}
	inline void rysujPunkt(int adres, unsigned int wartosc){
		((unsigned int*)screen->pixels)[adres]=wartosc;}
// grafika1.cc to plik do eksperymentow, 'wersja niestabilna' 
//      pioro o ksztalcie kola:
        inline void rysujPunkt2(int x, int y, unsigned int wartosc){
	        okrag(x,y,pioro,wartosc);}
  inline void rysujPunkt4(int x, int y, unsigned int wartosc, int grubosc){
	        okrag(x,y,grubosc,wartosc);}
//      pioro o ksztalcie kwadratu:  
        inline void rysujPunkt3(int x, int y, unsigned int wartosc){
	  	rysujPunkt(x,y,wartosc,pioro);}
           //        if(x>=0 && y>=0 && x<wymiar.x && y<wymiar.y)
           //          ((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
	inline void rysujPunkt(int x, int y, unsigned int wartosc){
	  //	rysujPunkt(x,y,wartosc,pioro);}
                  if(x>=0 && y>=0 && x<wymiar.x && y<wymiar.y)
                    ((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
	inline void rysujNieKlipowanyPunkt(int x, int y, unsigned int wartosc){
	    ((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
	inline unsigned int KolorPunktu(int x, int y){
                if(x>=0 && y>=0 && x<wymiar.x && y<wymiar.y)
	          return ( ((unsigned int*)screen->pixels)[x+y*wymiar.x] );
	          else return 0;}
	void rysujPunkt(int x, int y, unsigned int wartosc, int pioro){
		if(pioro>1)prostokat(x-(pioro+1)/2+1,y-(pioro+1)/2+1,pioro,pioro,wartosc);
		else if(x>=0 && y>=0 && x<wymiar.x && y<wymiar.y)
			((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
	void rysujPunkt(int x, int y, unsigned char r, unsigned char g, unsigned char b){
		rysujPunkt(x,y,(r<<16)|(g<<8)|b);}
	int czytajPunkt(int x, int y){return ((unsigned int*)screen->pixels)[x+y*wymiar.x];}
	int czcionka_czytajPunkt(int x, int y){
        return ((unsigned int*)czcionka->pixels)[x+y*(czcionka->w)];}
	void linia(punkt p1,punkt p2,unsigned int kolor){
		linia(p1.x,p1.y,p2.x,p2.y,kolor);
	}

        int xc0, xc1, yc0, yc1; // doda@c inicjalizacje w konstruktorze // dodane
  
#define CLIP0_X (0+xc0)
#define CLIP1_X (wymiar.x-xc1)
#define CLIP0_Y (0+yc0)
#define CLIP1_Y (wymiar.y-yc1)

// to tez bardzo nieelegancko
#define DOLNA_GRANICA_PIORA (8)
  
	void liniaPionowa(int x, int y0, int y1, unsigned int kolor)
    	{

		int tmp;
      		if (y0 > y1) { tmp = y0;y0 = y1;y1 = tmp; }
      		if (y0 < CLIP0_Y) y0 = CLIP0_Y;
      		if (y1 >= CLIP1_Y) y1 = CLIP1_Y - 1; // height - 1;

      		int start, stop;

      		start = y0; // rawStride * y0 + x;
      		stop  = y1; // rawStride * y1 + x;
//  rysujPunkt2 to eksperyment
      		do
			rysujPunkt(x, start++, kolor);
		while (start <= stop);
      	}

	void liniaPozioma(int y, int x0, int x1, unsigned int kolor)
    	{
		int tmp;
      		if (x0 > x1) { tmp = x0;x0 = x1;x1 = tmp; }
      		if (x0 < CLIP0_X) x0 = CLIP0_X;
      		if (x1 >= CLIP1_X) x1 = CLIP1_X - 1;

      		int start, stop;

      		start = x0; // rawStride * y + x0;
      		stop  = x1; // rawStride * y + x1;
//  rysujPunkt2 to eksperyment
           	do    // rawImage[start] = kolor;
		      	rysujPunkt(start++, y, kolor); // start++; // += rawStride;
      		while (start <= stop);
        }

	void liniaPionowa(int x,int y0,int y1,unsigned int kolor,int grubosc) {
#ifndef ROUND_ENDS
	  if(0) {
#else
	  if(grubosc >= DOLNA_GRANICA_PIORA) {
#endif	    
	    liniaPionowa2(x,y0,y1,kolor,grubosc);
	  } else {
	   for(int i=0;i<grubosc-1;i++)liniaPionowa(x+i-(grubosc>>1),y0,y1,kolor);
		// grubosc-1: no17 post17
	  }
	}

        void liniaPozioma(int y,int x0,int x1,unsigned int kolor,int grubosc) {
#ifndef ROUND_ENDS
	  if(0) {
#else
	  if(grubosc >= DOLNA_GRANICA_PIORA) {
#endif	    
	    liniaPozioma2(y,x0,x1,kolor,grubosc);
	  } else {
	   for(int i=0;i<grubosc-1;i++)liniaPozioma(y+i-(grubosc>>1),x0,x1,kolor);
		// grubosc-1: no17 post17
	  }
	} 

  void liniaPionowa2(int x, int y0, int y1, unsigned int kolor, int grubosc) {
		int tmp;
      		if (y0 > y1) { tmp = y0;y0 = y1;y1 = tmp; }
      		if (y0 < CLIP0_Y) y0 = CLIP0_Y;
      		if (y1 >= CLIP1_Y) y1 = CLIP1_Y - 1; // height - 1;
      		int start, stop;
      		start = y0;
      		stop  = y1;
//  rysujPunkt2 to eksperyment
      		do
		  rysujPunkt4(x, start++, kolor, grubosc >> 1);
		while (start <= stop);
      	}
  void liniaPozioma2(int y, int x0, int x1, unsigned int kolor, int grubosc) {
		int tmp;
      		if (x0 > x1) { tmp = x0;x0 = x1;x1 = tmp; }
      		if (x0 < CLIP0_X) x0 = CLIP0_X;
      		if (x1 >= CLIP1_X) x1 = CLIP1_X - 1;
      		int start, stop;
      		start = x0; 
      		stop  = x1; 
//  rysujPunkt2 to eksperyment
           	do    
		  rysujPunkt4(start++, y, kolor, grubosc >> 1); 
      		while (start <= stop);
        }

    /* Klipowanie: gorna krawedz. zalozenie: y0 < y1.

                    x0,y0
                    |\
                /   | \
              dOut  |  \
                \ / |   \
                  __|____\xIn_____ y_clip0
                 dy |xOut \ | dIn
                  \ |__dx__\|
                             x1,y1

       xOut / dOut = dx / dy
       xOut = dOut * dx / dy

       x0=0 (x_clip0)
       x0=x0+yOut

       uwaga na dOut, dx > 16 bitow, 32767
   */
  int tmpPioro;
// grafika1.cc to plik do eksperymentow, 'wersja niestabilna' 
  void linia4(int x0, int y0, int x1, int y1, unsigned int kolor) {
    linia_wersja_schodki(x0,y0,x1,y1,kolor);
    if ( pioro >= DOLNA_GRANICA_PIORA ) {
      tmpPioro = pioro;
      pioro = (tmpPioro << 1);
      linia(x0,y0,x1,y1,kolor/2);
      pioro = tmpPioro;
    }
  };
  void linia1(int x0, int y0, int x1, int y1, unsigned int kolor) {
    if ( pioro >= DOLNA_GRANICA_PIORA && ((x0 == x1) || (y0 == y1)) ) {
      tmpPioro = pioro;
      pioro = (tmpPioro << 1);
      linia(x0,y0,x1,y1,kolor);
      pioro = tmpPioro;
    }
    linia_wersja_schodki(x0,y0,x1,y1,kolor);
  };
// grafika1.cc to plik do eksperymentow, 'wersja niestabilna' 
  void linia_wersja_schodki(int x0, int y0, int x1, int y1, unsigned int kolor){
	      	// Proste klipowanie
	      	if ((x0 <  CLIP0_X && x1 <  CLIP0_X) ||
		    (x0 >= CLIP1_X && x1 >= CLIP1_X) ||
	   	    (y0 <  CLIP0_Y && y1 <  CLIP0_Y) ||
		    (y0 >= CLIP1_Y && y1 >= CLIP1_Y)) kolor = 0xb0ffb0;
		  // return;
		
	        if (x0 == x1) {
	                liniaPionowa(x0, y0, y1, kolor);
			return;
		}
		if (y0 == y1) {
		       liniaPozioma(y0, x0, x1, kolor);
		       return;
      		}

		int dx,dy,tmp,fract,xOut,yOut,dOut;

		dx=abs(x1-x0);
		dy=abs(y1-y0);

		/* */
	      	if (! ((x0 <  CLIP0_X && x1 <  CLIP0_X) ||
		       (x0 >= CLIP1_X && x1 >= CLIP1_X) ||
	   	       (y0 <  CLIP0_Y && y1 <  CLIP0_Y) ||
		       (y0 >= CLIP1_Y && y1 >= CLIP1_Y)) )
		  { 
		    /* */
		// klipowanie kod1
		if(y0 > y1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
		if(y0 < CLIP0_Y) {
		  dOut = CLIP0_Y - y0;
		  xOut = dOut * dx / dy;
		  y0 = CLIP0_Y;
		  x0 = x0 + ( (x1 > x0) ?  xOut : -xOut );
		}
		// klipowanie kod3
		/*if(y0 > y1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		  }*/
		if(y1 >= CLIP1_Y) {
		  dOut = y1 - CLIP1_Y;
		  xOut = dOut * dx / dy;
		  y1 = CLIP1_Y - 1;
		  x1 = x1 + ( (x1 < x0) ?  xOut : -xOut );
		}
		/* */
		// klipowanie kod2
		if(x0 > x1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
		if(x0 < CLIP0_X) {
		  dOut = CLIP0_X - x0;
		  yOut = dOut * dy / dx;
		  x0 = CLIP0_X;
		  y0 = y0 + ( (y1 > y0) ?  yOut : -yOut );
		}
		// klipowanie kod4
		/*if(x0 > x1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		  }*/
		if(x1 >= CLIP1_X) {
		  dOut = x1 - CLIP1_X;
		  yOut = dOut * dy / dx;
		  x1 = CLIP1_X - 1;
		  y1 = y1 + ( (y1 < y0) ?  yOut : -yOut );
		}
		/* */
		  } 
		/* */
		if ((x0 < CLIP0_X && y1 < CLIP0_Y) ||
		    (x1 < CLIP0_X && y0 < CLIP0_Y) ||

		    (x0 >= CLIP1_X && y1 >= CLIP1_Y) ||
		    (x1 >= CLIP1_X && y0 >= CLIP1_Y) ||

		    (x0 < CLIP0_X && y1 >= CLIP1_Y) ||
		    (x1 < CLIP0_X && y0 >= CLIP1_Y) ||

		    (x0 >= CLIP1_X && y1 < CLIP0_Y) ||
		    (x1 >= CLIP1_X && y0 < CLIP0_Y)) kolor = 0x8080ff;

		if ((x0 <  CLIP0_X && x1 <  CLIP0_X) ||
		    (x0 >= CLIP1_X && x1 >= CLIP1_X) ||
	   	    (y0 <  CLIP0_Y && y1 <  CLIP0_Y) ||
		    (y0 >= CLIP1_Y && y1 >= CLIP1_Y)) kolor = 0xffd0ff;
		// return;


		if(dx>dy){
			if(x0>x1){
				tmp=x0;x0=x1;x1=tmp;
				tmp=y0;y0=y1;y1=tmp;
			}
			dx=x1-x0; // Na razie nie wiem, jak to optymalniej liczyc, (pomijajac powtórne liczenie dx,dy)
			dy=y1-y0; // to zreszta tylko 2 odejmowania i przypisania wiecej na jedna linie
			if(dx)fract=(dy<<16)/dx;
			else fract=0;
			//if(y1>y0)fract=-fract;
			y0<<=16;
			y0 += (1 << 15);
			for(; x0 <= x1 ; x0++) {
// grafika1.cc to plik do eksperymentow, 'wersja niestabilna' 
				rysujPunkt2(x0,y0>>16,kolor);
				y0+=fract;
			}	
		}else{
			if(y0>y1){
				tmp=x0;x0=x1;x1=tmp;
				tmp=y0;y0=y1;y1=tmp;
			}
			dx=x1-x0; // Komentarz jak wy¿ej przy liczeniu dx,dy
			dy=y1-y0;
			if(dy)fract=(dx<<16)/dy;
			else fract=0;
			//if(x1>x0)fract=-fract;
			x0<<=16;
			x0 += (1 << 15);
			for(; y0<=y1 ; y0++){
// grafika1.cc to plik do eksperymentow, 'wersja niestabilna' 
				rysujPunkt2(x0>>16,y0,kolor);
				x0+=fract;
			}
		}
	}

    void linia(int x0, int y0, int x1, int y1, unsigned int kolor, int rozszerz = 0, int kropki = 1){
      	// printf("%d$%d$%d$%d$",x0,y0,x1,y1);
	double aD3r, aD3rPrim, r;
	aD3r = M_PI+atan2(x0-x1,y0-y1);
	pioro1 = pioro;
        if(pioro>1){ // zle kodowanie: magic number, patrz wyjasnienie nizej
	        if((aD3r > M_PI/4 && aD3r <=M_PI-M_PI/4)||(aD3r > M_PI/4+M_PI && aD3r <= 2*M_PI-M_PI/4)) {
	        	pioro = abs(pioro1 / cos(M_PI/2-aD3r));
    		} else {
      			pioro = abs(pioro1 / cos(aD3r)); // f(0) = 1/2; f(45) = sqrt(2)/2 
    		}
    	}
	if(rozszerz){
		//printf("PRZED:rozszerz=%d; aD3r=%f; %d,%d,%d,%d\n", rozszerz, aD3r, x0,y0,x1,y1);
		x0-=sin(aD3r)*rozszerz;
		y0-=cos(aD3r)*rozszerz;
		x1+=sin(aD3r)*rozszerz;
		y1+=cos(aD3r)*rozszerz;
	}
	
	// aD3r mod M_PI/4 == M_PI/4 --> rozszerz dodatkowo o 10% (5%) (n%):
	
#define rad2deg(a) (180.0*a/M_PI)
	if( pioro > 1 && 0 ) {
		aD3rPrim = aD3r;
		while(aD3rPrim >= M_PI/2) aD3rPrim -= M_PI/2;
		// aD3r' zawarte w [ 0°, 90° ) 
		// 45° -> n% 0° i 90° -> 0%
		//printf("%3.3f ", rad2deg(aD3rPrim));		
		aD3rPrim = aD3rPrim / (M_PI/2);
		//printf("[0, 1) %3.3f ", aD3rPrim);		
		// .. zawarte w [0, 1)
		// 
		//    /     =>
		//   /          /\
		//

//#define abs11(a) ( ((a)<0) ? (-a) : (a) )
		aD3rPrim = 2 * ( 0.5-abs(aD3rPrim-0.5) );
		//printf ("%3.3f\n", aD3rPrim);

		// dla 60 pixeli odleglosci
		// 8 pixeli korekcji
		r = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
//#define KANCERA2 (60 * (aD3rPrim * 8 + 1 * (aD3r > M_PI)) / r)
//#define KANCERA3 (60 * (aD3rPrim * 8 - 1 * (aD3r > M_PI)) / r)

#define KANCERA2 ( (aD3rPrim * 8 + 1 * (aD3r > M_PI)) )
#define KANCERA3 ( (aD3rPrim * 8 - 1 * (aD3r > M_PI)) )
		x0-=sin(aD3r)*KANCERA2;
		y0-=cos(aD3r)*KANCERA2;
		x1+=sin(aD3r)*KANCERA3;
		y1+=cos(aD3r)*KANCERA3;
	}
	
	
/*	if(kropki){
		rysujPunkt4(x0-1,y0-1,kolor,(pioro1)/2);
		rysujPunkt4(x1-1,y1-1,kolor,(pioro1)/2);
	}
*/
      	Linia2(x0, y0, x1, y1, kolor, pioro, rozszerz, kropki);
	pioro = pioro1;
    }
  
    double pioro1;
	// g    _g   _h
	// 1 :   2    1
	// 2 :   2    0
	// 3 :   3    1
	// 4 :   3    0
	// 5 :   4    1
        // 6 :   4    0
    void Linia2(int x0, int y0, int x1, int y1, unsigned int kolor, int grubosc,
                int rozszerz, int kropki) {
	_Line(x0, y0, x1, y1, kolor, (grubosc + 2) >> 1, (grubosc + 1) & 1, rozszerz, kropki);
    }
    /// <summary>
    /// Ogólna linia, NIE optymalizowana dla poziomych i pionowych linii.7
    /// </summary>
    /// <param name="x0">Współrzędna pozioma początku</param>
    /// <param name="y0">Współrzędna pionowa początku</param>
    /// <param name="x1">Współrzędna pozioma końca</param>
    /// <param name="y1">Współrzędna pionowa końca</param>
    /// <param name="kolor">kolor punktu - najstarszy bajt to przeźroczystość, dla pełnego koloru 0xff</param>
    /// <param name="grubosc">określa grubość linii, 
    /// rzeczywista grubość wynosi 2*wartość+1-half
    /// (0 -> 1, 2 -> 3, 3 -> 5 itd.)</param>
    /// <param name="half">Modyfikator grubosci, zmniejsza o jeden lub nie, patrz parametr "grubosc".</param>
    // grubosc = 0 -> 1 piksel, 1 -> 3 piksele, 2 -> 5 pikseli, ...
    void _Line(int x0, int y0, int x1, int y1, unsigned int kolor, int grubosc, int half, 
               int rozszerz, int kropki)
    {
      // Console.WriteLine($"DEBUG: _Line( {x0}, {y0}, {x1}, {y1}, {kolor}, {grubosc}, {half});");
      if ((x0 < CLIP0_X && x1 < CLIP0_X) || (x0 >= CLIP1_X && x1 >= CLIP1_X) || 
	  (y0 < CLIP0_Y && y1 < CLIP0_Y) || (y0 >= CLIP1_Y && y1 >= CLIP1_Y))
	{
#ifdef KLIPOWANIE
		return;
#endif	
		kolor = 0xb0ffb0;
	} // return; // Proste klipowanie
#define KROPKI_KOREKCJA (1.1)
//-half)
	        if (x0 == x1) {
	        //  if(kropki){
 		//	rysujPunkt4(x0-1,y0-1-rozszerz*((y0>y1)?(-1):1),kolor,pioro1/2); 
 		//	rysujPunkt4(x0-1,y1-1+rozszerz*((y0>y1)?(-1):1),kolor,pioro1/2);
	        //  }
			if(kropki) {
				rysujPunkt4(x0,y0-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
				rysujPunkt4(x1,y1-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
			}
			liniaPionowa(x0, y0, y1, kolor, 2*grubosc+1-half);
		  //	printf("\n");
			return;
		}
		if (y0 == y1) {
		//  if(kropki){
 		//	rysujPunkt4(x0-1-rozszerz*((x0>x1)?(-1):1),y0-1,kolor,pioro1/2); 
 		//	rysujPunkt4(x1-1+rozszerz*((x0>x1)?(-1):1),y0-1,kolor,pioro1/2);
 		//  }
			if(kropki) {
				rysujPunkt4(x0,y0-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
				rysujPunkt4(x1,y1-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
			}
			liniaPozioma(y0, x0, x1, kolor, 2*grubosc+1-half);
		  //	printf("\n");
		 	return;
      		}

		int dx, dy, tmp, fract, wi, xOut, yOut, dOut,
		    x00, x11, y00, y11, fract1, mod0, mod1, flaga;
		double alfa3, alfa4, alfa3p, func, dfunc;
		double aD3, aD3rad, x, d;
		
		int x0a,y0a,x1a,y1a;
		x0a=x0;x1a=x1;y0a=y0;y1a=y1;
		
		aD3rad = M_PI+atan2(x0-x1,y0-y1);
		aD3 = 180.0*aD3rad/M_PI;
		// printf("-%d-",(int)(aD3));
	
	        if(pioro1>1){  // Zly styl kodowania - magic number. Okresla limit grubosci,
	        // dla ktorego program wchodzi w temat krawedzi zewnetrznych rysowanej linii
	        // "tych krotszych" bokow prostokata
 	        	if((aD3 > 45 && aD3 <=135) || (aD3 > 45+180 && aD3 <= 135+180)) {
                   		x = abs(pioro1 / cos(M_PI/2-aD3rad));
    			} else {
      		  		x = abs(pioro1 / cos(aD3rad)); // f(0) = 1/2; f(45) = sqrt(2)/2 
    			}
    		} else {
    			x = 0;
    		}
    		
    		if(aD3 > 45 && aD3 <= 90) {
      		  d = x * cos(aD3rad) / 2;
    		} else {
      		  if (aD3 >= 0 && aD3 <= 45) { 
        	    d = x * cos(M_PI/2-aD3rad) / 2;    
      		  } else {
        	    if (aD3 > 90 && aD3 <= 135) {
          	      d = - x * cos(aD3rad) / 2; // ???????
        	    } else {
          	      if (aD3 > 135 && aD3 <= 180) {
            	         d = x * cos(M_PI/2 - aD3rad) / 2;
          	      } else {      
            	        if (aD3 > 180 && aD3 <= 225) {
              	          d = - x * cos(M_PI/2-aD3rad) / 2;
            	        } else {
              	          if (aD3 > 225 && aD3 <= 270) {
		            d = - x * cos(aD3rad) / 2;
        	          } else {  
		            if (aD3 > 270 && aD3 <= 315) {
		              d = x * cos(aD3rad) / 2;
		            } else { // 315 .. 360
		              d = - x * cos(M_PI/2-aD3rad) / 2; // ???????
		            }
		          }
		        }
          	      }
		    }
		  }
		}

    		x0-=d*sin(aD3rad);
		y0-=d*cos(aD3rad);
		x1+=d*sin(aD3rad);
		y1+=d*cos(aD3rad);
		
		dx=abs(x1-x0);
		dy=abs(y1-y0);

		/* */
	      	if (! ((x0 <  CLIP0_X && x1 <  CLIP0_X) ||
		       (x0 >= CLIP1_X && x1 >= CLIP1_X) ||
	   	       (y0 <  CLIP0_Y && y1 <  CLIP0_Y) ||
		       (y0 >= CLIP1_Y && y1 >= CLIP1_Y)) )
		  { 
		    /* */
		// klipowanie kod1
		if(y0 > y1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
		if(y0 < CLIP0_Y) {
		  dOut = CLIP0_Y - y0;
		  xOut = dOut * dx / dy;
		  y0 = CLIP0_Y;
		  x0 = x0 + ( (x1 > x0) ?  xOut : -xOut );
		}
		// klipowanie kod3
		/*if(y0 > y1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		  }*/
		if(y1 >= CLIP1_Y) {
		  dOut = y1 - CLIP1_Y;
		  xOut = dOut * dx / dy;
		  y1 = CLIP1_Y - 1;
		  x1 = x1 + ( (x1 < x0) ?  xOut : -xOut );
		}
		/* */
		// klipowanie kod2
		if(x0 > x1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
		if(x0 < CLIP0_X) {
		  dOut = CLIP0_X - x0;
		  yOut = dOut * dy / dx;
		  x0 = CLIP0_X;
		  y0 = y0 + ( (y1 > y0) ?  yOut : -yOut );
		}
		// klipowanie kod4
		/*if(x0 > x1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		  }*/
		if(x1 >= CLIP1_X) {
		  dOut = x1 - CLIP1_X;
		  yOut = dOut * dy / dx;
		  x1 = CLIP1_X - 1;
		  y1 = y1 + ( (y1 < y0) ?  yOut : -yOut );
		}
		/* */
		  } 
		/* */
		if ((x0 < CLIP0_X && y1 < CLIP0_Y) ||
		    (x1 < CLIP0_X && y0 < CLIP0_Y) ||

		    (x0 >= CLIP1_X && y1 >= CLIP1_Y) ||
		    (x1 >= CLIP1_X && y0 >= CLIP1_Y) ||

		    (x0 < CLIP0_X && y1 >= CLIP1_Y) ||
		    (x1 < CLIP0_X && y0 >= CLIP1_Y) ||

		    (x0 >= CLIP1_X && y1 < CLIP0_Y) ||
		    (x1 >= CLIP1_X && y0 < CLIP0_Y)) {
#ifdef KLIPOWANIE
			return;
#endif				
			kolor = 0x8080ff;
		}
		if ((x0 <  CLIP0_X && x1 <  CLIP0_X) ||
		    (x0 >= CLIP1_X && x1 >= CLIP1_X) ||
	   	    (y0 <  CLIP0_Y && y1 <  CLIP0_Y) ||
		    (y0 >= CLIP1_Y && y1 >= CLIP1_Y)) {
#ifdef KLIPOWANIE
			return;
#endif	
			kolor = 0xffd0ff;
		}
		// return;

		///////////// BAD CODING - redundancja kodu klipujacego
////////////      int dx, dy, tmp, fract, wi;
      dx = abs(x1 - x0);
      dy = abs(y1 - y0);

      // Lock();
      if (dx > dy) {
	if (x0 > x1) {
	  tmp = x0;x0 = x1;x1 = tmp; // XCHG x0, x1
	  tmp = y0;y0 = y1;y1 = tmp; // XCHG y0, y1
	}	
	dx = x1 - x0;
	dy = y1 - y0;

	if (dx != 0) fract = (dy << 16) / dx;
	else fract = 0; 
/////////////////////////////////////////////////////////////////// dx > dy
        // 4    __
        //  `\/2 '
#define deg(alfa) (alfa*180/M_PI)
        alfa3 = atan2(dx,dy);
	if(fract<0) { // 45°-90° -> 90°-45°; 45° -> 90°, 90° -> 45°
	  alfa3 = M_PI/2-(alfa3-M_PI/8); } // jest: 0-90 -> 90-0; 0 -> 90, 90 -> 0
	
        alfa4 = alfa3 - M_PI/4;
        func = alfa4/(M_PI/4); // [0°, 45°] -> [0, 1]
        func = func * 7.0;
        dfunc = .8 * M_PI/60 * func - M_PI/60;
        alfa3p = alfa3 + 1 * dfunc - (deg(alfa4) > 7.0) * M_PI/24;
        if(fract<0) { //  printf("~");
          alfa3p+=M_PI/2;
	  if(alfa3p > M_PI/4) alfa3p -= M_PI*5/180;
        }  
	if(alfa3p > M_PI/2) alfa3p = M_PI/2-.0005;
        fract1 = (int)((1<<16)*sqrt(tan(alfa3p)));

	y0 <<= 16;
	y0 += (1 << 15);

// dlugosc wystajacego, mniej kancery, pierwsze dla delty ujemnej.
#define KANCERA01 (1)
#define KANCERA11 (-2)	
#define KANCERA12 (-1)
// jw. dla dy>dx
#define KANCERA01Y (1)
#define KANCERA11Y (0)	
#define KANCERA12Y (1)
// dodatnie, np. 6 eliminuje kancere w 100%, ale maleje dlugosc
#define KANCERA1 (1)
#define KANCERA0 (1)
// jw. dla dy>dx
#define KANCERA1Y (4)
#define KANCERA0Y (4)
	x00 = x0-4-KANCERA01*(fract<0)-KANCERA11+KANCERA12*(deg(alfa4) > 8.0 );
	x11 = x1+4+KANCERA01*(fract<0)+KANCERA11-KANCERA12*(deg(alfa4) > 20.0);
///////////////////////////////////////////////////////////////////	
/* * /
        printf("a3: %3.3f a4: %3.3f a3p: %3.3f f: %3.3f df: %3.3f df°: %3.3f fr1: %3.3f\n", 
               deg(alfa3), deg(alfa4), deg(alfa3p), func, dfunc, deg(dfunc), fract1/(1.0*(1<<16)));
/ * */
        // alfa3 = 45° -> f = 0 ((-1)) (0) .5 .3
        // alfa3 = 90° -> sqrt(f) = 2 (1)

	// Na czym polega trudno@s@c z "kropkami": niepewno@s@c tych minus i plus, czyli
	// fakt, ze z pewnych powodow x0 mo@ze w tym miejscu by@c zamienione z x1a,
	// a x0 jest juz r@ozne, bo przesuni@ete o d[elte] zwi@azan@a z rysowaniem grubosci kreskami
	// pionowymi b@ad@@z poziomymi.
	//
	// To co innego. To pierwiastek z dwóch dla 45° i jedynka dla 90°
	// i druga rzecz - to powi@azanie tego pierwszego komentarza z tym obecnym:
	// Bo to nie tak prosto, @ze mno@zone przez cosinus / i lub sinus
	
	// if(kropki) rysujPunkt4(x0a-rozszerz*sin(aD3rad),y0a-rozszerz*cos(aD3rad),kolor,pioro1/2);	
	if(kropki) rysujPunkt4(x0a,y0a-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
        
	for (; x0 <= x1; x0++) {
	    if( true && ( grubosc != 0 ) )  //   W Y G L A D Z A N I E
	    {
#define max11(a,b) ( (a) < (b) ? (b) : (a) )
		mod0 = max11( 0, (grubosc - 1) - ( ( fract1*(((int)(x0-x00))) )>>16 ) + KANCERA0 ); 
		mod1 = max11( 0, ((fract1*(x0 - x11))>>16 ) + KANCERA1 + (grubosc - 1 + half) );
		if(fract<0){
			mod0 = max11( 0, ((fract1*(x0 - x11))>>16 ) + KANCERA0 + (grubosc - 1 + half) );
			mod1 = max11(0, grubosc - 1 - ( ( (int)( fract1 * (x0 - x00) )) >> 16 ) + KANCERA1 );
		}
		// modyfikator = grubosc - 1 dla x0 == x00
                // modyfikator = 0; // dla x0 == x00 + int(sqrt(grubosc));		
	      // Console.WriteLine(KolorPunktu( x0,  grubosc - half + ( y0 >> 16 ) ) );
		if(!mod1) {
			rysujPunkt( x0,  grubosc - half + (y0 >> 16),
				kolorDopelniajacy( kolor,
					( 0xffff - ( y0 & 0xffff ) )
					, KolorPunktu( x0,  grubosc - half + ( y0 >> 16 ) )
				)
			); // TODO: DONE. NullPointerException:: zamienic ( <-> ) _b.GetPixel <-> WezPunkt(...) - klipowany
			}
		if(!mod0) {
			rysujPunkt( x0, -grubosc + (y0 >> 16),
				kolorDopelniajacy( kolor,
					( y0 & 0xffff )
					, KolorPunktu( x0, -grubosc + ( y0 >> 16 ) ) 
				)
			);
			}
		for (wi = -grubosc + 1 + 2*mod0; wi <= grubosc - 1 - half - 2*mod1; wi++)
		rysujPunkt(x0, wi + (y0 >> 16), kolor);
	    }
	    y0 += fract;
	}

	// if(kropki) rysujPunkt4(x1a+rozszerz*sin(aD3rad),y1a+rozszerz*cos(aD3rad),kolor,pioro1/2);
	if(kropki) rysujPunkt4(x1a,y1a-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);

      }
      else {
	if (y0 > y1) {
	  tmp = x0;x0 = x1;x1 = tmp; // XCHG x0, x1
	  tmp = y0;y0 = y1;y1 = tmp; // XCHG y0, y1
	}
	dx = x1 - x0;
	dy = y1 - y0;
	if (dy != 0) fract = (dx << 16) / dy;
	else fract = 0;

/////////////////////////////////////////////////////////////////// dy > dx
        // 4    __
        //  `\/2 '
#define deg(alfa) (alfa*180/M_PI)
        alfa3 = atan2(dy,dx);
 	if(fract<0) {// 180° -> 0°; 135° -> 45°; 0°-45° -> 45°-0°
 		alfa3=M_PI-alfa3; }

        alfa4 = alfa3 - M_PI/4;
        func = alfa4/(M_PI/4); // [0°, 45°] -> [0, 1]
        func = func * 7.0;
        dfunc = .8 * M_PI/60 * func - M_PI/60;
        alfa3p = alfa3 + 1 * dfunc - (deg(alfa4) > 7.0) * M_PI/24;
 	if(fract<0) {
	  //alfa3p = 22.5*M_PI/180;
          //alfa3p+=M_PI/4;
	  //if(alfa3p > M_PI/4) alfa3p -= M_PI*5/180;		
	  //alfa3p = M_PI/2-alfa3p;
 	}
 	alfa3p += M_PI*2/180;
	if(alfa3p > M_PI/2) alfa3p = M_PI/2-.0005;
        fract1 = (int)((1<<16)*sqrt(tan(alfa3p)));
	x0 <<= 16;
	x0 += (1 << 15);

	y00 = y0-4-KANCERA01Y*(fract<0)-KANCERA11Y+KANCERA12Y*(deg(alfa4) > 8.0 );
	y11 = y1+4+KANCERA01Y*(fract<0)+KANCERA11Y-KANCERA12Y*(deg(alfa4) > 20.0);
///////////////////////////////////////////////////////////////////	
/* * /	
        printf("a3: %3.3f a4: %3.3f a3p: %3.3f f: %3.3f df: %3.3f df°: %3.3f fr1: %3.3f\n", 
               deg(alfa3), deg(alfa4), deg(alfa3p), func, dfunc, deg(dfunc), fract1/(1.0*(1<<16)));
/ * */
        // alfa3 = 45° -> f = 0 ((-1)) (0) .5 .3
        // alfa3 = 90° -> sqrt(f) = 2 (1)
	//y00 = y0;
	
	// if(kropki) rysujPunkt4(x0a-rozszerz*sin(aD3rad),y0a-rozszerz*cos(aD3rad),kolor,pioro1/2);
	if(kropki) rysujPunkt4(x0a,y0a-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);
	//if(kolor == 0) kolor = 0xff0000;
	for (; y0 <= y1; y0++) {
	    if( true && ( grubosc != 0 ) )  //   W Y G L A D Z A N I E
	    {
		mod0 = max11( 0, (grubosc - 1) - ( ( fract1*(((int)(y0-y00))) )>>16 ) + KANCERA0Y ); 
		mod1 = max11( 0, ((fract1*(y0 - y11))>>16 ) + KANCERA1Y + (grubosc - 1 + half) );
		if(fract<0){
			//if(kolor == 0xff0000) kolor = 0xff00;
			mod1 = max11( 0, (grubosc - 1) - ( ( (int)( fract1*(((int)(y0-y00))) ))>>16 ) + KANCERA1Y ); 
			mod0 = max11( 0, ((fract1*(y0 - y11))>>16 ) + KANCERA0Y + (grubosc - 1 + half) );
		}
		// modyfikator = grubosc - 1 dla x0 == x00
                // modyfikator = 0; // dla x0 == x00 + int(sqrt(grubosc));		
	      // Console.WriteLine(KolorPunktu( x0,  grubosc - half + ( y0 >> 16 ) ) );
		if(!mod1) {
			rysujPunkt( grubosc - half + (x0 >> 16), y0,
				kolorDopelniajacy( kolor,
					( 0xffff - ( x0 & 0xffff ) )
					, KolorPunktu( grubosc - half + (x0 >> 16),  y0 )
				)
			); // TODO: DONE: NullPointerException:: zamienic ( <-> ) _b.GetPixel <-> WezPunkt(...) - klipowany
		}
		if(!mod0) {
			rysujPunkt( -grubosc + (x0 >> 16), y0,
				kolorDopelniajacy( kolor,
					( x0 & 0xffff )
					, KolorPunktu( -grubosc + (x0 >> 16), y0 )
				) 
			);
			}
		
		for (wi = -grubosc + 1 + 2*mod0; wi <= grubosc - 1 - half - 2*mod1; wi++)
		    rysujPunkt(wi + (x0 >> 16), y0, kolor);
	    }
	    x0 += fract;
	}

	// if(kropki) rysujPunkt4(x1a+rozszerz*sin(aD3rad),y1a+rozszerz*cos(aD3rad),kolor,pioro1/2);
	if(kropki) rysujPunkt4(x1a,y1a-half,kolor,(pioro1+KROPKI_KOREKCJA)/2);

      }
      // Unlock();
    }

    /// <summary>
    /// Zakladany rozklad skladowych:
    ///   ABGR: 0xAaBbGgRr - alfa. blue. green. red.
    /// </summary>
  
#define COLOR_R(k) (         (k & 0xff) )
#define COLOR_G(k) ( ((k >>  8) & 0xff) )
#define COLOR_B(k) ( ((k >> 16) & 0xff) )
  int kolor2r(unsigned int k) { return COLOR_R(k); } 
  int kolor2g(unsigned int k) { return COLOR_G(k); } // ( ((k >>  8) & 0xff) );}
  int kolor2b(unsigned int k) { return COLOR_B(k); } // ( ((k >> 16) & 0xff) );}
  
    // inline?
    /* */
      inline unsigned int r2kolor(unsigned int r) { return ( r ); }
      inline unsigned int g2kolor(unsigned int g) { return ( g << 8 ); }
      inline unsigned int b2kolor(unsigned int b) { return ( b << 16 ); }
    /* */

    // point /in ( 0x0000 .. 0xffff ), 0x0000 -> s0; 0xffff -> s1
    int skladowaDopelniajaca(int s0, int s1, int point)	{
      return ( ((s0 * (0xffff - point) + s1 * point) / 0xffff) )  ;
    }

#define COLOR_White (0xffffff)
#define COLOR_Black (0)
  
    unsigned int kolorDopelniajacy(unsigned int kolor, int level) {
      return kolorDopelniajacy(kolor, level, COLOR_White);
//      return kolorDopelniajacy(kolor, level, COLOR_White);
//      return kolorDopelniajacy(kolor, level, COLOR_Black);
    }
    unsigned int kolorDopelniajacy(unsigned int kolor, int level, unsigned int kolorTla)
    {
      int r,g,b, rt,gt,bt, ro,go,bo;
      r = kolor2r(kolor);
      g = kolor2g(kolor);
      b = kolor2b(kolor);

      rt = kolor2r(kolorTla);
      gt = kolor2g(kolorTla);
      bt = kolor2b(kolorTla);

      ro = skladowaDopelniajaca(r, rt, level);
      go = skladowaDopelniajaca(g, gt, level);
      bo = skladowaDopelniajaca(b, bt, level);

      // return Color_FromArgb(0xff, ro, go, bo);
      return ( r2kolor(ro) | g2kolor(go) | b2kolor(bo) );
    }

	void okrag(int ox, int oy, int r, unsigned int kolor){
		int x,y;
		for(y=-r;y<r;y++)
			for(x=-r;x<r;x++) 
			// Mo¿na szybciej, ale potrzebna trygonometria
				if(y*y+x*x<r*r)rysujPunkt(ox+x,oy+y,kolor);
	} // A tak poza tym, to chyba jest ko³o a nie okr¹g?
	void okrag(int ox, int oy, int r, int jedne_osme, unsigned int kolor){
         int px, py;
         
         px=0;
         py=r;
         while(px<=py){
             if(jedne_osme&1)rysujPunkt(ox+px,oy+py,kolor);
             if(jedne_osme&2)rysujPunkt(ox+py,oy+px,kolor);
             
             if(jedne_osme&4)rysujPunkt(ox+py,oy-px,kolor);
             if(jedne_osme&8)rysujPunkt(ox+px,oy-py,kolor);

             if(jedne_osme&16)rysujPunkt(ox-px,oy-py,kolor);
             if(jedne_osme&32)rysujPunkt(ox-py,oy-px,kolor);
             
             if(jedne_osme&64)rysujPunkt(ox-py,oy+px,kolor);
             if(jedne_osme&128)rysujPunkt(ox-px,oy+py,kolor);
             if(abs((px+1)*(px+1)+(py-1)*(py-1)-r*r)<abs((px+1)*(px+1)+py*py-r*r))
                 {px++;py--;}else{px++;}
//             odswiez();
         }
    }
	void prostokat(int ox, int oy, int wx, int wy, unsigned int kolor){
		int x,y;
		for(x=ox;x<ox+wx;x++)
			for(y=oy;y<oy+wy;y++)
				rysujPunkt(x,y,kolor,1); // Mo¿na szybciej,  przez (adres, kolor) 
// Przed ka¿d¹ optymalizacj¹ trzeba siê jednak upewniæ, ¿e dany fragment kodu dzia³a poprawnie...
	}
	void elipsa(int ox, int oy, int rx, int ry, 
	int alfa0, int alfa1,int alfa3, unsigned int kolor, int dotted = 0){
		double a;
		int x0,y0,x1,y1,i;
		
		x0=ox+rx;
		y0=oy;
		i=1;
		for(a=alfa0*2*M_PI/360+M_PI/32;a<alfa1*2*M_PI/360;a+=M_PI/32){
			x1=ox+(int)(cos(a)*rx);
			y1=oy+(int)(sin(a)*ry);
			if((!dotted) || (i & 1))linia(x0,y0,x1,y1,kolor);
			x0=x1;y0=y1;
			i++;
		}
		linia(x0,y0,ox+rx,oy,kolor);
	}
	void elipsa(int ox, int oy, int rx, int ry, unsigned int kolor){
		elipsa(ox,oy,rx,ry,0,360,0,kolor);}	
// S¹ nie mniej ni¿ dwa sposoby obrotu: albo przez funkcjê obrotu punktu wokó³ punktu o k¹t alfa3,
// albo przez przejcie do wsp. biegunowych (w³aciwie wyjcie od nich), dodanie alfa3 i przejcie do
// wsp. ortogonalnych.

// 1. Wzór na promieñ elipsy r dla danego k¹ta alfa: 
// 		r=sqrt(1/(cos(alfa)*cos(alfa)/rx/rx+sin(alfa)*sin(alfa)/ry/ry))
// 2. obrót:
//		alfa_prim=alfa+alfa3;
// 3. przejcie do wsp. ortogonalnych:
//		 x1=cos(alfa_prim)*r; y1=sin(alfa_prim*r);
// To chyba tyle, teraz jeszcze trzeba to zaprogramowaæ...
	void elipsa3(int ox, int oy, int rx, int ry, 
		     double alfa0, double alfa1,double alfa3, unsigned int kolor, int dotted=0){
		double r, a, aPrim;
		double x0,y0,x1,y1,x2,y2,x3,y3;
		
//#define EL3_STEP (M_PI/180)
//#define EL3_STEP (M_PI/160)
// podwaja szybkosc /z 4 do 8 klatek na sekunde/ przykladowej animacji:
//#define EL3_STEP (M/PI/30)
//#define EL3_STEP (M_PI/80)
#define EL3_STEP (M_PI/160)
#define ROZSZERZ (0)
#define KROPKI (1)
#define KROPKI_P (1)
//#define KROPKI (0)
//#define KROPKI_P (0)
#define PRZEPLOT (1)
		a=alfa0*2.0*M_PI/360.0;
		r=sqrt(1.0/(cos(a)*cos(a)/rx/rx+sin(a)*sin(a)/ry/ry));
		aPrim=a+alfa3*2.0*M_PI/360.0;
		x0=ox+r*cos(aPrim);
		y0=oy+r*sin(aPrim);
		a+=EL3_STEP;
		aPrim=a+alfa3*2.0*M_PI/360.0;
		x1=ox+r*cos(aPrim);
		y1=oy+r*sin(aPrim);
		a+=EL3_STEP;
		aPrim=a+alfa3*2.0*M_PI/360.0;
		x2=ox+r*cos(aPrim);
		y2=oy+r*sin(aPrim);
		int parity=0;
		for(a=alfa0*2.0*M_PI/180.0+3.0*EL3_STEP;
		    a<alfa1*2.0*M_PI/360.0+2.0*EL3_STEP;a+=EL3_STEP){
		        parity++;
			r=sqrt(1.0/(cos(a)*cos(a)/rx/rx+sin(a)*sin(a)/ry/ry));
			aPrim=a+alfa3*2.0*M_PI/360.0;
			x3=ox+cos(aPrim)*r;
			y3=oy+sin(aPrim)*r;
			if(dotted) {
			  if((parity & 7) == 7) {
			    if(PRZEPLOT) {
			    	linia(x0,y0,x2,y2,kolor, ROZSZERZ,KROPKI_P);
			    	linia(x1,y1,x3,y3,kolor, ROZSZERZ,KROPKI_P);
			    } else {
			    	linia(x0,y0,x1,y1,kolor,ROZSZERZ, KROPKI);
			    	linia(x1,y1,x2,y2,kolor,ROZSZERZ, KROPKI);
			    	linia(x2,y2,x3,y3,kolor,ROZSZERZ, KROPKI);
			    }
			  }
			} else {
			  if(PRZEPLOT) {
			  	linia(x0,y0,x2,y2,kolor, ROZSZERZ, KROPKI_P);
			  	linia(x1,y1,x3,y3,kolor, ROZSZERZ, KROPKI_P);
			  } else {
			  	linia(x0,y0,x1,y1,kolor,ROZSZERZ, KROPKI);
			  	linia(x1,y1,x2,y2,kolor,ROZSZERZ, KROPKI);
			  	linia(x2,y2,x3,y3,kolor,ROZSZERZ, KROPKI);
			  }
			}
			x0=x1;y0=y1;
			x1=x2;y1=y2;
			x2=x3;y2=y3;
		}
	}
	void elipsa2(int ox, int oy, int rx, int ry, 
	int alfa0, int alfa1, unsigned int kolor){
		int x,y,px,py,funct,functprim;
		int flaga;
		px=0;py=0;
		for(x=ox-rx-16;x<ox+rx+16;x++)
			for(y=oy-ry-16;y<oy+ry+16;y++){
				//funct=px*px/(rx*rx)+py*py/(ry*ry)-1;
//				funct=px*px*ry*ry+py*py*rx*rx-rx*rx*ry*ry;
				px=x-ox;
				py=y-oy;
				functprim=((px*px)<<12)/(rx*rx)+((py*py)<<12)/(ry*ry)-(1<<12);
				// 350 x 350 x 200 x 200 = 4 900 000 000 dwa bity za du¿o
				/*
				if((funct<0 && functprim>=0)||
				   (funct<0 && functprim>=0))
				   */
				flaga=1;
	//if(-144*rx/ry*abs(py)/ry<=functprim && functprim<=144*rx/ry*abs(py)/ry)	
	if(-3*pow(ry,.95)<=functprim && functprim<=3*pow(ry,.95))	
						rysujPunkt(x,y,flaga?kolor:functprim); 
			}		
		// Mo¿na szybciej,  przez (adres, kolor) . Czy mo¿na zawrzeæ to w inline void rysujPunkt?
		// O tyle nie, ¿e za ka¿dym razem trzeba w rysujPunkt przeliczyæ adres...
		// Mo¿na zrobiæ funkcjê rysujPunkt(adres,kolor), tylko po co? zamiast ekran[segment+adres]=kolor?
		// O tyle siê op³aca, ¿e nie trzeba ci¹gle tego rzutowania adresu ekranu na tablicê typu unsigned int
		// Ano tak wiem bez sensu to pisanie, skoro to i tak nie ma (nie musi) byæ jaki super efektywny kod...
	}
	unsigned int* E(int x, int y){
		return ((unsigned int*)screen->pixels)+x+y*wymiar.x;}
	void wypelnijKolorem(punkt p, unsigned int kolor){
		unsigned int k;
		k=*E(p.x,p.y);
		*E(p.x,p.y)=kolor;
	
		do{
			if(*E(p.x-1,p.y)==k) stos_punktow.wloz(punkt(p.x-1,p.y));
			if(*E(p.x+1,p.y)==k) stos_punktow.wloz(punkt(p.x+1,p.y));
			if(*E(p.x,p.y-1)==k) stos_punktow.wloz(punkt(p.x,p.y-1));
			if(*E(p.x,p.y+1)==k) stos_punktow.wloz(punkt(p.x,p.y+1));
			if(!stos_punktow.pusty()){p=stos_punktow.zdejmij();
				*E(p.x,p.y)=0xffffff;
				//wyswietl();
				odswiez(p.x,p.y,p.x,p.y);
				*E(p.x,p.y)=kolor;
				
			}
			//odswiez(0,0,p.x,p.y);//wyswietl();
			odswiez(p.x,p.y,p.x,p.y);
			//K->sprawdzIWyjdzGdyKlawisz();
		}while(!stos_punktow.pusty()); // UWAGA! 
		// Czy nie mo¿e byæ tak, ¿e stos pusty, a dooko³a podniesionego
		// punktu jeszcze punkty do zape³nienia? 1.10.2008
	}
	void wklej(rysunek r, int ox, int oy){
	//  WYJ¥TKI !!! (throws punkt_poza_obszarem_okna)
//		if ox<0 or oy<0 or ox>this->x-1 or oy>this->y-1 throw punkt_poza_obszarem_okna;
		int x,y;
		
		for(x=0;x<r.x;x++)for(y=0;y<r.y;y++)
			this->rysujPunkt(x+ox,y+oy,
			r.punkty[3*x+y*3*r.x]|
			(r.punkty[3*x+1+y*3*r.x]<<8)|
			(r.punkty[3*x+2+y*3*r.x]<<16));
	}
    void zapiszBMP(char *plik){SDL_SaveBMP(screen,plik);}
    
    void skalujObraz(int skala, double jasnosc = 1)
    {
         int x, y, skala2 = skala*skala, i, j;
         unsigned int r, g, b;
         unsigned int kolor;
         
         for(i=0;i<wymiar.x-skala;i+=skala)
             for(j=0;j<wymiar.y-skala;j+=skala){
  //               printf("j = %d\n", j);
                 r=0;
                 g=0;
                 b=0;
                 for(x=0;x<skala;++x)
                     for(y=0;y<skala;++y){
                         kolor = czytajPunkt(i+x,j+y);
                         r += (kolor >> 16) & 0xff;
                         g += (kolor >> 8) & 0xff;
                         b += kolor & 0xff;
                     }
                 rysujPunkt(i/skala, j/skala, 
                            ((int)(jasnosc*r/skala2) << 16) 
                            | ((int)(jasnosc*g/skala2) << 8)
                            | (int)(jasnosc*b/skala2));
             }
    }
};
#endif
