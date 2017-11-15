#include "building.h"
#include "../player/player.h"
#include "../point/point.h"

/* #define GoldPerTurn 10 /* gold yang diberikan village tiap turn */

/* typedef struct { */
/*   Point Coordinate; /* koordinat building */
/*   Player Owner;     /* pemilik building */
/*   char Type;        /* jenis building : [V]illage, [C]astle, [T]ower */
/* } Building; */

/* *** Selektor Building *** */
/* #define BCoordinate(B) (B).Coordinate */
/* #define BPlayer(B) (B).Owner */
/* #define BType(B) (B).Type */

void MakeBuilding(Building* B,Point C, Player O, char T) {
/**
 * I.S. B sembarang
 * F.S. B terdefinisi di Coordinate C, dimiliki Player O
 *      dan direpresentasikan huruf T
 */
  BCoordinate(*B) = C;
	BPlayer(*B) = O;
	BType(*B) = T;
}
