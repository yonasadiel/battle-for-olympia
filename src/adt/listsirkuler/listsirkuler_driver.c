#include "listsirkuler.h"
#include <stdio.h>

typedef struct {
	int x;
	int y;
} Titik;

Titik createTitik(int x, int y) {
	Titik titik;
	titik.x = x;
	titik.y = y;
	return titik;
}

void PrintTitik(Titik titik) {
	printf("<%d %d>", titik.x, titik.y);
}

int main() {
	Titik titik1 = createTitik(1, 2);
	Titik titik2 = createTitik(2, 3);
	Titik titik3 = createTitik(3, 4);

	ListSirkuler L;

	LSCreateEmpty(&L);

	LSInsVFirst(&L, &titik1);
	LSInsVFirst(&L, &titik2);
	LSInsVFirst(&L, &titik3);

	address p = LSFirst(L);
	do {
		Titik* titikerToTitik = (Titik*) LSInfo(p);
		Titik isiTitikerTitik = *titikerToTitik; 

		PrintTitik(isiTitikerTitik);
		p = LSNext(p);
	} while(p != LSFirst(L));


	return 0;
}