#include "player.h"
#include <stdio.h>

int main() {
	Player* player1 = (Player*) malloc(sizeof(Player));
	Player* player2 = (Player*) malloc(sizeof(Player));
	Point* loc = (Point*) malloc(sizeof(Point));
	Map* map = (Map*) malloc(sizeof(Map));
	Unit* u = (Unit*) malloc(1* sizeof(Unit));
	ListSirkuler units;
	ListLinier buildings;
	LSCreateEmpty(&units);
  LLCreateEmpty(&buildings);
	InitPlayer(player1,100,100,units,buildings,CBLUE);
	printf("Player1 has been created.\n");
	MakePoint(5, 5, loc);
	MakeMap(10, 10, map);
	MakePlayer(player2, CCYAN, *loc, map);
	printf("Player2 has been created.\n");
	AddUnit(player2, *loc, 'K', map);
	printf("New unit added to player2.\n");
	DeleteUnit(player2, u, map);
	printf("Deleted unit from player2.\n");
	ResetMovPointAllUnit(player2);
	printf("Reset all movement points.\n");
	return 0;
}
