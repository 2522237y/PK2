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

/** Funkcja wypełnia dany wiersz na przemian polami czarnymi i białymi, otrzymuje na przemian
argumenty, które decydują o kolejności wypłenienia. */
void nowy_wiersz(int tab[N][N], int pole_pierwsze, int pole_drugie, int wiersz);

/** Funkcja utworz_nowa_szachownice tworzy szachownice, wypełniają ją na przemian polami białymi i czarnymi
wykorzystuje do tego funkcję nowy_wiersz*/
void utworz_nowa_szachownice(int tablica[N][N]);

