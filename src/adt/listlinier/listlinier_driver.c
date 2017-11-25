#include "listlinier.h"
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
	Titik* Ttemp;
	Titik titik1 = createTitik(1, 2);
	Titik titik2 = createTitik(2, 3);
	Titik titik3 = createTitik(3, 4);

	ListLinier L;

	LLCreateEmpty(&L);

	LLInsVFirst(&L, &titik1);
	LLInsVFirst(&L, &titik2);
	LLInsVFirst(&L, &titik3);

	Ttemp = (Titik*) LLInfo(LLNthAddress(L, 1)); PrintTitik(*Ttemp);
	Ttemp = (Titik*) LLInfo(LLNthAddress(L, 2)); PrintTitik(*Ttemp);
	Ttemp = (Titik*) LLInfo(LLNthAddress(L, 3)); PrintTitik(*Ttemp);

	LLAddress p = LLFirst(L);
	while(p != Nil) {
		Titik* titikerToTitik = (Titik*) LLInfo(p);
		Titik isiTitikerTitik = *titikerToTitik; 

		PrintTitik(isiTitikerTitik);
		p = LLNext(p);
	}

	return 0;
}