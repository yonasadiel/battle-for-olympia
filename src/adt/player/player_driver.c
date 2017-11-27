#include "Player.h"
#include <stdio.h>

int main() {
	Player* player = (Player*) malloc(sizeof(Player));
	Point* loc = (Point*) malloc(sizeof(Point));
	Map* map = (Map*) malloc(sizeof(Map));

	MakePoint(5, 5, loc);
	MakeMap(10, 10, map);
	MakePlayer(player, CCYAN, *loc, map);
	printf("Player has been created.\n");
	AddUnit(player, *loc, 'K', map);
	printf("New unit added to player.\n");
	ResetMovPointAllUnit(player);
	printf("Reset all movement points.\n");

	return 0;
}