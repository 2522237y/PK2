#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>


enum szachownica
{
	pole_biale,
	pole_czarne,
	pionek_bialy,
	damka_biala,
	pionek_czarny,
	damka_czarna,
	gracz_biały = 10,
	gracz_czarny = 11,
	N = 8, //rozmiar szachownicy
};

void zapisz_parametry_mapy_na_koncu_gry_do_pliku_(int szachownica[N][N]);

/** Funkcja wypełnia dany wiersz na przemian polami czarnymi i białymi, otrzymuje na przemian
argumenty, które decydują o kolejności wypłenienia. */
void nowy_wiersz(int tab[N][N], int pole_pierwsze, int pole_drugie, int wiersz);

/** Funkcja utworz_nowa_szachownice tworzy szachownice, wypełniają ją na przemian polami białymi i czarnymi
wykorzystuje do tego funkcję nowy_wiersz*/
void utworz_nowa_szachownice(int tablica[N][N]);


/**Wyświetla pionki na szachownicy, wykorzystując bibliotekę allegro.*/
void wyswietlaj_pionki(int tab[N][N], ALLEGRO_BITMAP * czarny, ALLEGRO_BITMAP * bialy, ALLEGRO_BITMAP * damka_b, ALLEGRO_BITMAP * damka_cz);


/**Funkcja rozkłada pionki dla danego gracza na szachownicy,
rozkłada po 3 rzędy pionków, tylko na polach czarnych.*/
void rozloz_pionki_gracza(int tab[N][N], int gracz, int rzad_startowy);

/**Wykonuje ruch dla otrzymanych współrzędnych oraz sprawdza czy nie
trzeba zmienić pionka w damkę gdy osiągnie ostatni rząd szachownicy.*/
void wykonaj_ruch(int tab[N][N], int pola[N]);

/**Sprawdza koniec gry, czyli zwraca true jeśli nie  napotka  pionka lub damki dla danego gracza.*/
bool sprawdz_koniec(int tab[N][N], int gracz_pionek, int gracz_damka);


/** Funkcja sprawdza możliwość kolejnego zbicia dla damki dla danego gracza,
korzysta z współrzędnych na których znajdzie się damka,
zwraca true gdy jest taka możliwość*/
bool damka_nastepne_bicie(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik);

/**Sprawdza poprawność ruchu damki, sprawdza czy zbija tylko jednego przeciwnika, czy
obecny gracz nie poruszły się nie swoją damka, zbija ewentualnyego przeciwnika
wywołuje funkcje wykonującą ruch, a następnie wywołuje funkcje, która sprawdzi możliwe
następne bicie.*/
bool damka(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik);

/**Funkcja sprawdza możliwość kolejnego zbicia dla pionka w tej samej kolejce danego gracza,
jeśli jest możliwe zwraca true.*/
bool sprawdz_wielokrotny_pionek(int tab[N][N], int pola[N], int przeciwnik, int d_przeciwnik);

/**Sprawdza poprawność ruchu pionka, gdy jest to damka wywołuje odpowiednią funkcję, zbija pionka
jeśli jest taka możliwość */
int sprawdzaj_ruch(int tab[N][N], int pola[N], int obecny_gracz);

/**Odczytanie współrzeędnych myszki(pierwsze cztery elementy tablicy punkty)
obliczenie z tego pól na szachownicy - elementy 4-7 , następnie wywołuje funkcję sprawdzającą
ruch, dla otrzymanych wyyników odpowiednio decyduję jakie zakończenie ruchu wybrać, lub czy
jest możliwy jeszcze jeden ruch gracza w tej kolejce, wtedy zwraca false*/
bool odczytaj_pola(int punkty[N], int szachownica[N][N], int obecny_gracz);


/**Funkcja zarząda wszystkimi pozostałymi funkcjami, generuje obrazy, pobiera i wczytuje bitmapy
pobiera wpółrzędne myszki, wywołuje funkcje odpowiedzialne za ruchy i wyświetlanie obrazu, kończy grę */
bool graj(char *nazwa_pliku);

