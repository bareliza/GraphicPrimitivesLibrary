#ifdef _ALE_ZLY_STYL_BIBLIOTEK_
//#undef __cplusplus
#include "SDL/SDL.h"
//#define __cplusplus
#include <stdio.h>
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
		wymiar.y=wymiar_y; // dalszy kod konstruktora zapo¿yczony z dokumentacji SDL
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
	inline void rysujPunkt(int x, int y, unsigned int wartosc){
        	rysujPunkt(x,y,wartosc,pioro);}
        //          if(x>=0 && y>=0 && x<wymiar.x && y<wymiar.y)
        //	            ((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
	inline void rysujNieKlipowanyPunkt(int x, int y, unsigned int wartosc){
	    ((unsigned int*)screen->pixels)[x+y*wymiar.x]=wartosc;}
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

#define CLIP0_X (0+220)
#define CLIP1_X (wymiar.x-270)
#define CLIP0_Y (0+170)
#define CLIP1_Y (wymiar.y-190)
  
	void liniaPionowa(int x, int y0, int y1, unsigned int kolor)
    	{

		int tmp;
      		if (y0 > y1) { tmp = y0;y0 = y1;y1 = tmp; }
      		if (y0 < CLIP0_Y) y0 = CLIP0_Y;
      		if (y1 >= CLIP1_Y) y1 = CLIP1_Y - 1; // height - 1;

      		int start, stop;

      		start = y0; // rawStride * y0 + x;
      		stop  = y1; // rawStride * y1 + x;

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

           	do    // rawImage[start] = kolor;
		      	rysujPunkt(start++, y, kolor); // start++; // += rawStride;
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
  
	void linia(int x0, int y0, int x1, int y1, unsigned int kolor){
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
		// klipowanie kod3
		if(y0 > y1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
		if(y1 >= CLIP1_Y) {
		  dOut = y1 - CLIP1_Y;
		  xOut = dOut * dx / dy;
		  y1 = CLIP1_Y - 1;
		  x1 = x1 + ( (x1 < x0) ?  xOut : -xOut );
		}
		// klipowanie kod4
		if(x0 > x1){
		  tmp=x0;x0=x1;x1=tmp;
		  tmp=y0;y0=y1;y1=tmp;
		}
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
				rysujPunkt(x0,y0>>16,kolor);
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
				rysujPunkt(x0>>16,y0,kolor);
				x0+=fract;
			}
		}
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
	int alfa0, int alfa1,int alfa3, unsigned int kolor){
		double a;
		int x0,y0,x1,y1;
		
		x0=ox+rx;
		y0=oy;
		
		for(a=alfa0*2*M_PI/360+M_PI/32;a<alfa1*2*M_PI/360;a+=M_PI/32){
			x1=ox+(int)(cos(a)*rx);
			y1=oy+(int)(sin(a)*ry);
			linia(x0,y0,x1,y1,kolor);
			x0=x1;y0=y1;
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
	int alfa0, int alfa1,int alfa3, unsigned int kolor){
		double r, a, aPrim;
		int x0,y0,x1,y1;
		
		a=alfa0*2*M_PI/360;
		r=sqrt(1/(cos(a)*cos(a)/rx/rx+sin(a)*sin(a)/ry/ry));
		aPrim=a+alfa3*2*M_PI/360;
		x0=ox+(int)(r*cos(aPrim));
		y0=oy+(int)(r*sin(aPrim));
		for(a=alfa0*2*M_PI/180+M_PI/180;a<alfa1*2*M_PI/360;a+=M_PI/180){
			r=sqrt(1/(cos(a)*cos(a)/rx/rx+sin(a)*sin(a)/ry/ry));
			aPrim=a+alfa3*2*M_PI/360;
			x1=ox+(int)(cos(aPrim)*r);
			y1=oy+(int)(sin(aPrim)*r);
			linia(x0,y0,x1,y1,kolor);
			x0=x1;y0=y1;
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
