/* *********************** ADT UNIT ********************************* */

#ifndef UNIT_H
#define UNIT_H

#include "boolean.h"

typedef struct { 
	int row;
	int col;
} point; /*untuk lokasi unit*/

typedef struct {
	/* Rincian properti yang dapat dimiliki oleh sebuah unit*/
	int MaxHealth; /*darah unit saat pertama kali direkrut*/
	int Health; /*darah yang tersisa*/
	int Atk; /*Besar damage yang diterima unit lain yang diserang*/
	int MaxMovPoint; /*banyak gerakan maksimum unit dalam 1 turn*/
	int MovPoint; /*banyak gerakan yang tersisa*/
	char AtkType; /*'m' = melee, 'r' = ranged*/
	boolean AtkChance; /*true = unit belum menyerang*/
	point Location; /*posisi(baris,kolom) sebuah unit*/
	int RecCost; /*harga untuk merekrut unit*/
	/* Tipe unit*/
	char Type; /*'K'=king, 'A'=acher, 'S'=swordsman, 'W'=white mage*/
} UNIT;

/* ************************ SELEKTOR ******************************** */
#define MaxHealth(U) (U).MaxHealth
#define Health(U) (U).Health
#define Atk(U) (U).Atk
#define MaxMovPoint(U) (U).MaxMovPoint
#define MovPoint(U) (U).MovPoint
#define AtkType(U) (U).AtkType
#define AtkChance(U) (U).AtkChance
#define Location(U) (U).Location
#define RecCost(U) (U).RecCost
#define Type(U) (U).Type
#define Row(P) (P).row
#define Column(P) (P).col

/* ******************** DEFINISI PROTOTIPE PRIMITIF ***************** */
UNIT CreatUnit (char unit_type);
/* Prekondisi: unit_type pasti salah satu dari char 'A','K','S',dan'W' */
/* Membentuk sebuah unit berdasarkan unit_type :'K'=king, 'A'=acher, 'S'=swordsman, 'W'=white mage*/
/* mengembalikan semua kondisi properti dari unit saat pertama kali direkrut */

#endif

















