#include "player.h"
#include "../boolean/boolean.h"
#include "../color/color.h"
#include "../unit/unit.h"
#include "../building/building.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../point/point.h"

/* #define Nil NULL */

/* typedef struct { */
/*   int Cash;                 /* jumlah uang yang dimiliki pemain */
/*   int Income;               /* jumlah pendapatan pemain tiap turn */
/*   int UpKeep;               /* jumlah pengeluaran pemain tiap turn */
/*   ListSirkuler ListUnit;    /* list unit yang dimiliki pemain */
/*   ListLinier ListBuilding;  /* list building yang dimiliki pemain */
/*   int MovPoint;             /* movement point yang tersisa */
/*   Color Warna;              /* warna dari player */
/* } Player; */

/* *** Selektor Player *** */
/* #define Cash(P) (P).Cash */
/* #define Income(P) (P).Income */
/* #define UpKeep(P) (P).UpKeep */
/* #define ListUnit(P) (P).ListUnit */
/* #define ListBuilding(P) (P).ListBuilding */
/* #define Warna(P) (P).Warna */

void InitPlayer(Player* P, int cash, int income, int upkeep, ListSirkuler units, ListLinier buildings, Color warna) {
  Cash(*P) = income;
  Income(*P) = income;
  UpKeep(*P) = upkeep;
  ListUnit(*P) = units;
  ListBuilding(*P) = buildings;
  Warna(*P) = warna;
}

void MakePlayer(Player* P, Color W, Point Loc) {
  Unit U;
  Building T, CN, CW, CE, CS;

  Cash(*P) = 50;
  Income(*P) = 0;
  UpKeep(*P) = 0;
  //LSCreateEmpty(&ListUnit(*P));
  LLCreateEmpty(&ListBuilding(*P));
  Warna(*P) = W;

  CreateUnit(&U, 'K', Loc);
  LSInsVFirst(&ListUnit(*P), &U);

  MakeBuilding(&T, Loc, 'T');
  MakeBuilding(&CN, PlusDelta(Loc, 0, -1), 'C');
  MakeBuilding(&CS, PlusDelta(Loc, 0,  1), 'C');
  MakeBuilding(&CE, PlusDelta(Loc,  1, 0), 'C');
  MakeBuilding(&CW, PlusDelta(Loc, -1, 0), 'C');
  LLInsVFirst(&ListBuilding(*P), &T);
  LLInsVFirst(&ListBuilding(*P), &CN);
  LLInsVFirst(&ListBuilding(*P), &CS);
  LLInsVFirst(&ListBuilding(*P), &CE);
  LLInsVFirst(&ListBuilding(*P), &CW);
}
