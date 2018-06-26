#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#define SCREEN_WIDTH	640        //w px.
#define SCREEN_HEIGHT	480			//w px.
#define szerokosc_planszy 1024			//w px.
//#define ilosc_zyc 1
#define pozycja_poczatkowax 64   //w px.
#define pozycja_poczatkoway 80		//w px.
#define wymiary_podlogi 32      //w px.
#define czas_rozgrywki  200		//w sek.
#define wysokosc_mario 32			//w px
#define szerokosc_mario 24			//w px
#define liczba_zyc 3				// zwykla liczba
#define czas_lotu 1				//w sek.
#define predkosc_mario_pozioma 100    // px na s
#define mario_predkosc_pionowa 200     // px na s
#define predkosc_minionka 0.8             //uzyte w funkcji z sin()         px na s
#define czas_chodzenia 2.0          //w s
#define minionka_wysokosc 32        // w px
#define minionka_szerokosc 32          // w px
#define czas_animacji 0.3           //w s
#define czas_anima_goombas  0.3   //w s

// funkcje podstawowe
extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}

struct polozenie_wsk {
	double *pozx;
	double *pozy;
};


struct polozenie {
	double pozx;
	double pozy;
};

struct minionek_polozenie {
	double *pozx;
	double *pozy;
};

struct plansza {
	double pozx;
	double pozy;
	int stan1;
};



struct mario_animacja {
	//	13
	SDL_Surface *_moveL0;
	SDL_Surface *_moveL1;
	SDL_Surface *_moveL2;
	SDL_Surface *_moveR0;
	SDL_Surface *_moveR1;
	SDL_Surface *_moveR2;
	SDL_Surface *_jumpR;
	SDL_Surface *_jumpL;
	//SDL_Surface *_
};


void umieszczenie_drugiej_podlogi(SDL_Surface *screen, SDL_Surface *podloga, double *mario_szerokosc);
void polozenie_mario(SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario);
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void umieszczenie_pierwszej_podlogi(SDL_Surface *screen, SDL_Surface *podloga, double *mario_szerokosc , SDL_Surface *sciana);
void umieszczenie_drugiej_podlogi(SDL_Surface *screen, SDL_Surface *podloga, double *mario_szerokosc);
void umieszczenie_pierwszej_przeszkody(int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]);
int sprawdzenie_tablicy(double *mario_wysokosc, double *mario_szerokosc, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]);
int sprawdzanie_przeszkody(double *mario_wysokosc, double *mario_szerokosc, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]);
void zapis_pliku(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1);
void odczyt_pliku(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1);
void nowa_gra(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1, int *flaga3);
void latanie(double *mario_wysokosc, double *mario_szerokosc, int *quit, double *czas_latania, double delta, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *wsk_na_zycia, double *wsk_czas, int *flaga1, int *flaga3, double *mario_wsk_czas_chodzenia, int *spr_wsk_kierunku , int *spr_skoku);
void obs³uga_zdarzen(double *mario_wysokosc, double *mario_szerokosc, int *quit, double *czas_latania, double delta, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *wsk_na_zycia, double *wsk_czas, int *flaga1, int *flaga3, double *mario_wsk_czas_chodzenia, int *spr_wsk_kierunku, mario_animacja mario_anim, SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario , int *spr_skoku);
void zmiana_obrazu(int spr, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]);
void malowanie_obrazu(double *mario_wysokosc, double *mario_szerokosc, SDL_Surface *screen, SDL_Surface *podloga, int *flaga1, int *flaga3, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *quit , SDL_Surface *sciana);
int zabieranie_zyc(double *wsk_czas, int pozostale_zycia, double *mario_wysokosc, double *mario_szerokosc, int *flaga1, int *flaga3, minionek_polozenie minionek_nr1);
void koniec_gry(SDL_Surface *screen, int czarny);
void polozenie_minionka_nr1(SDL_Surface *screen, minionek_polozenie minionek_nr1, double *wsk_czas, SDL_Surface *wzor1, double *mario_szerokosc, int *flaga1 , SDL_Surface *wzor2 , double delta , double *animacja_goombas);
void zmiana_polozenia_mario(double *mario_wsk_czas_chodzenia, double *mario_szerokosc, double delta, int *spr_wsk_kierunku, mario_animacja mario_anim, SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario, double *czas_latania, double *wsk_czas , int *flaga3 , int *spr_skoku);
void zabranie_i_wyzerowanie_planszy(double *wsk_czas, double *mario_wysokosc, double *mario_szerokosc, int *flaga1);
int  spr_bmp(SDL_Surface *podloga, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *charset);