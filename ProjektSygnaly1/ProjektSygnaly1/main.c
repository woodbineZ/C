#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <locale.h>
// #include <cctype>
// #include <cstring>
#define ampmax 2.0

struct punkt
{
	double x; // wspolrzedna x
	double y; // wspolrzedna y
	double s; // wspolrzedna y zaszumiona
};
struct tablica  // tablica wynikowa wraz z rozmiarem
{
	punkt *tabRES;
	int tabRESsize;
};

void show(tablica tab)
{
	int t;
	for (t = 0; t < tab.tabRESsize; t++)
		printf("x: %lf,  y: %lf s: %lf\n", tab.tabRES[t].x, tab.tabRES[t].y, tab.tabRES[t].s);
	system("PAUSE");
}
void wspolczynniki(double* tabWSP)
{
	puts("funkcja wspolczynniki sie rozpoczela");
	printf("Podaj wspolczynniki funkcji matematycznej\n");
	printf("Podaj wspolczynnik 'a' funkcji\n");
	scanf_s("%lf", &tabWSP[0]);
	printf("Podaj wspolczynnik 'b' funkcji\n");
	scanf_s("%lf", &tabWSP[1]);
	printf("Podaj wspolczynnik 'c' funkcji\n");
	scanf_s("%lf", &tabWSP[2]);
	do
	{
		printf("Podaj wspolczynnik 'd' funkcji, ktory powinien byc rozny od 0\n");
		scanf_s("%lf", &tabWSP[3]);

	} while (tabWSP[3] == 0);
}
void dziedzina(double* tabIKS)
{
	puts("funkcja dziedzina sie rozpoczela");
	printf("Podaj dolny zakres dziedziny\n");
	scanf("%lf", &tabIKS[0]);
	printf("Podaj gorny zakres dziedziny\n");
	scanf("%lf", &tabIKS[1]);
}
tablica filtr(tablica tab)
{
	puts("funkcja filtr sie rozpoczela");
	int i;
	double a1, a2, a3, tmp;
	double suma = 0;
	if (tab.tabRESsize <= 0)
	{
		puts("uruchom generowanie lub odczytaj z pliku dane");
		system("pause");
		return tab;
	}
	for (i = 0; i < tab.tabRESsize; i++)
	{
		if (i == 0) a1 = tab.tabRES[i].s;
		else a1 = tab.tabRES[i - 1].s;
		a2 = tab.tabRES[i].s;
		if (i == tab.tabRESsize - 1) a3 = tab.tabRES[i].s;
		else a3 = tab.tabRES[i + 1].s;
		if (a1 > a2)
		{
			tmp = a1;
			a1 = a2;
			a2 = tmp;
		}
		if (a3 < a1)
		{
			tmp = a3;
			a3 = a2;
			a2 = a1;
			a1 = tmp;
		}
		if (a3 < a2)
		{
			tmp = a3;
			a3 = a2;
			a2 = tmp;
		}
		//suma = suma + a2;
		tab.tabRES[i].y = a2; //suma / (i + 1);
	}
	return tab;
}
int rozmiarwynikow()
{
	puts("funkcja rozmiarwynikow sie rozpoczela");
	int ret;
	int p;
	do
	{
		printf("Podaj rozmiar tablicy wynikow\n");
		p = scanf("%d", &ret);
		if (ret <= 0 || p != 1) puts("Podaj wartosc calkowita wieksza od 0\n");
	} while (ret <= 0);
	return ret;
}
tablica generuj(tablica tab)
{
	puts("funkcja generuj sie rozpoczela");
	double tabWSP[4];
	double tabIKS[2];
	int i = 0;
	double stepx;
	double x;
	tab.tabRESsize = rozmiarwynikow();
	//free(tabRES);
	//tabRES = NULL;
	//printf("addr: %d\n", tabRES);
	tab.tabRES = (punkt*)realloc(tab.tabRES, tab.tabRESsize * sizeof(punkt));
	wspolczynniki(tabWSP);
	//printf("a: %lf  b: %lf  c: %lf  d: %lf\n", tabWSP[0], tabWSP[1], tabWSP[2], tabWSP[3]);
	dziedzina(tabIKS);
	x = tabIKS[0];
	stepx = (tabIKS[1] - tabIKS[0]) / (tab.tabRESsize - 1);
	//printf("x_from: %lf  x_to: %lf  Size: %d  Step: %lf\n", tabIKS[0], tabIKS[1], tabRESsize, stepx);
	//show(tabRES, tabRESsize); 
	for (i = 0; i < tab.tabRESsize; i++)
	{
		printf("i: %d, xi: %lf\n", i, x);
		if (x == 0)
		{
			double xx;
			xx = x + 0.00001;
			tab.tabRES[i].x = xx;
			tab.tabRES[i].y = (tabWSP[0] * xx*xx*sin((tabWSP[1] * xx) + tabWSP[2])) / (tabWSP[3] * xx);
			tab.tabRES[i].s = tab.tabRES[i].y;
		}
		else
		{
			tab.tabRES[i].x = x;
			tab.tabRES[i].y = (tabWSP[0] * x*x*sin((tabWSP[1] * x) + tabWSP[2])) / (tabWSP[3] * x);
			tab.tabRES[i].s = tab.tabRES[i].y;
		}
		x = x + stepx;
	}
	show(tab);
	return tab;
}

double randomdouble(double min, double max)
{
	puts("funkcja randomdouble sie rozpoczela");
	double tmp;
	if (max >= min)
		max -= min;
	else
	{
		tmp = min - max;
		min = max;
		max = tmp;
	}
	return max ? (rand() / (RAND_MAX + 1.0) * max + min) : min;
}
int randomint(int min, int max)
{
	puts("funkcja randomint sie rozpoczela");
	int tmp;
	if (max >= min)
		max -= min;
	else
	{
		tmp = min - max;
		min = max;
		max = tmp;
	}
	return max ? (rand() % max + min) : min;
}
tablica szumowanie(tablica tab)
{
	puts("funkcja szumowanie sie rozpoczela");
	int iloscprobek, i, nrElTabRES;
	double amplituda;
	if (tab.tabRESsize <= 0)
	{
		puts("uruchom generowanie lub odczytaj z pliku dane");
		system("pause");
		return tab;
	}
	iloscprobek = randomint(0, tab.tabRESsize - 1);
	amplituda = randomdouble(0, ampmax);
	for (i = 0; i < iloscprobek; i++)
	{
		do
		{
			nrElTabRES = randomint(0, tab.tabRESsize - 1);
		} while (tab.tabRES[nrElTabRES].y != tab.tabRES[nrElTabRES].s);
		tab.tabRES[nrElTabRES].s = tab.tabRES[nrElTabRES].y + randomdouble(-amplituda, amplituda);
	}
	return tab;
}
void zapis(tablica tab)
{
	puts("funkcja zapis sie rozpoczela");
	FILE *plik;
	char nazwa[256];
	char wybor[100];
	char znak;
	int i, error;
	if (tab.tabRESsize <= 0)
	{
		puts("uruchom generowanie lub odczytaj z pliku dane");
		system("pause");
		return;
	}
	do
	{
		printf("Podaj nazwe pliku (.csv)\n");
		scanf("%s", &nazwa);
		plik = fopen(nazwa, "w");
		if (plik == 0) puts("Podales niepoprawna nazwe pliku");
	} while (plik == 0);
	do
	{
		error = 0;
		puts("Czy wyniki (N)ormalne czy (Z)aszumione zapisac w pliku. Podaj 'Z' lub 'N'\n");
		scanf("%s", &wybor);
		if (strlen(wybor) != 1) error = 1;
		if (error == 0) znak = toupper(wybor[0]);
		if (error == 0 && znak != 'Z' && znak != 'N') error = 1;
		if (error == 1) puts("Podaj 'Z' lub 'N'");
	} while (error == 1);
	for (i = 0; i < tab.tabRESsize; i++)
	{
		fprintf(plik, "%lf;%lf\n", tab.tabRES[i].x, znak == 'Z' ? tab.tabRES[i].s : tab.tabRES[i].y);
	}
	fclose(plik);
}
tablica odczyt(tablica tab)
{
	puts("funkcja odczyt sie rozpoczela");
	FILE *plik;
	char nazwa[256];
	int rezultat;
	double x, y;
	do
	{
		printf("Podaj nazwe pliku (.csv)\n");
		scanf("%s", &nazwa);
		plik = fopen(nazwa, "r");
		if (plik == 0) puts("Podales niepoprawna nazwe pliku");
	} while (plik == 0);
	free(tab.tabRES);
	tab.tabRESsize = 0;
	tab.tabRES = NULL;
	do
	{
		rezultat = fscanf(plik, "%lf;%lf\n", &x, &y);
		if (rezultat != EOF && rezultat == 2)
		{
			tab.tabRESsize = tab.tabRESsize + 1;
			tab.tabRES = (punkt*)realloc(tab.tabRES, tab.tabRESsize * sizeof(punkt));
			tab.tabRES[tab.tabRESsize - 1].x = x;
			tab.tabRES[tab.tabRESsize - 1].y = y;
			tab.tabRES[tab.tabRESsize - 1].s = y;
		}
		else if (rezultat != 2 && rezultat != EOF) printf("Blad wewnatrz pliku w wierszu %d: ", tab.tabRESsize);
	} while (rezultat != EOF);
	fclose(plik);
	return tab;
}
int main()
{
	int opcja;
	int t = 0;
	tablica tbl;
	setlocale(LC_ALL, "");
	tbl.tabRES = (punkt*)malloc(0);
	tbl.tabRESsize = 0;
	//menu
	//	printf("addr: %d\n", tbl.tabRES);
	//	tbl=generuj(tbl);
	//	printf("addr: %d\n", tbl.tabRES);
	//	show(tbl);
	//	tbl=szumowanie(tbl);
	//show(tbl);
	//	zapis(tbl);
	//	zapis(tbl);
	//	tabRESsize=odczyt(tabRES);
	//	tbl=filtr(tbl);
	//show(tbl);
	//zapis(tbl);

	do
	{
		system("cls");
		puts("Witaj, wybierz:\n'1' Aby wygenerowac sygnal.\n'2' Aby wczytac plik.\n'3' Aby wprowadzic szum.\n'4' Aby odfiltorwac sygnal.\n'5' Aby zapisac aktualny stan sygnalu.");
		scanf("%d", &opcja);
		switch (opcja)
		{
		case 1: tbl = generuj(tbl); break;
		case 2: tabRESsize = odczyt(tabRES); break;
		case 3: tbl = szumowanie(tbl); break;
		case 4: tbl = filtr(tbl); break;
		case 5:zapis(tbl); break;
		default: puts("Podana niepoprawna wartosc"); system("pause"); break;
		}
	} while (opcja != 0);
	free(tbl.tabRES);
	return 0;
}