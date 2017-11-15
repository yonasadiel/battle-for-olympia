#ifndef GAME_COORDINATOR_H
#define GAME_COORDINATOR_H

#include "../boolean/boolean.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../queueint/queueint.h"
#include "../player/player.h"

#define NMaxPlayer 2
typedef struct {
  Player P[NMaxPlayer+1];
  Queue QI;
  Map GameMap;
  Stack MoveRecord;
} GameCoordinator;

void PrintFirstMenu(void);
/**
 * I.S. Game belum dimulai
 * F.S. menu utama tampil di layar beserta pilihannya (tanpa Load Game)
 */
void PrintNextMenu(void);
/**
 * I.S. Game sudah dimulai
 * F.S. menu utama tampil di layar beserta pilihannya (beserta Load Game)
 */
void InitGame(GameCoordinator* GC);
/**
 * I.S. GC tidak terdefinisi.
 * F.S. GC terdefinisi default.
 */
void LoadGame(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi.
 * F.S. GC terdefinisi sesuai save file.
 */
void SaveGame(GameCoordinator GC);
/**
 * I.S. GC terdefinisi.
 * F.S. save file terisi dengan GC.
 */
void RunGame(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi.
 * F.S. Game selesai.
 */

#endif
