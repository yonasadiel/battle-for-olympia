#ifndef BUILDING_H
#define BUILDING_H

#include "player.h"

typedef struct{
	int row;
	int col;
}Location;

typedef struct{
	int maxHP; //maximum HP
	int currHP;	//current HP
}HP;

typedef struct{
	Location koordinat;
	HP health;
	Player owner; //pemilik building
	int gold;
	char jpetak; //jenis petak : normal, village, castle, tower
	Player unitp; //unit yang sedang berada di dalam building
}Building;

void CreateBuilding(Building *B, char jpetak, Player owner);
/*	Membentuk sebuah building "kosong" yang siap diisi, dengan jenis petak dan pemilik tertentu.
	I.S. Jenis petak dan pemilik building sudah terdefinisi.
	F.S. Building B sesuai dengan definisi di atas terbentuk. */

#endif
