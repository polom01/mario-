//includ i define stale
#include "funkcja.h"
//DrawSurface(screen, podloga, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT-16 );             //uzyc do poruszania botami !!!!!!!!!!!

// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	polozenie mario;
	minionek_polozenie minionek_nr1;
	mario_animacja mario_anim;
	
	int tab_podlogi[SCREEN_HEIGHT / wymiary_podlogi][szerokosc_planszy / wymiary_podlogi];
	int t1, t2, frames, rc, pomoc_do_quit, do_flagi1, do_flagi2, do_flagi3, pozostale_zycia, spr_kierunku, do_spr_skoku;
	double delta, worldTime, fpsTimer, fps, pozostaly_czas, zmienna_do_czasu_latania , mario_czas_chodzenia , zmienna_minionx , zmienna_miniony, do_animacja_goombas;
	double *mario_wsk_czas_chodzenia = &mario_czas_chodzenia;
	int *spr_wsk_kierunku = &spr_kierunku;
	int *quit = &pomoc_do_quit;
	double *mario_szerokosc = &mario.pozx;
	double *mario_wysokosc = &mario.pozy;
	int *wsk_na_zycia;
	double *czas_latania = &zmienna_do_czasu_latania;

	SDL_Surface *screen, *charset;
	SDL_Surface *podloga, *przyklad_mario , *goombas01 , *goombas02 , *sciana , *spikey0_0 , *spikey0_1;    //obrazki bmp
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	pozostaly_czas = czas_rozgrywki;


	// tryb pe³noekranowy
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Kacper Po³om s165324");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	//////////////////////////////////////////////////////////////rozpoczecie akcji////////////////////////////////////////////////////////
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	podloga = SDL_LoadBMP("./podloga.bmp");
	spr_bmp(podloga, screen, scrtex, window, renderer, charset); 

		sciana = SDL_LoadBMP("./brickred.bmp");
	spr_bmp(podloga, screen, scrtex, window, renderer, charset);

	przyklad_mario = SDL_LoadBMP("./przyklad.bmp");
	spr_bmp(przyklad_mario, screen, scrtex, window, renderer, charset);

	mario_anim._moveL0 = SDL_LoadBMP("./1mario_move0.bmp");
	spr_bmp(mario_anim._moveL0, screen, scrtex, window, renderer, charset);

	mario_anim._moveL1 = SDL_LoadBMP("./1mario_move1.bmp");
	spr_bmp(mario_anim._moveL1, screen, scrtex, window, renderer, charset);

	mario_anim._moveL2 = SDL_LoadBMP("./1mario_move2.bmp");
	spr_bmp(przyklad_mario, screen, scrtex, window, renderer, charset);

	mario_anim._moveR0 = SDL_LoadBMP("./mario_move0.bmp");
	spr_bmp(mario_anim._moveR0, screen, scrtex, window, renderer, charset);

	mario_anim._moveR1 = SDL_LoadBMP("./mario_move1.bmp");
	spr_bmp(mario_anim._moveR1, screen, scrtex, window, renderer, charset);

	mario_anim._moveR2 = SDL_LoadBMP("./mario_move2.bmp");
	spr_bmp(mario_anim._moveR2, screen, scrtex, window, renderer, charset);

	mario_anim._jumpL= SDL_LoadBMP("./1mario_jump.bmp");
	spr_bmp(mario_anim._jumpL, screen, scrtex, window, renderer, charset);

	mario_anim._jumpR = SDL_LoadBMP("./mario_jump.bmp");
	spr_bmp(mario_anim._jumpR, screen, scrtex, window, renderer, charset);

	goombas01 = SDL_LoadBMP("./goombas_0.bmp");
	spr_bmp(mario_anim._jumpR, screen, scrtex, window, renderer, charset);

	goombas02 = SDL_LoadBMP("./goombas_1.bmp");
	spr_bmp(mario_anim._jumpR, screen, scrtex, window, renderer, charset);

	spikey0_0 = SDL_LoadBMP("./spikey0_0.bmp");
	spr_bmp(mario_anim._jumpR, screen, scrtex, window, renderer, charset);

	spikey0_1 = SDL_LoadBMP("./spikey0_1.bmp");
	spr_bmp(mario_anim._jumpR, screen, scrtex, window, renderer, charset);

	
	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);


	t1 = SDL_GetTicks();          //czas poczatkowy

	umieszczenie_pierwszej_przeszkody(tab_podlogi);
	//animacja_goombas = 0;
	frames = 0;
	fpsTimer = 0;
	fps = 0;
	*quit = 0;
	worldTime = 0;
	do_flagi1 = 0;
	do_flagi2 = 0;
	do_flagi3 = 0;
	*czas_latania = 0;
	 pozostale_zycia = liczba_zyc;
	 wsk_na_zycia=&pozostale_zycia;
	 minionek_nr1.pozx =&zmienna_minionx;
	 minionek_nr1.pozy = &zmienna_miniony;
	 *minionek_nr1.pozx = 16.5 * wymiary_podlogi;
	 *minionek_nr1.pozy = 2.5 * wymiary_podlogi;
	int *flaga1 = &do_flagi1;
	int *flaga2 = &do_flagi2;
	int *flaga3 = &do_flagi3;
	int *spr_skoku = &do_spr_skoku;
	double *wsk_czas = &pozostaly_czas;
	double *animacja_goombas = &do_animacja_goombas;
	*animacja_goombas = czas_anima_goombas;
	//zapis_pliku(mario_wysokosc , mario_szerokosc , wsk_czas , wsk_na_zycia, flaga1);
	

	*mario_wysokosc = (pozycja_poczatkoway  );
	*mario_szerokosc = pozycja_poczatkowax;
	///////////////////////////////////////////////////////////////////rozpoczecie petli///////////////////////////////////////////////////
	while (!(*quit)) {
		t2 = SDL_GetTicks();
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		//animacja_goombas += delta;
		worldTime += delta;
		SDL_FillRect(screen, NULL, niebieski);
		if (*flaga3 == 0) {
			malowanie_obrazu(mario_wysokosc, mario_szerokosc, screen, podloga, flaga1, flaga3, tab_podlogi, quit , sciana);
		//	polozenie_mario(screen, przyklad_mario, mario);
			if (*flaga1 == 0) {
				polozenie_minionka_nr1(screen, minionek_nr1, wsk_czas, goombas01, mario_szerokosc, flaga1, goombas02, delta, animacja_goombas);
			}
			else if (*flaga1 == 1) {
				polozenie_minionka_nr1(screen, minionek_nr1, wsk_czas, spikey0_0, mario_szerokosc, flaga1, spikey0_1, delta, animacja_goombas);
			}
			//	screen->w / 2 - strlen(text) * 15
			// tekst informacyjny
			//	DrawRectangle(screen, 4, 4, SCREEN_WIDTH /4, 36, czerwony, niebieski);
			sprintf(text, "Czas = %.1lf s ", pozostaly_czas);
			//sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
			DrawString(screen, 5, 10, text, charset);
			sprintf(text, "liczba zyc : %.1ld ", pozostale_zycia);
			//sprintf(text, "liczba zyc : %.1lf ", fps);
			DrawString(screen, 200, 10, text, charset);
			sprintf(text, "liczba monet :");
			DrawString(screen, 400, 10, text, charset);
			sprintf(text, "ESC = wyjscie     N = nowa gra");
			DrawString(screen, 5, 26, text, charset);
			*flaga2 = 0;
		}
		else {
			koniec_gry(screen, czarny);
			sprintf(text, "koniec gry wcisnij : ");
			DrawString(screen, 5, 10, text, charset);
			sprintf(text, "ESC = wyjscie     N = nowa gra");
			DrawString(screen, 5, 26, text, charset);
			*flaga2 = 1;
		}
		
		// naniesienie wyniku rysowania na rzeczywisty ekran
		//		SDL_Flip(screen);

		fpsTimer += delta;
		if (fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
		};
		pozostale_zycia = zabieranie_zyc(wsk_czas, pozostale_zycia, mario_wysokosc, mario_szerokosc, flaga1, flaga3, minionek_nr1);
		obs³uga_zdarzen(mario_wysokosc, mario_szerokosc, quit, czas_latania, delta, tab_podlogi, wsk_na_zycia, wsk_czas, flaga1, flaga3, mario_wsk_czas_chodzenia, spr_wsk_kierunku, mario_anim, screen, przyklad_mario, mario , spr_skoku);//kierowanie postaci¹

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_SetColorKey(przyklad_mario, true, 0xFF00FF);
	//	SDL_SetColorKey(przyklad_mario, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveL0, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveL1, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveL2, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveR1, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveR2, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._moveR0, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._jumpL, true, 0xFF00FF);
		SDL_SetColorKey(mario_anim._jumpR, true, 0xFF00FF);
		SDL_SetColorKey(goombas01, true, 0xFF00FF);
		SDL_SetColorKey(goombas02, true, 0xFF00FF);
		SDL_SetColorKey(spikey0_0, true, 0xFF00FF);
		SDL_SetColorKey(spikey0_1, true, 0xFF00FF);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y)
	//	polozenie_minionka(screen, minionek_nr1, wsk_czas, podloga);

	
		if(*flaga2 != 1) pozostaly_czas -= delta;   //obliczanie czasu
		else pozostaly_czas = czas_rozgrywki;
		frames++;
	};

	// zwolnienie powierzchni
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
