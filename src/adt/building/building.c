#include "building.h"
#include "../point/point.h"

/* #define GoldPerVillage 10 /* gold yang diberikan village tiap turn */

/* typedef struct { */
/*   Point Coordinate; /* koordinat building */
/*   char Type;        /* jenis building : [V]illage, [C]astle, [T]ower */
/* } Building; */

/* *** Selektor Building *** */
/* #define BCoordinate(B) (B).Coordinate */
/* #define BType(B) (B).Type */

void MakeBuilding(Building* B, Point C, char T) {
  BCoordinate(*B) = C;
	BType(*B) = T;
}
