/** @file */
#include <stdio.h>
#include <allegro5/allegro5.h>
#include "warcaby.h"

#define k 64 //szerokosc jednego wyswietlanego okienka

void nowy_wiersz(int tab[N][N], int pole_pierwsze, int pole_drugie, int wiersz)
{
	int i;
	int j = 1;

	for (i = 0; i<N; ++i)
	{
		if (j == 1)
			tab[wiersz][i] = pole_pierwsze;


		if (j == 2)
		{
			tab[wiersz][i] = pole_drugie;
			j = 0;
		}
		++j;
	}
}



void utworz_nowa_szachownice(int tablica[N][N])
{
	int i = 1;
	int j;

	for (j = 0; j < N; ++j)
	{
		if (i == 1)
			nowy_wiersz(tablica, pole_biale, pole_czarne, j);
		if (i == 2)
		{
			nowy_wiersz(tablica, pole_czarne, pole_biale, j);
			i = 0;
		}
		++i;
	}
}



void wyswietlaj_pionki(int tab[N][N], ALLEGRO_BITMAP * czarny, ALLEGRO_BITMAP * bialy, ALLEGRO_BITMAP * damka_b, ALLEGRO_BITMAP * damka_cz)
{

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (tab[i][j] == pionek_czarny)
			{
				al_draw_bitmap(czarny, j*k, i*k, NULL);
			}

			if (tab[i][j] == pionek_bialy)
			{
				al_draw_bitmap(bialy, j*k, i*k, NULL);
			}
			if (tab[i][j] == damka_biala)
			{
				al_draw_bitmap(damka_b, j*k, i*k, NULL);
			}
			if (tab[i][j] == damka_czarna)
			{
				al_draw_bitmap(damka_cz, j*k, i*k, NULL);
			}

		}
	}
}

void rozloz_pionki_gracza(int tab[N][N], int gracz, int rzad_startowy)
{
	int i;
	int j;

	for (j = rzad_startowy; j < rzad_startowy + 3; ++j)
	{
		for (i = 0; i < N; ++i)
		{
			if (tab[j][i] == 1)
				tab[j][i] = gracz;
		}
	}
}



void wykonaj_ruch(int tab[N][N], int pola[N])
{
	int temp;

	temp = tab[pola[4]][pola[5]];
	tab[pola[4]][pola[5]] = pole_czarne;
	tab[pola[6]][pola[7]] = temp;


	if (temp == pionek_bialy && pola[6] == 0)
		tab[pola[6]][pola[7]] = damka_biala;


	if (temp == pionek_czarny && pola[6] == 7)
		tab[pola[6]][pola[7]] = damka_czarna;

}

bool sprawdz_koniec(int tab[N][N], int gracz_pionek, int gracz_damka)
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab[i][j] == gracz_pionek || tab[i][j] == gracz_damka)
				return false;
		}
	}

	return true;

}



bool damka_nastepne_bicie(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik)
{
	//iterowanie a¿ napotka przeciwnika
	//sprawdzenie czy nastepne pole o pole czarne-jeœli tak to return true
	int temp_x;
	int temp_y;
	int x = pola[6];
	int y = pola[7];

	int i = 1;
	int straznik = 0;//pilnuj¹ czy dla danego kierunku, po drodze nie wys¹pi³ w³asny pionek

	temp_x = x;
	temp_y = y;

	while (x >= 0 && x < N && y >= 0 && y < N && straznik==0)
	{	
		++x;
		--y;
		//1 kierunek
		if (tab[x][y] != pole_czarne && tab[x ][y] != przeciwnik)
			if (tab[x][y] != d_przeciwnik)
				++straznik;


		if (tab[x][y] == przeciwnik || tab[x][y] == d_przeciwnik)
			if (tab[x + 1][y- 1] == pole_czarne)
				return true;
	}

	x=temp_x;
	y=temp_y;
	straznik = 0;
	
	while (x >= 0 && x < N && y >= 0 && y < N && straznik == 0)
	{
		//2 kierunek
		++x;
		++y;

		if (tab[x][y] != pole_czarne && tab[x][y] != przeciwnik)
			if (tab[x][y] != d_przeciwnik)
				++straznik;


		if (tab[x][y] == przeciwnik || tab[x][y] == d_przeciwnik)
			if (tab[x + 1][y + 1] == pole_czarne)
				return true;
	}
	x = temp_x;
	y = temp_y;
	straznik = 0;
	while (x >= 0 && x < N && y >= 0 && y < N && straznik == 0)
	{
		//3 kierunek
		--x;
		--y;

		if (tab[x][y] != pole_czarne && tab[x][y] != przeciwnik)
			if (tab[x][y] != d_przeciwnik)
				++straznik;


		if (tab[x][y] == przeciwnik || tab[x][y] == d_przeciwnik)
			if (tab[x - 1][y - 1] == pole_czarne)
				return true;
	}
	x = temp_x;
	y = temp_y;
	straznik = 0;
	while (x >= 0 && x < N && y >= 0 && y < N && straznik == 0)
	{
		//4 kierunek
		--x;
		++y;

		if (tab[x][y] != pole_czarne && tab[x][y] != przeciwnik)
			if (tab[x][y] != d_przeciwnik)
				++straznik;


		if (tab[x][y] == przeciwnik || tab[x][y] == d_przeciwnik)
			if (tab[x - 1][y + 1] == pole_czarne)
				return true;
	}

	return false;
}


bool damka(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik)
{
	
	int z_temp = damka_biala;

	if (d_przeciwnik == damka_biala)
		z_temp = damka_czarna;


	if (z_temp != tab[pola[4]][pola[5]])
		return false;


	

	int z_x = pola[4];
	int z_y = pola[5];
	int na_x = pola[6];
	int na_y = pola[7];

	int odleglosc_x = abs(z_x - na_x);
	int odleglosc_y = abs(z_y - na_y);

	//damka rusza sie tylko po ukosie, tylko na czarne pole
	if (odleglosc_x != odleglosc_y || tab[na_x][na_y] != pole_czarne)
		return false;

	

	int straznik = 0;//pilnuje ile pionkow przeciwnika spotka na drodze, jesli wiecej niz jeden to ruch niepoprawny
	int i = 1;
	int zbij_x = 0;
	int zbij_y = 0;//wpolrzedne do zbicia

	if (z_x < na_x  && odleglosc_x >1)
	{
		if (na_y < z_y)
		{
			while (i < odleglosc_x)
			{
				if (tab[z_x + i][z_y - i] != pole_czarne && tab[z_x + i][z_y - i] != przeciwnik)//po drodze moze byc tylko przeciwnik.
					if (tab[z_x + i][z_y - i] != d_przeciwnik)
						return false;

				if (tab[z_x + i][z_y - i] == przeciwnik || tab[z_x + i][z_y - i] == d_przeciwnik)
				{
					++straznik;

					if (straznik > 1)
						return false;

					zbij_x = z_x + i;
					zbij_y = z_y - i;
				}
				++i;
			}
		}
		else //(na_y > z_y)
		{
			while (i < odleglosc_x)
			{
				if (tab[z_x + i][z_y + i] != pole_czarne && tab[z_x + i][z_y + i] != przeciwnik)
					if (tab[z_x + i][z_y + i] != d_przeciwnik)
						return false;

				if (tab[z_x + i][z_y + i] == przeciwnik || tab[z_x + i][z_y + i] == d_przeciwnik)
				{
					++straznik;

					if (straznik > 1)
						return false;
					zbij_x = z_x + i;
					zbij_y = z_y + i;
				}
				++i;
			}
		}
		tab[zbij_x][zbij_y] = pole_czarne;
	}
	if (z_x > na_x  && odleglosc_x >1)
	{
		if (na_y < z_y)
		{
			while (i < odleglosc_x)
			{
				if (tab[z_x - i][z_y - i] != pole_czarne && tab[z_x - i][z_y - i] != przeciwnik)
					if (tab[z_x - i][z_y - i] != d_przeciwnik)
						return false;

				if (tab[z_x - i][z_y - i] == przeciwnik || tab[z_x - i][z_y - i] == d_przeciwnik)
				{
					++straznik;

					if (straznik > 1)
						return false;
					zbij_x = z_x - i;
					zbij_y = z_y - i;
				}
				++i;
			}
		}
		else //(na_y > z_y)
		{
			while (i < odleglosc_x)
			{
				if (tab[z_x - i][z_y + i] != pole_czarne && tab[z_x - i][z_y + i] != przeciwnik)
					if (tab[z_x - i][z_y + i] != przeciwnik)
						return false;

				if (tab[z_x - i][z_y + i] == przeciwnik || tab[z_x - i][z_y + i] == d_przeciwnik)
				{
					++straznik;

					if (straznik > 1)
						return false;
					zbij_x = z_x - i;
					zbij_y = z_y + i;
				}
				++i;
			}
		}
		tab[zbij_x][zbij_y] = pole_czarne;
	}


	wykonaj_ruch(tab, pola);

	return true;


}


bool sprawdz_wielokrotny_pionek(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik)
{
	int x = pola[6];
	int y = pola[7];


	int i = 0;//sprawdza dla bialych lub czarnych

	if (przeciwnik == pionek_czarny)
		i = 1;


	if (i == 0)
	{
		if (x < 6 && y<6 && tab[x + 2][y + 2] == pole_czarne && (tab[x + 1][y + 1] == przeciwnik || tab[x + 1][y + 1] == d_przeciwnik)) //sprawdzenie czy jest przecwinik
			return true;

		if (x < 6 && y>1 && tab[x + 2][y - 2] == pole_czarne && (tab[x + 1][y - 1] == przeciwnik || tab[x + 1][y - 1] == d_przeciwnik))  //sprawdzenie czy jest wolne pole
			return true;
	}
	if (i == 1)
	{
		if (x > 1 && y < 6 && tab[x - 2][y + 2] == pole_czarne && (tab[x - 1][y + 1] == przeciwnik || tab[x - 1][y + 1] == d_przeciwnik))
			return true;

		if (x >2 && y >1 && tab[x - 2][y - 2] == pole_czarne && (tab[x - 1][y - 1] == przeciwnik || tab[x - 1][y - 1] == d_przeciwnik))
			return true;
	}

	return false;


}




int sprawdzaj_ruch(int tab[N][N], int pola[N], int obecny_gracz)
{

	int przeciwnik = pionek_bialy;
	int damka_przecwnik = damka_biala;

	if (obecny_gracz == gracz_bia³y)
	{
		przeciwnik = pionek_czarny;
		damka_przecwnik = damka_czarna;
	}


	//spradzenie czy damka i odpalenie dla niej funkcji
	if (tab[pola[4]][pola[5]] == damka_biala || tab[pola[4]][pola[5]] == damka_czarna)
	{

		if (damka(tab, pola, przeciwnik, damka_przecwnik) == true)
		{
			if (damka_nastepne_bicie(tab,pola,przeciwnik,damka_przecwnik) == true)//mozliwe wielokrotne, wiec jeszcze raz ten gracz
				return 0;

			else
				return 3;
		}
	}



	//zmienne z jakiej pozycji siê rusza i na jak¹ chce iœæ
	int z_pola = tab[pola[4]][pola[5]];
	int na_pole = tab[pola[6]][pola[7]];

	int pionek_zbity_x = (pola[4] + pola[6]) / 2;
	int pionek_zbity_y = (pola[5] + pola[7]) / 2;


	//sprawdzenie czy nie swoim pionkiem, wed³ug kolejnoœci
	int z_temp = pionek_bialy;

	if (obecny_gracz == gracz_czarny)
		z_temp = pionek_czarny;

	if (z_temp != z_pola)
		return 0;

	//ruch z pustego pola, lub na niedozwolone pole bia³e
	if (z_pola == pole_biale || z_pola == pole_czarne || na_pole != pole_czarne)
		return 0;



	//sprawdzenie czy nie cofn¹³ ruchu
	if (z_temp == pionek_bialy)
	{
		if (pola[6] > pola[4])
			return 0;
	}
	else
	{
		if (pola[4] > pola[6])
			return 0;
	}

	//spradzeni czy ruch nie jest za d³ugi,mo¿e zbijaæ
	int dlugosc_x = abs(pola[4] - pola[6]);
	int dlugosc_y = abs(pola[5] - pola[7]);

	if (dlugosc_x > 2 || dlugosc_y > 2)
		return 0;

	if (dlugosc_x == 2 || dlugosc_y == 2)
	{
		if (tab[pionek_zbity_x][pionek_zbity_y] == przeciwnik || tab[pionek_zbity_x][pionek_zbity_y] == damka_przecwnik)//poprawne zbicie
		{
			tab[pionek_zbity_x][pionek_zbity_y] = pole_czarne;//usuniêcie pionka

			if (sprawdz_wielokrotny_pionek(tab, pola, przeciwnik, damka_przecwnik) == true)//sprawdzenie czy jeszcze cos moze zbic
				return 2;

			return 1;
		}
		else
			return 0;
	}

	return 1;

}

bool odczytaj_pola(int punkty[N], int szachownica[N][N], int obecny_gracz)
{
	int i = 0;
	int temp = punkty[i];
	int j = 0;

	while (i < N && j < 4)
	{
		if (temp > i*k && temp < (i + 1)*k)
		{
			punkty[j + 4] = i;
			temp = punkty[++j];
			i = -1;
		}
		++i;
	}

	int koniec = sprawdzaj_ruch(szachownica, punkty, obecny_gracz);

	switch (koniec)
	{
	case 0:
		return false;

	case 1:

		wykonaj_ruch(szachownica, punkty);
		return true;

	case 2:
		wykonaj_ruch(szachownica, punkty);
		return false;

	case 3:
		return true;
	}
}


bool graj()
{
	//rozmiar okienka
	int width = 512;
	int height = 512;
	bool done = false;

	int polozenie[N];
	int kolejnosc = 0;

	//zmienne allegro
	ALLEGRO_BITMAP* pionek_cz = NULL;
	ALLEGRO_BITMAP *pionek_b = NULL;
	ALLEGRO_BITMAP* damka_cz = NULL;
	ALLEGRO_BITMAP *damka_b = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *tab = NULL;

	//program init Allegro
	if (!al_init())
		return -1;

	//wyswielta obiekt
	display = al_create_display(width, height);

	//testowanie wyswietlania
	if (!display)
		return -1;

	//inicjalizacja
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();

	//wczytanie bitmap
	tab = al_load_bitmap("tab.jpg");
	pionek_b = al_load_bitmap("bialy.png");
	pionek_cz = al_load_bitmap("czarny.png");

	damka_cz = al_load_bitmap("cz_damka.png");
	damka_b = al_load_bitmap("b_damka.png");

	//szachownica - tablica
	int szachownica[N][N];
	utworz_nowa_szachownice(szachownica);

	//wczytanie szachownicy
	al_draw_bitmap(tab, 0, 0, NULL);

	//rozlozenie w tablicy graczy
	rozloz_pionki_gracza(szachownica, 4, 0);
	rozloz_pionki_gracza(szachownica, 2, 5);
	//szachownica[2][3] = 4;


	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());


	while (done == false)
	{

		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		//esc mozna wyjsc
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		//¿eby przenieœæ pionek trzeba go chwyciæ i przytrzymaæ.
		//z pola
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			polozenie[1] = ev.mouse.x;
			polozenie[0] = ev.mouse.y;
		}

		//na pole+odpowiednia kolejnosc-zaczyna bia³y zawsze
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			polozenie[3] = ev.mouse.x;
			polozenie[2] = ev.mouse.y;

			if (kolejnosc == 0) //gracz bia³y
			{
				//ruch niepoprawny, wiêc jeszcze raz bia³y
				if (odczytaj_pola(polozenie, szachownica, gracz_bia³y) == false)
					kolejnosc = -1;
				else
					kolejnosc = 0;

			}

			if (kolejnosc == 1)//czarny
			{
				//ruch niepoprawny, wiêc jeszcze raz czarny
				if (odczytaj_pola(polozenie, szachownica, gracz_czarny) == false)
					kolejnosc = 0;

				else
					kolejnosc = -1;
			}

			++kolejnosc;
		}

		al_draw_bitmap(tab, 0, 0, NULL);

		wyswietlaj_pionki(szachownica, pionek_cz, pionek_b, damka_b, damka_cz);

		if (sprawdz_koniec(szachownica, pionek_czarny, damka_czarna) == true)
		{
			done = true;//koniec gry wygra³ gracz bia³y

		}

		if (sprawdz_koniec(szachownica, pionek_bialy, damka_biala) == true)
		{
			done = true;//koniec gry wygra³ gracz czarny
		}

		al_flip_display();
	}

	//zniszczenie bitmap
	al_destroy_bitmap(pionek_cz);
	al_destroy_bitmap(pionek_b);
	al_destroy_bitmap(damka_cz);
	al_destroy_bitmap(damka_b);
	al_destroy_bitmap(tab);

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return true;
}