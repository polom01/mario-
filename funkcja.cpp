#include "funkcja.h"


void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};
// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

//  funkcje napisane przezemnie 
void umieszczenie_pierwszej_podlogi(SDL_Surface *screen, SDL_Surface *podloga, double *mario_szerokosc , SDL_Surface *sciana) {
	int szer = *mario_szerokosc;
	static int roznica;
	if ((szer > SCREEN_WIDTH / 2) && szer < SCREEN_WIDTH) {
		roznica = (szer - SCREEN_WIDTH / 2) / 2;
	}
	else if (szer < SCREEN_WIDTH / 2) { roznica = 0; }
	for (int wysokosc = 0; wysokosc <= SCREEN_HEIGHT; wysokosc += wymiary_podlogi) {
		for (int szerokosc_podstawowa = 0; szerokosc_podstawowa <= szerokosc_planszy; szerokosc_podstawowa += wymiary_podlogi) {
			if (wysokosc <= wymiary_podlogi) {
				DrawSurface(screen, podloga, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
			}
			////////////////////
			if (((SCREEN_HEIGHT - wysokosc) == 13 * wymiary_podlogi) || ((SCREEN_HEIGHT - wysokosc) == 12 * wymiary_podlogi)) {
				if ((SCREEN_WIDTH - szerokosc_podstawowa) == 13 * wymiary_podlogi) {
					DrawSurface(screen, sciana, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
				}
			}
			///////////////////
			if ((SCREEN_HEIGHT - wysokosc) == 10 * wymiary_podlogi) {
				if (((SCREEN_WIDTH - szerokosc_podstawowa) >= 3 * wymiary_podlogi) && ((SCREEN_WIDTH - szerokosc_podstawowa) <= 6 * wymiary_podlogi)) {
					DrawSurface(screen, sciana, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
				}
			}
			if ((SCREEN_HEIGHT - wysokosc) == 11 * wymiary_podlogi) {
				if ((SCREEN_WIDTH - szerokosc_podstawowa) == 10 * wymiary_podlogi) {
					DrawSurface(screen, sciana, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
				}
				else if ((SCREEN_WIDTH - szerokosc_podstawowa) == 16 * wymiary_podlogi) {
					DrawSurface(screen, sciana, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
				}
			}
		}
	}
}

// chyba ok

void umieszczenie_drugiej_podlogi(SDL_Surface *screen, SDL_Surface *podloga, double *mario_szerokosc) {

	int szer = *mario_szerokosc;
	static int roznica;
	if ((szer > SCREEN_WIDTH / 2) && szer < SCREEN_WIDTH) {
		roznica = (szer - SCREEN_WIDTH / 2) / 2;
	}
	else if (szer < SCREEN_WIDTH / 2) { roznica = 0; }
	for (int wysokosc = 0; wysokosc <= SCREEN_HEIGHT; wysokosc += wymiary_podlogi) {
		for (int szerokosc_podstawowa = 0; szerokosc_podstawowa <= szerokosc_planszy; szerokosc_podstawowa += wymiary_podlogi) {
			if (wysokosc <= wymiary_podlogi) {
				if (((SCREEN_WIDTH - szerokosc_podstawowa) <= 3 * wymiary_podlogi) || ((SCREEN_WIDTH - szerokosc_podstawowa) > 6 * wymiary_podlogi))
					DrawSurface(screen, podloga, (wymiary_podlogi / 2) + szerokosc_podstawowa - roznica, (SCREEN_HEIGHT - (wymiary_podlogi / 2)) - wysokosc);
			}
		}
	}
}

void polozenie_mario(SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario) {
	static int roznica;
	int szer = mario.pozx;
	if ((szer > SCREEN_WIDTH / 2) && szer < SCREEN_WIDTH) {
		roznica = (szer - SCREEN_WIDTH / 2) / 2;
	}
	else if (szer < SCREEN_WIDTH / 2) { roznica = 0; }
	DrawSurface(screen, przyklad_mario, mario.pozx - roznica, SCREEN_HEIGHT - mario.pozy);
}

void polozenie_minionka_nr1(SDL_Surface *screen, minionek_polozenie minionek_nr1, double *wsk_czas, SDL_Surface *wzor1 , double *mario_szerokosc , int *flaga1 , SDL_Surface *wzor2 , double delta , double *animacja_goombas) {
	if (*flaga1 == 0) {
		*minionek_nr1.pozx = 16.5 * wymiary_podlogi;
		*minionek_nr1.pozy = 2.5 * wymiary_podlogi;
	}
	else if (*flaga1 == 1) {
		*minionek_nr1.pozx = 9.5 * wymiary_podlogi;
		*minionek_nr1.pozy = 2.5 * wymiary_podlogi;
	}
		int szer = *mario_szerokosc;
		static int roznica;
		if ((szer > SCREEN_WIDTH / 2) && szer < SCREEN_WIDTH) {
			roznica = (szer - SCREEN_WIDTH / 2) / 2;
		}
		else if (szer < SCREEN_WIDTH / 2) { roznica = 0; }

		*minionek_nr1.pozx = (*minionek_nr1.pozx) + (sin((*wsk_czas)*predkosc_minionka))*(4 * wymiary_podlogi);
		//+(sin((*wsk_czas)*predkosc_minionak))*(2 * wymiary_podlogi);



		if (*animacja_goombas < (czas_anima_goombas / 2)) {
			*animacja_goombas -= delta;
			DrawSurface(screen, wzor1, *minionek_nr1.pozx - roznica, SCREEN_HEIGHT - *minionek_nr1.pozy);
			if (*animacja_goombas < 0) *animacja_goombas = czas_anima_goombas;
		}
		else if (*animacja_goombas >= (czas_anima_goombas / 2)) {
			*animacja_goombas -= delta;
			DrawSurface(screen, wzor2, *minionek_nr1.pozx - roznica, SCREEN_HEIGHT - *minionek_nr1.pozy);
			
		}
		else {
			*animacja_goombas -= delta;
			DrawSurface(screen, wzor2, *minionek_nr1.pozx - roznica, SCREEN_HEIGHT - *minionek_nr1.pozy);
		}
		//animacja_goombas += delta;
}
//chyba ok
void umieszczenie_pierwszej_przeszkody(int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]) {
	int a = 14;
	int b = 31;
	for (int wysokosc = 0; wysokosc <= SCREEN_HEIGHT; wysokosc += wymiary_podlogi, a--) {
		for (int szerokosc = 0; szerokosc <= szerokosc_planszy; szerokosc += wymiary_podlogi, b--) {
			if ((SCREEN_HEIGHT - wysokosc) < 3 * wymiary_podlogi) {
				(tab_podlogi[a][b]) = 1;
			}
			else if (((SCREEN_HEIGHT - wysokosc) == 13 * wymiary_podlogi) || ((SCREEN_HEIGHT - wysokosc) == 12 * wymiary_podlogi)) {
				if ((SCREEN_WIDTH - szerokosc) == 13 * wymiary_podlogi)
				{
					(tab_podlogi[14 - a][31 - b]) = 1;
				}
			}
			if ((SCREEN_HEIGHT - wysokosc) == 10 * wymiary_podlogi) {
				if (((SCREEN_WIDTH - szerokosc) >= 3 * wymiary_podlogi) && ((SCREEN_WIDTH - szerokosc) <= 6 * wymiary_podlogi)) {
					(tab_podlogi[14 - a][31 - b]) = 1;
				}
			}
			if ((SCREEN_HEIGHT - wysokosc) == 11 * wymiary_podlogi) {
				if ((SCREEN_WIDTH - szerokosc) == 10 * wymiary_podlogi) {
					(tab_podlogi[14 - a][31 - b]) = 1;
				}
				else if ((SCREEN_WIDTH - szerokosc) == 16 * wymiary_podlogi) {
					(tab_podlogi[14 - a][31 - b]) = 1;
				}
			}
		}
		b = 31;
	}
}

int sprawdzenie_tablicy(double *mario_wysokosc, double *mario_szerokosc, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]) {
	for (int zmienna_y = (-1)*wysokosc_mario/2; zmienna_y <= wysokosc_mario/2; zmienna_y += wysokosc_mario)    //zmieniam na +40 zeby tylko raz sie wykonalo
		for (int zmienna_x = (-1)*szerokosc_mario/2; zmienna_x <= szerokosc_mario/2; zmienna_x += szerokosc_mario) {
			int wys = (*mario_wysokosc + zmienna_y) / wymiary_podlogi;
			int szer = (*mario_szerokosc + zmienna_x) / wymiary_podlogi;
			if (tab_podlogi[wys][szer] == 1) {
				return 1;
			}
		}
	return 0;
}

int sprawdzanie_przeszkody(double *mario_wysokosc, double *mario_szerokosc, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]) {
	for (int zmienna_y = (-1)*wysokosc_mario/2; zmienna_y <= wysokosc_mario / 2; zmienna_y += wysokosc_mario / 2)
		for (int zmienna_x = (-1)* szerokosc_mario/2 ; zmienna_x <= szerokosc_mario/2; zmienna_x += szerokosc_mario) {
			int wys = (*mario_wysokosc + zmienna_y) / wymiary_podlogi;
			int szer = (*mario_szerokosc + zmienna_x) / wymiary_podlogi;
			if (zmienna_x == -szerokosc_mario/2) {          //jezeli przeszkoda po lewej stronie
				if (tab_podlogi[wys][szer] == 1) {
					return 1;
				}
			}
			else {           //jezeli przeszkoda po prawej stronie
				if (tab_podlogi[wys][szer] == 1) {
					return 2;
				}
			}
		}
	return 0;
}
int sprawdzanie_platformy(double *mario_wysokosc, double *mario_szerokosc, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]) {
	int zmienna_y = 16;
	for (int zmienna_x = (-1)*szerokosc_mario / 2; zmienna_x <= szerokosc_mario / 2; zmienna_x += szerokosc_mario) {
		int wys = (*mario_wysokosc + zmienna_y) / wymiary_podlogi;
		int szer = (*mario_szerokosc + zmienna_x) / wymiary_podlogi;
		if (tab_podlogi[wys][szer] == 1) {
			return 1;
		}
	}
	return 0;
}

void zapis_pliku(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1) {

	int czas = *wsk_czas * 1000;
	int mario_wysokosc_pom = *mario_wysokosc * 1000;
	int mario_szerokosc_pom = *mario_szerokosc * 1000;
	FILE* plik = fopen("zapis.txt", "w+");
	fprintf(plik, "%d %d %d %d %d \n", mario_wysokosc_pom, mario_szerokosc_pom, czas, *pozostale_zycia, *flaga1);

	fclose(plik);

}

void odczyt_pliku(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1) {
	FILE * plik;
	plik = fopen("zapis.txt", "r");
	if (plik) {
		int f, spr;
		double czas;
		fscanf(plik, " %d", &f);
		*mario_wysokosc = f;
		*mario_wysokosc=*mario_wysokosc / 1000.0;
		fscanf(plik, " %d", &f);
		*mario_szerokosc = f;
		*mario_szerokosc=*mario_szerokosc / 1000.0;
		fscanf(plik, " %d", &f);
		czas = f;  // :100.0; gdy nie uda sie double
		*wsk_czas = f;
		*wsk_czas=*wsk_czas / 1000.0;
		fscanf(plik, " %d", &f);
		*pozostale_zycia = f;
		fscanf(plik, " %d", &f);
		*flaga1 = f;

	}
	else *mario_wysokosc = 540;
	fclose(plik);
}

void nowa_gra(double *mario_wysokosc, double *mario_szerokosc, double *wsk_czas, int *pozostale_zycia, int *flaga1, int *flaga3) {
	*mario_wysokosc = pozycja_poczatkoway;
	*mario_szerokosc = pozycja_poczatkowax;
	*wsk_czas = czas_rozgrywki;
	*pozostale_zycia = liczba_zyc;
	*flaga1 = 0;
	*flaga3 = 0;
}

void latanie(double *mario_wysokosc, double *mario_szerokosc, int *quit, double *czas_latania, double delta, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *wsk_na_zycia, double *wsk_czas, int *flaga1, int *flaga3 , double *mario_wsk_czas_chodzenia, int *spr_wsk_kierunku , int *spr_skoku) {
	SDL_Event event;
	*spr_skoku=1;
	static double zprawdz = 0;
	zprawdz += delta;
	if (*wsk_czas == czas_rozgrywki) {
		zprawdz = 0;
	}
	double wys = *mario_wysokosc + 1;
	//wymiary_podlogi/2;   //do proby
	double *wysokosc = &wys;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if ((*czas_latania > 0)) {
				if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 1)) {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 1;
					}              
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}
				else if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 2) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_LEFT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 0;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}
				else {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 1;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 0;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}

			}
			else if (*czas_latania <= 0) {
				*czas_latania = 0;
				if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 1)) {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 1;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}
				else if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_LEFT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 0;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}
				else {
					if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 1;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						*mario_wsk_czas_chodzenia = czas_chodzenia;
						*spr_wsk_kierunku = 0;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
					else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					break;
				}
			}
			break;
		case SDL_KEYUP:
			*mario_wsk_czas_chodzenia =0.0;
			break;
		case SDL_QUIT:
			*quit = 1;
			break;
		};
	};

	if (sprawdzanie_platformy(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) {
		*czas_latania = 0;
		//zprawdz = 0;
		if (*mario_wysokosc >= 2 * wymiary_podlogi + wysokosc_mario + 2)
			//*mario_wysokosc -= mario_predkosc_pionowa * delta;       
			*mario_wysokosc -= 2;
			// wazne dorbic ( spr ) -= 2
	}

	if ((*czas_latania < czas_lotu / 2.0)) {
		*czas_latania -= delta;
		if (sprawdzenie_tablicy(mario_wysokosc, mario_szerokosc, tab_podlogi) != 1) {
			if (zprawdz >0.5) *mario_wysokosc -= mario_predkosc_pionowa * delta;
			else *mario_wysokosc -= 0;
		}
		else {
		}

		if (*czas_latania < 0) {
			*czas_latania = 0;
			//	*mario_wysokosc = (2 * wymiary_podlogi) + (wysokosc_mario / 2);             // zmienic na bardziej ogolny
		}
	}
	else if (*czas_latania > czas_lotu / 2.0) {
		*czas_latania -= delta;
		*mario_wysokosc += mario_predkosc_pionowa * delta;
	}
	else if (*czas_latania == czas_lotu / 2.0) {
		*czas_latania -= delta;
	}

	if (sprawdzenie_tablicy(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) {
		*spr_skoku = 0;
	}


}

void obs≥uga_zdarzen(double *mario_wysokosc, double *mario_szerokosc, int *quit, double *czas_latania, double delta, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *wsk_na_zycia, double *wsk_czas, int *flaga1, int *flaga3, double *mario_wsk_czas_chodzenia, int *spr_wsk_kierunku, mario_animacja mario_anim, SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario , int *spr_skoku) {

	SDL_Event event;
	*spr_skoku = 0; //jest na ziemi
	double wys = *mario_wysokosc + 3;   //do proby + wymiary_podlogi/3
	double *wysokosc = &wys;
	int spr1 = sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi);
	int spr2 = sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi);
	if (*czas_latania == 0) {
		if (sprawdzenie_tablicy(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 1)) {
						if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;                                         // z lewej strony przeszkoda
						else if (event.key.keysym.sym == SDLK_UP) *czas_latania = czas_lotu;
						else if (event.key.keysym.sym == SDLK_RIGHT) {
							*mario_wsk_czas_chodzenia = czas_chodzenia;
							*spr_wsk_kierunku = 1;
						} //(predkosc_mario_pozioma * delta)
						else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
						else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
						else if (event.key.keysym.sym == SDLK_l) odczyt_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
					}
					else if ((sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
						if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) || (sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
							if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
							else if (event.key.keysym.sym == SDLK_UP) *czas_latania = czas_lotu;
							else if (event.key.keysym.sym == SDLK_LEFT) {
								*mario_wsk_czas_chodzenia = czas_chodzenia;
								*spr_wsk_kierunku = 0;
							}
							else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
							else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
							else if (event.key.keysym.sym == SDLK_l) odczyt_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
							break;
						}
					}
					else {
						if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
						else if (event.key.keysym.sym == SDLK_UP) *czas_latania = czas_lotu;
						else if (event.key.keysym.sym == SDLK_RIGHT) { *mario_wsk_czas_chodzenia = czas_chodzenia; 
						*spr_wsk_kierunku = 1;
						}
						else if (event.key.keysym.sym == SDLK_LEFT) {
							*mario_wsk_czas_chodzenia = czas_chodzenia;
							*spr_wsk_kierunku = 0;
						}
						else if (event.key.keysym.sym == SDLK_n) nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1, flaga3);
						else if (event.key.keysym.sym == SDLK_l) odczyt_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
						else if (event.key.keysym.sym == SDLK_s) zapis_pliku(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_na_zycia, flaga1);
						break;
					}
				case SDL_KEYUP:
					*mario_wsk_czas_chodzenia = 0;
					break;
				case SDL_QUIT:
					*quit = 1;
					break;
				};
			};
		}
		else   latanie(mario_wysokosc, mario_szerokosc, quit, czas_latania, delta, tab_podlogi, wsk_na_zycia, wsk_czas, flaga1, flaga3 , mario_wsk_czas_chodzenia , spr_wsk_kierunku , spr_skoku);
	}
	else latanie(mario_wysokosc, mario_szerokosc, quit, czas_latania, delta, tab_podlogi, wsk_na_zycia, wsk_czas, flaga1, flaga3, mario_wsk_czas_chodzenia, spr_wsk_kierunku , spr_skoku);

	zmiana_polozenia_mario(mario_wsk_czas_chodzenia, mario_szerokosc, delta, spr_wsk_kierunku, mario_anim, screen, przyklad_mario, mario, czas_latania, wsk_czas ,flaga3 , spr_skoku);

	if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) && (sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 1)) {
		*mario_szerokosc += 1;
	}
	else if ((sprawdzanie_przeszkody(wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
		if ((sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 1) || (sprawdzanie_przeszkody(mario_wysokosc, mario_szerokosc, tab_podlogi) == 2)) {
			*mario_szerokosc -= 1;
		}
	}

}

void zmiana_obrazu(int spr, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi]) {
	for (int a = 0; a<2; a++)
		for (int b = 14; b < 17; b++) {
			tab_podlogi[a][b] = spr;
		}
	tab_podlogi[4][4] = spr;
	tab_podlogi[2][7] = spr;
	tab_podlogi[3][7] = spr;
	tab_podlogi[4][10] = spr;
	tab_podlogi[5][14] = spr;
	tab_podlogi[5][15] = spr;
	tab_podlogi[5][16] = spr;
	tab_podlogi[5][17] = spr;

}

void malowanie_obrazu(double *mario_wysokosc, double *mario_szerokosc, SDL_Surface *screen, SDL_Surface *podloga, int *flaga1, int *flaga3, int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi], int *quit, SDL_Surface *sciana)
{


	if (*flaga1 == 0) {
		zmiana_obrazu(1, tab_podlogi);
		umieszczenie_pierwszej_podlogi(screen, podloga, mario_szerokosc , sciana);
		if (*mario_szerokosc >= (szerokosc_planszy - 7 * wymiary_podlogi) - szerokosc_mario) {
			*mario_szerokosc = pozycja_poczatkowax;
			*flaga1 = 1;
		}
	}
	else if (*flaga1 == 1) {
		zmiana_obrazu(0, tab_podlogi);
		umieszczenie_drugiej_podlogi(screen, podloga, mario_szerokosc);
		if (*mario_szerokosc >= (szerokosc_planszy - 7 * wymiary_podlogi) - szerokosc_mario) {
			*flaga3 = 1;
		}
	}
}

int zabieranie_zyc(double *wsk_czas, int pozostale_zycia, double *mario_wysokosc, double *mario_szerokosc, int *flaga1, int *flaga3 , minionek_polozenie minionek_nr1) {

	if (pozostale_zycia <= 0) {
		*flaga3 = 1;
	}

	if (*mario_wysokosc<0) {
		pozostale_zycia -= 1;
		zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
		return pozostale_zycia;
	}
	
	if ((*flaga1 == 0) || (*flaga1 == 1)) {
		if (*minionek_nr1.pozy - *mario_wysokosc >= 0) {
			if (*minionek_nr1.pozx - *mario_szerokosc >= 0) {
				if ((*minionek_nr1.pozx - *mario_szerokosc <= minionka_szerokosc / 2 + szerokosc_mario / 2) && (*minionek_nr1.pozy - *mario_wysokosc <= minionka_wysokosc / 2 + wysokosc_mario / 2)) {
					pozostale_zycia -= 1;
					zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
					return pozostale_zycia;
				}
			}
			else if (*minionek_nr1.pozx - *mario_szerokosc < 0) {
				if ((*mario_szerokosc - *minionek_nr1.pozx <= minionka_szerokosc / 2 + szerokosc_mario / 2) && (*minionek_nr1.pozy - *mario_wysokosc <= minionka_wysokosc / 2 + wysokosc_mario / 2)) {
					pozostale_zycia -= 1;
					zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
					return pozostale_zycia;
				}
			}
		}
		else if (*minionek_nr1.pozy - *mario_wysokosc < 0) {
			if (*minionek_nr1.pozx - *mario_szerokosc >= 0) {
				if ((*minionek_nr1.pozx - *mario_szerokosc <= minionka_szerokosc / 2 + szerokosc_mario / 2) && (*mario_wysokosc - *minionek_nr1.pozy <= minionka_wysokosc / 2 + wysokosc_mario / 2)) {
					pozostale_zycia -= 1;
					zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
					return pozostale_zycia;
				}
			}
			else if (*minionek_nr1.pozx - *mario_szerokosc < 0) {
				if ((*mario_szerokosc - *minionek_nr1.pozx <= minionka_szerokosc / 2 + szerokosc_mario / 2) && (*mario_wysokosc - *minionek_nr1.pozy <= minionka_wysokosc / 2 + wysokosc_mario / 2)) {
					pozostale_zycia -= 1;
					zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
					return pozostale_zycia;
				}
			}
		}
	}


	if (*wsk_czas <= 0) {
		pozostale_zycia -= 1;
		zabranie_i_wyzerowanie_planszy(wsk_czas, mario_wysokosc, mario_szerokosc, flaga1);
		if (pozostale_zycia <= 0) {
			//	zobaczyc czy potrzebne ?
			*flaga3 = 1;
			//nowa_gra(mario_wysokosc, mario_szerokosc, wsk_czas, wsk_pozostale_zycia, flaga1);
		}
		return pozostale_zycia;
	}
	else return pozostale_zycia;
}

void koniec_gry(SDL_Surface *screen, int czarny) {

	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, czarny, czarny);
}

void zmiana_polozenia_mario(double *mario_wsk_czas_chodzenia, double *mario_szerokosc, double delta, int *spr_wsk_kierunku, mario_animacja mario_anim, SDL_Surface *screen, SDL_Surface *przyklad_mario, polozenie mario, double *czas_latania, double *wsk_czas , int *flaga3 , int *spr_skoku){

	static double sprawdz_animacje_chodzenia = czas_animacji;  // 0.5 s jesli nie zostala zmieniona
	if (*flaga3 == 0){
	if (*mario_wsk_czas_chodzenia > 0) {
		if (*spr_wsk_kierunku == 0) {
			*mario_szerokosc -= predkosc_mario_pozioma*delta;
			*mario_wsk_czas_chodzenia -= delta;
			if ((sprawdz_animacje_chodzenia > 0) && (sprawdz_animacje_chodzenia <= czas_animacji / 3)) {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveL2, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpL, mario);
				}
			}
			else if ((sprawdz_animacje_chodzenia > czas_animacji / 3) && (sprawdz_animacje_chodzenia <= 2 * (czas_animacji / 3))) {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveL1, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpL, mario);
			}
			}
			else if ((sprawdz_animacje_chodzenia > 2 * (czas_animacji / 3)) && (sprawdz_animacje_chodzenia <= czas_animacji + 1)) {
				
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveL0, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpL, mario);
				}
			
			}
			else {
			
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveL1, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpL, mario);
				}
				sprawdz_animacje_chodzenia = czas_animacji;
			}
		}
		else if (*spr_wsk_kierunku == 1) {
			*mario_szerokosc += predkosc_mario_pozioma*delta;
			*mario_wsk_czas_chodzenia -= delta;
			if ((sprawdz_animacje_chodzenia > 0) && (sprawdz_animacje_chodzenia <= czas_animacji / 3)) {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveR2, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpR, mario);
				}
			}
			else if ((sprawdz_animacje_chodzenia > czas_animacji / 3) && (sprawdz_animacje_chodzenia <= 2 * (czas_animacji / 3))) {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveR1, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpR, mario);
				}
			}
			else if ((sprawdz_animacje_chodzenia > 2 * (czas_animacji / 3)) && (sprawdz_animacje_chodzenia <= czas_animacji + 1)) {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveR0, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpR, mario);
				}
			}
			else {
				if (*spr_skoku <= 0) {
					polozenie_mario(screen, mario_anim._moveR2, mario);
				}
				else {
					polozenie_mario(screen, mario_anim._jumpR, mario);
				}
				sprawdz_animacje_chodzenia = czas_animacji;
			}
		}
	}
	else {
		if (*spr_skoku <= 0) {
			polozenie_mario(screen, przyklad_mario, mario);
		}
		else {
			polozenie_mario(screen, mario_anim._jumpR, mario);
		}
		
	}
	sprawdz_animacje_chodzenia -= delta;
	}
}

void zabranie_i_wyzerowanie_planszy(double *wsk_czas, double *mario_wysokosc, double *mario_szerokosc, int *flaga1) {
	*flaga1 = 0;
	*wsk_czas = czas_rozgrywki;
	*mario_wysokosc = pozycja_poczatkoway;
	*mario_szerokosc = pozycja_poczatkowax;
}

int spr_bmp(SDL_Surface *wzor, SDL_Surface *screen, SDL_Texture *scrtex, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *charset) {
	if (wzor == NULL) {
		printf("SDL_LoadBMP(tekstura.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
}