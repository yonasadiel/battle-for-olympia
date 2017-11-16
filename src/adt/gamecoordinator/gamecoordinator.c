#include "gamecoordinator.h"
#include "../boolean/boolean.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../queueint/queueint.h"
#include "../player/player.h"
#include <stdio.h>
#include <conio.h>

/* #define NMaxPlayer 2 */
/* typedef struct { */
/*   Player P[NMaxPlayer+1]; */
/*   Queue QI; */
/*   Map GameMap; */
/*   Stack MoveRecord; */
/*   Unit* CurrentUnit; */
/* } GameCoordinator; */

/* *** Selektor *** */
/* #define Pi(GC,i) (GC).P[(i)] */
/* #define QI(GC) (GC).QI */
/* #define GameMap(GC) (GC).GameMap */
/* #define MoveRecord(GC) (GC).MoveRecord */
/* #define CurrentUnit(GC) (GC).CurrentUnit */

void PrintMenu(void) {
  //
}

void InitGame(GameCoordinator* GC) {
  //
}

void LoadGame(GameCoordinator* GC) {
  //
}

void SaveGame(GameCoordinator GC) {
  //
}

void RunGame(GameCoordinator* GC) {
  system("cls");

  printPlayerInfo(Pi(*GC,QInfoHead(QI(*GC))));
  printCurrentUnitInfo(*CurrentUnit(*GC));

}

void printPlayerInfo(Player P) {
  printf("Player %d's Turn\n");
  printf("Cash: %dG | Income: %dG | Upkeep: %dG\n", Cash(P), Income(P), UpKeep(P));
}

void printCurrentUnitInfo(Unit U) {
  printf("Unit: ");
  PrintUnitName(U);
  TulisPoint(Location(U));
  printf(" | Movement Point: %d | Can Attack: ", MovPoint(U));
  if (AtkChance(U)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}