#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element {
	double RE;
	double IM;
	struct element* poprzedni;
};

struct element* push(double nowa_gora_RE, double nowa_gora_IM, struct element *gora) {

	struct element *nowy;
	nowy = (struct element*)malloc(sizeof(struct element));
	nowy->RE = nowa_gora_RE;
	nowy->IM = nowa_gora_IM;
	nowy->poprzedni = gora;
	gora = &nowy[0];
	return gora;
}

struct element *pop(struct element *gora) {

	struct element *tymczasowy;

	if (gora == NULL)
	{
		printf("Na stosie nie ma elementu do pobrania!\n");
		return 0;
	}
	else {
		struct element *tymczasowy = gora->poprzedni;
		free(gora);
		gora = tymczasowy;
		return gora;
	}
}
struct element *wyczysc(struct element *gora) // czyszczenie stosu
{
	struct element *temp;

	while (gora != NULL)
	{
		temp = gora->poprzedni;
		free(gora);
		gora = temp;
	}

	return gora;
}
int pusty(struct element *gora)				//sprawdzenie czy stos nie jest pusty
{
	if (gora == NULL) {
		printf("Stos jest pusty");
		return 0;
	}
	else {
		printf("Na stosie sa nastepujace elementy:\n");
	}return 1;
}

void wyswietl(struct element *gora)			//wyswietlenie elementu stosu
{
	while (gora != NULL)
	{
		if ((*gora).IM == 0) {
			printf("%0.2f; ", (*gora).RE);
		}
		else if ((*gora).RE == 0) {
			printf("%0.2fi; ", (*gora).IM);
		}
		else {
			printf("%0.2f %0.2fi; ", (*gora).RE, (*gora).IM);
		}
		gora = (*gora).poprzedni;
	}

	return;
}

struct element* dodawanie(struct element* gora) {
	double wynik_RE, wynik_IM, RE1, RE2, IM1, IM2;
	RE1 = gora->RE;
	IM1 = gora->IM;
	gora = pop(gora);
	RE2 = gora->RE;
	IM2 = gora->IM;
	gora = pop(gora);

	wynik_RE = (RE1 + RE2);
	wynik_IM = (IM1 + IM2);
	gora = push(wynik_RE, wynik_IM, gora);
	return gora;
}

struct element* odejmowanie(struct element* gora) {
	double wynik_RE, wynik_IM, RE1, RE2, IM1, IM2;
	RE1 = gora->RE;
	IM1 = gora->IM;
	gora = pop(gora);
	RE2 = gora->RE;
	IM2 = gora->IM;
	gora = pop(gora);

	wynik_RE = (RE1 - RE2);
	wynik_IM = (IM1 - IM2);
	gora = push(wynik_RE, wynik_IM, gora);
	return gora;
}

struct element* mnozenie(struct element* gora) {
	double wynik_RE, wynik_IM, RE1, RE2, IM1, IM2;
	RE1 = gora->RE;
	IM1 = gora->IM;
	gora = pop(gora);
	RE2 = gora->RE;
	IM2 = gora->IM;
	gora = pop(gora);

	wynik_RE = (RE1*RE2) - (IM1*IM2);
	wynik_IM = (RE1*IM2) + (IM1 + RE2);

	gora = push(wynik_RE, wynik_IM, gora);
	return gora;
}

struct element* dzielenie(struct element* gora) {
	double wynik_RE, wynik_IM, RE1, RE2, IM1, IM2;
	RE1 = gora->RE;
	IM1 = gora->IM;
	gora = pop(gora);
	RE2 = gora->RE;
	IM2 = gora->IM;
	gora = pop(gora);

	wynik_RE = ((RE1*RE2) + (IM1*IM2)) / (IM2*IM2 + RE2 * RE2);
	wynik_IM = ((IM1*RE2) - (RE1*IM2)) / (IM2*IM2 + RE2 * RE2);

	gora = push(wynik_RE, wynik_IM, gora);
	return gora;
}

int main(void) {
	struct element *gora;
	struct element *pierwszy;
	char operator [10];
	char opcja[10];
	double nowa_gora_RE;
	double nowa_gora_IM;


	pierwszy = (struct element*)malloc(sizeof(struct element));
	pierwszy->RE = 0;
	pierwszy->IM = 0;
	pierwszy->poprzedni = NULL;
	gora = &pierwszy[0];
	gora = NULL;

	printf("RE IM - liczby oddzielone spacja, gdzie RE to czesc rzeczywista, a IM to czesc urojona liczby zespolonej\n");
	printf("Jesli na stosie sa przynajmniej dwie liczby mozesz wykonac na nich operacje.\n");
	printf("Podanie wiecej niz jednego operatora skutkuje wykonaniem pierwszej podanej operacji\n");
	printf("  1 - Dodanie liczby zespolonej\n  2 - Dodanie tylko czesci rzeczywistej, wowczas czesc urojona rowna jest 0\n->3 - Wykonanie operacji\n  4 - Sprawdzenie czy stos jest pusty\n  5 - Wyjscie z programu\n  6 - Wyczyszczenie stosu\n");

	while (1) {
	poczatek:
		printf("\nPodaj opcje:\n");
		scanf("%9s", opcja);
		switch (opcja[0]) {
		case '1': {
			printf("Prosze podac liczbe do stosu\n");
			scanf("%lf %lf", &nowa_gora_RE, &nowa_gora_IM);
			gora = push(nowa_gora_RE, nowa_gora_IM, gora);
			printf("Aktualny stos to:\n");
			wyswietl(gora);
		}; break;
		case '2': {
			printf("Prosze podac czesc rzeczywista do stosu\n");
			scanf("%lf", &nowa_gora_RE);
			nowa_gora_IM = 0;
			gora = push(nowa_gora_RE, nowa_gora_IM, gora);
			printf("Aktualny stos to:\n");
			wyswietl(gora);
		}; break;
		case '3': {
			printf("->Prosze wybrac dzialanie\n->W tym celu uzyj jednego ze znakow: +, -, *, /\n->Aby wrocic do menu glownego nacisnij '!'\n");
			while (1) {
				printf("\nPodaj 'podopcje':\n");
				scanf("%9s", operator);
				switch (operator[0]) {

				case '+':
				{
					if (gora == NULL || (*gora).poprzedni == NULL)
					{
						printf("Nie ma wystarczajacej ilosci liczb na stosie!\n");
						break;
					}
					gora = dodawanie(gora);
					printf("Aktualny stos to:\n");
					wyswietl(gora);
				}; break;
				case '-':
				{
					if (gora == NULL || (*gora).poprzedni == NULL)
					{
						printf("Nie ma wystarczajacej ilosci liczb na stosie!\n");
						break;
					}
					gora = odejmowanie(gora);
					printf("Aktualny stos to:\n");
					wyswietl(gora);
				}; break;
				case '*':
				{
					if (gora == NULL || (*gora).poprzedni == NULL)
					{
						printf("Nie ma wystarczajacej ilosci liczb na stosie!\n");
						break;
					}
					gora = mnozenie(gora);
					printf("Aktualny stos to:\n");
					wyswietl(gora);
				}; break;
				case '/':
				{
					if (gora == NULL || (*gora).poprzedni == NULL)
					{
						printf("Nie ma wystarczajacej ilosci liczb na stosie!\n");
						break;
					}
					gora = dzielenie(gora);
					printf("Aktualny stos to:\n");
					wyswietl(gora);
				}; break;
				case '!':
				{
					printf("Wrociles do menu glownego\n");
					goto poczatek;
				}; break;
				default:
				{
					printf("Nieprawidlowy znak\n");
				}; break;

				}
			}

		}; break;
		case '6': {
			gora = wyczysc(gora);
			printf("Stos zostal wyczyszczony\n");
		}; break;
		case '4': {
			printf("Sprawdzenie czy stos jest pusty:\n");
			pusty(gora);
			wyswietl(gora);
		}; break;
		case '5': {
			printf("Wychodzenie z programu");
			gora = pop(gora);
			free(pierwszy);
			exit(0);
		}; break;
		default:
		{
			printf("Nieprawidlowy znak\n");
			printf("Podaj opcje:\n");
		}; break;

		}
	}
	system("PAUSE");
	return 0;
}