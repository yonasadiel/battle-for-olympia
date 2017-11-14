#ifndef BUILDING_H
#define BUILDING_H

#include "../player/player.h"
#include "../point/point.h"

#define GoldPerTurn 10 /* gold yang diberikan village tiap turn */

typedef struct {
	Point Coordinate; /* koordinat building */
	Player Owner;     /* pemilik building */
	char Type;        /* jenis building : [V]illage, [C]astle, [T]ower */
} Building;

/* *** Selektor Building *** */
#define BCoordinate(B) (B).Coordinate
#define BPlayer(B) (B).Player
#define BType(B) (B).Type

Building MakeBuilding(Point C, Player O, char T);
/**
 * Mengembalikan Building yang berada di point
 * C, dimiliki oleh O, dan tipe bangunannya T
 */

#endif
