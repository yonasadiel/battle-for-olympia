#include "gamecoordinator.h"
#include <stdio.h>
#include "../mesinkata/mesinkata.h"

int main() {
	GameCoordinator GC;
	int x;
	boolean err;

	InitGame(&GC, 8, 8);

	Point point;
	MakePoint(1, 2, &point);
	Unit* unit = (Unit*) malloc(sizeof(Unit));
	CreateUnit(unit, 'K', point);
	CurrentUnit(GC) = unit;

	SaveGame(GC);
	LoadGame(&GC);
}