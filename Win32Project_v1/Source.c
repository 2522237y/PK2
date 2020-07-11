/** @file */
#include <stdio.h>
#include "warcaby.h"


int main(int argc, char *argv[])
{
	char wyjscie = "o";

	char *nazwa_pliku = NULL;

	//for (int i = 0; i < argc; ++i) {
	if (argv[2] != NULL)
	{
		nazwa_pliku = argv[2];
	}
	else 
	{
		nazwa_pliku = "output_file.txt";
	}

	//}


	graj(nazwa_pliku);

	return 0;
}