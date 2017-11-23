#ifndef UNIT_H
#define UNIT_H

#include "../boolean/boolean.h"
#include "../point/point.h"

typedef struct {
	int MaxHealth;     /* darah unit saat pertama kali direkrut */
	int Health;        /* darah yang tersisa */
	int Atk;           /* Besar damage yang diterima unit lain yang diserang */
	int Heal;	       /* Besar pertambahan darah yang diberikan kepada pemain sekutu (kemampuan khusus White Mage) */
	int MovPoint;      /* banyak gerakan yang tersisa */
	char AtkType;      /* 'm' = melee, 'r' = ranged */
	boolean AtkChance; /* true = unit belum menyerang */
	Point Location;    /* posisi(baris,kolom) sebuah unit */
	int RecCost;       /* harga untuk merekrut unit */
	char Type;         /* TipeUnit [K]ing, [A]cher, [S]wordsman, [W]hite mage */
} Unit;

/* *** Selektor Unit *** */
#define MaxHealth(U) (U).MaxHealth
#define Health(U) (U).Health
#define Atk(U) (U).Atk
#define Heal(U) (U).Heal
#define MovPoint(U) (U).MovPoint
#define AtkType(U) (U).AtkType
#define AtkChance(U) (U).AtkChance
#define Location(U) (U).Location
#define RecCost(U) (U).RecCost
#define Type(U) (U).Type
#define Location(U) (U).Location

/* *** Definisi Prototipe Primitif *** */
void CreateUnit (Unit* U, char UnitType, Point P);
/**
 * I.S. U sembarang, UnitType pasti salah satu dari char 'A','K','S',dan'W'
 * F.S. U terdefinisi berdasar UnitType :'K'=king, 'A'=acher, 'S'=swordsman, 'W'=white mage
 *      mengatur semua kondisi properti dari unit saat pertama kali direkrut
 */

void PrintUnitName(Unit U);
/**
 * I.S. U terdefinisi
 * F.S. tercetak nama U: "King", "Archer", "Swordsman", atau "White Mage"
 */

void printInfoUnit(Unit U);
/**
 * I.S. U terdefinisi
 * F.S. tercetak semua info U: Nama Unit, Maximum Health, Health, ..., Recruit Cost.
 */
 
#endif

















