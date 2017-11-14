#ifndef PLAYER_H
#define PLAYER_H

#include "../boolean/boolean.h"
#include "../color/color.h"
#include "../unit/unit.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"

#define Nil NULL

typedef struct {
	int Cash;                 /* jumlah uang yang dimiliki pemain */
	int Income;               /* jumlah pendapatan pemain tiap turn */
	int UpKeep;               /* jumlah pengeluaran pemain tiap turn */
	ListSirkuler ListUnit;    /* list unit yang dimiliki pemain */
	ListLinier ListBuilding;  /* list building yang dimiliki pemain */
	Color Warna;              /* warna dari player */
} Player;

/* *** Selektor Player *** */
#define Cash(P) (P).Cash
#define Income(P) (P).Income
#define UpKeep(P) (P).UpKeep
#define ListUnit(P) (P).ListUnit
#define ListBuilding(P) (P).ListBuilding
#define Warna(P) (P).Warna

void MakePlayer(Player* P, Color W);
/**
 * I.S. P sembarang, W valid
 * F.S. P terdefinisi dengan cash 50, income 0, upkeep 0, 
 *      ListUnit kosong, ListBuilding kosong, MovPoint 0,
 *      dan Warna sesuai W.
 */

#endif