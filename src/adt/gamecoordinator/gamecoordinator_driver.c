#include "gamecoordinator.h"
#include <stdio.h>
#include "../mesinkata/mesinkata.h"

int main() {
	// GameCoordinator GC;
	// InitGame(&GC, 8, 8);

	// Point point;
	// MakePoint(1, 2, &point);
	// Unit* unit = (Unit*) malloc(sizeof(Unit));
	// CreateUnit(unit, 'K', point);
	// CurrentUnit(GC) = unit;

	/*
	FILE* file = fopen("saved\\hee.dat", "r");
	if(file) {
		printf("S\n");
	} else {
		printf("N\n");
	}
	*/

	/*
	if(STARTKATA("saved\\hehe.dat")) {
		printf("OKE\n");
	} else {
		printf("FAILED\n");
	}
	*/

	// SaveGame(GC);
	// LoadGame(&GC);

	START(0);
	char c = CC;
	printf("%c\n", c);
	char d = CC;
	printf("%c\n", d);
	START(0);
	char e = CC;
	printf("%c\n", e);
}