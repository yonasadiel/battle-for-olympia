#include "gamecoordinator.h"
#include <stdio.h>

int main() {
	GameCoordinator GC;
	InitGame(&GC);

	Point point;
	MakePoint(1, 2, &point);
	Unit* unit = (Unit*) malloc(sizeof(Unit));
	CreateUnit(unit, 'K', point);
	CurrentUnit(GC) = unit;

	//SaveGame(GC);
	LoadGame(&GC);
}