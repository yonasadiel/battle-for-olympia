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

void MakePlayer(Player* P, Color W, Point Loc) {
  Unit U;
  Building B;

  Cash(*P) = 50;
  Income(*P) = 0;
  UpKeep(*P) = 0;
  //LSCreateEmpty(&ListUnit(*P));
  LLCreateEmpty(&ListBuilding(*P));
  Warna(*P) = W;

  CreateUnit(&U, 'K', Loc);
  // TODO : create all unit and building

}
