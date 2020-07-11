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