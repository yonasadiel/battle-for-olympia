#ifndef PLAYER_H
#define PLAYER_H

#include "../boolean/boolean.h"
#include "../color/color.h"
#include "../unit/unit.h"
#include "../building/building.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../point/point.h"
#include "../map/map.h"

#define Nil NULL

typedef struct {
	int Cash;                 /* jumlah uang yang dimiliki pemain */
	int Income;               /* jumlah pendapatan pemain tiap turn */
	ListSirkuler ListUnit;    /* list unit yang dimiliki pemain */
	ListLinier ListBuilding;  /* list building yang dimiliki pemain */
	Color Warna;              /* warna dari player */
} Player;

/* *** Selektor Player *** */
#define Cash(P) (P).Cash
#define Income(P) (P).Income
#define UpKeep(P) LSNbElmt(ListUnit(P)) 
#define ListUnit(P) (P).ListUnit
#define ListBuilding(P) (P).ListBuilding
#define Warna(P) (P).Warna

void InitPlayer(Player* P, int cash, int income, ListSirkuler units, ListLinier buildings, Color warna);
/**
 * TODO
 * ada orang tidak bertanggung jawab bikin fungsi ini tanpa header
 * ada sukarelawan?
 */

void MakePlayer(Player* P, Color W, Point Loc, Map* M);
/**
 * I.S. P sembarang, W valid
 * F.S. P terdefinisi dengan cash 50, income 0, upkeep 0, 
 *      ListUnit kosong, ListBuilding kosong, MovPoint 0,
 *      dan Warna sesuai W.
 *      Basecamp P ada di Loc
 */

void ResetMovPointAllUnit(Player* P);
/**
 * I.S. P terdefinisi
 * F.S. Semua Unit di P punya movement point 2
 */

#endif