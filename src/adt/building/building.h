#ifndef BUILDING_H
#define BUILDING_H

#include "../player/player.h"
#include "../point/point.h"

typedef struct{
	Point koordinat;
	int maxHP; //maximum HP
	int currHP;	//current HP
	Player owner; //pemilik building
	int gold;
	char type; //jenis petak : normal, village, castle, tower
}Building;

void CreateBuilding(Building *B, char type, Player owner);
/*	Membentuk sebuah building "kosong" yang siap diisi, dengan jenis petak dan pemilik tertentu.
	I.S. Jenis petak dan pemilik building sudah terdefinisi.
	F.S. Building B sesuai dengan definisi di atas terbentuk. */

#endif
