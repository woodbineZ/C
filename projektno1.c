#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
struct punkt
{
	double x;
	double y;
};
void generuj(double* tabWSP, double* tabIKS, punkt* tabRES, int tabRESsize)
{
	int i = 0;
	double stepx;
	double x = tabIKS[0];
	int dziura=0;
	if (tabRESsize <= 1)
	{
		puts("tabRESsize ma za maly rozmiar");
		system("pause");
		return;
	}
	if (tabIKS[0] * tabIKS[1] <= 0)
		dziura = 1;
	stepx = (tabIKS[1] - tabIKS[0]) / (tabRESsize - 1);
	for (i = 0; i <= tabRESsize; i++)
	{
		if (x == 0) i++;

		tabRES[i].x = x;
		tabRES[i].y = (tabWSP[0] * x*x*sin((tabWSP[1] * x) + tabWSP[2])) / (tabWSP[3] * x);
		x = x + stepx;
	}
}
void wspolczynniki(double* tabWSP)
{
	
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
	printf("Podaj dolny zakres dziedziny\n");
	scanf("%lf", &tabIKS[0]);
	printf("Podaj gorny zakres dziedziny\n");
	scanf("%lf", &tabIKS[1]);
}
int main()
{
	int t = 0;
	double tabWSP[3];
	double tabIKS[1];
	punkt tabRES[10];
	wspolczynniki(&tabWSP[0]);
	dziedzina(&tabIKS[0]);
	printf("%lf, %lf, %lf, %lf\n", tabWSP[0], tabWSP[1], tabWSP[2], tabWSP[3]);
	printf("%lf, %lf", tabIKS[0], tabIKS[1]);
	generuj(&tabWSP[0], &tabIKS[0], &tabRES[0], 10);
	for (t = 0; t <= 10; t++)
	{
		printf("pkt1: %d : %lf, %lf\n", t, tabRES[t].x, tabRES[t].y);
	}
	system("PAUSE");
	return 0;
}