#include "gamecoordinator.h"
#include "../boolean/boolean.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../queueint/queueint.h"
#include "../player/player.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

int main() {
	GameCoordinator GC;
	ListSirkuler LS;
	InitGame(&GC,8,8);
	GetListSurroundingUnit(GC,&LS);
	return 0;
}
