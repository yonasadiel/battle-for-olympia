#include "player.h"
#include "../boolean/boolean.h"
#include "../color/color.h"
#include "../unit/unit.h"
#include "../building/building.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../point/point.h"
#include "../map/map.h"

/* #define Nil NULL */

/* typedef struct { */
/*   int Cash;                 /* jumlah uang yang dimiliki pemain */
/*   int Income;               /* jumlah pendapatan pemain tiap turn */
/*   ListSirkuler ListUnit;    /* list unit yang dimiliki pemain */
/*   ListLinier ListBuilding;  /* list building yang dimiliki pemain */
/*   int MovPoint;             /* movement point yang tersisa */
/*   Color Warna;              /* warna dari player */
/* } Player; */

/* *** Selektor Player *** */
/* #define Cash(P) (P).Cash */
/* #define Income(P) (P).Income */
/* #define UpKeep(P) LSNbElmt(ListUnit(P)) */
/* #define ListUnit(P) (P).ListUnit */
/* #define ListBuilding(P) (P).ListBuilding */
/* #define Warna(P) (P).Warna */

void InitPlayer(Player* P, int cash, int income, ListSirkuler units, ListLinier buildings, Color warna) {
  Cash(*P) = income;
  Income(*P) = income;
  ListUnit(*P) = units;
  ListBuilding(*P) = buildings;
  Warna(*P) = warna;
}

void MakePlayer(Player* P, Color W, Point Loc, Map* M) {
  Unit* U;
  Building *T, *CN, *CW, *CE, *CS;

  Cash(*P) = 51; /* ofset 1 to be reduced after king made */
  Income(*P) = 0;
  LSCreateEmpty(&ListUnit(*P));
  LLCreateEmpty(&ListBuilding(*P));
  Warna(*P) = W;

  U = (Unit*) malloc(1* sizeof(Unit));
  T = (Building*) malloc(1 * sizeof(Building));
  CN = (Building*) malloc(1 * sizeof(Building));
  CW = (Building*) malloc(1 * sizeof(Building));
  CE = (Building*) malloc(1 * sizeof(Building));
  CS = (Building*) malloc(1 * sizeof(Building));

  CreateUnit(U, 'K', Loc);

  MakeBuilding(T, Loc, 'T');
  MakeBuilding(CN, PlusDelta(Loc, 0, -1), 'C');
  MakeBuilding(CS, PlusDelta(Loc, 0,  1), 'C');
  MakeBuilding(CE, PlusDelta(Loc,  1, 0), 'C');
  MakeBuilding(CW, PlusDelta(Loc, -1, 0), 'C');

  LSInsVFirst(&ListUnit(*P), U);
  LLInsVFirst(&ListBuilding(*P), T);
  LLInsVFirst(&ListBuilding(*P), CN);
  LLInsVFirst(&ListBuilding(*P), CS);
  LLInsVFirst(&ListBuilding(*P), CE);
  LLInsVFirst(&ListBuilding(*P), CW);

  MapPutUnit(M, *U, W);
  MapPutBuilding(M, *T, W);
  MapPutBuilding(M, *CN, W);
  MapPutBuilding(M, *CS, W);
  MapPutBuilding(M, *CE, W);
  MapPutBuilding(M, *CW, W);
  
  ResetMovPointAllUnit(P);
}

void ResetMovPointAllUnit(Player* P) {
  LSAddress PU;

  if (!LSIsEmpty(ListUnit(*P))) {
    PU = LSFirst(ListUnit(*P));

    do {
      Unit* U = (Unit*) LSInfo(PU);
      MovPoint(*U) = 2;

      PU = LSNext(PU);
    } while (PU != LSFirst(ListUnit(*P)));
  }
}