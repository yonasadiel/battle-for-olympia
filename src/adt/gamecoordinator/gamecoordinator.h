#ifndef GAME_COORDINATOR_H
#define GAME_COORDINATOR_H

#include "../boolean/boolean.h"
#include "../listlinier/listlinier.h"
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
  Unit* CurrentUnit;
} GameCoordinator;

/* *** Selektor *** */
#define Pi(GC,i) (GC).P[(i)]
#define QI(GC) (GC).QI
#define GameMap(GC) (GC).GameMap
#define MoveRecord(GC) (GC).MoveRecord
#define CurrentUnit(GC) (GC).CurrentUnit

void PrintMenu(void);
/**
 * I.S. Game belum dimulai
 * F.S. menu utama tampil di layar beserta pilihannya 
 */

void InitGame(GameCoordinator* GC, int NInitBaris, int NInitKolom);
/**
 * I.S. GC tidak terdefinisi.
 * F.S. GC terdefinisi default berukuran NInitBaris x NInitKolom.
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

void printPlayerInfo(Player P);
/**
 * I.S. P terdefinisi
 * F.S. Info mengenai player P muncul di layar
 */

void printCurrentUnitInfo(Unit U);
/**
 * I.S. U terdefinisi
 * F.S. Info mengenai unit U muncul di layar
 */

void EndTurn(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi
 * F.S. Current Player berganti beserta Current Unit dan Cash dikurangi upkeep
 */

void ReduceCash(Player* P);
/**
 * I.S. P terdefinisi
 * F.S. Cash P berkurang sesuai upkeep
 */

void UndoMovement(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi
 * F.S. Jika stack MoveRecord tidak kosong, kembalikan unit ke top stack
 *      Jika kosong, tampilkan pesan kesalahan
 */

void MoveUnit(Map* M, Unit* U, Point Source, Point Dest);
/**
 * I.S. Semua terdefinisi dan valid, Source mungkin sama dengan Dest
 * F.S. Memindahkan unit U dari Source ke Dest dengan mengganti Location,
 *      mengganti karakter di peta, dan mengganti warna di peta
 */

void ChangeUnit(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi
 * F.S. Menampilkan daftar unit player dan meminta input nomor
 *      Mengganti Current Unit dnegan unit pilihan player
 */

void NextUnit(GameCoordinator* GC);
/**
 * I.S. GC terdefinisi
 * F.S. Mengganti Current Unit dengan unit sesudahnya di list unit
 */

void PrintAllUnitInfo(ListSirkuler LU);
/**
 * I.S. LU terdefinisi
 * F.S. menuliskan semua unit yang ada di LU
 */

#endif
