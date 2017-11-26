#ifndef BUILDING_H
#define BUILDING_H

#include "../point/point.h"

#define GoldPerVillage 10 /* gold yang diberikan village tiap turn */

typedef struct {
	Point Coordinate; /* koordinat building */
	char Type;        /* jenis building : [V]illage, [C]astle, [T]ower */
} Building;

/* *** Selektor Building *** */
#define BCoordinate(B) (B).Coordinate
#define BType(B) (B).Type

void MakeBuilding(Building* B, Point C, char T);
/**
 * I.S. B sembarang
 * F.S. B terdefinisi di Coordinate C dan direpresentasikan huruf T
 */

#endif
