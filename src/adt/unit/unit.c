/* *********************** ADT UNIT ********************************* */

#include "boolean.h"
#include "unit.h"

/* ******************** DEFINISI PROTOTIPE PRIMITIF ***************** */
UNIT CreatUnit (char unit_type)
/* Prekondisi: unit_type merupakan salah satu dari char 'A','K','S', atau 'W' */
/* Mengembalikan sebuah unit berdasarkan unit_type :'K'=king, 'A'=acher, 'S'=swordsman, 'W'=white mage*/
/* Semua kondisi properti dari unit merupakan kondisi saat pertama kali direkrut */
{
	UNIT U;
	if (unit_type == 'A') {
		MaxHealth(U) = 29;
		Health(U) = 29;
		Atk(U) = 10;
		MaxMovPoint(U) = 2;
		MovPoint(U) = 2;
		AtkType(U) = 'r';
		AtkChance(U) = true;
		/* Location(U) = */
		RecCost(U) = 17;
	} else if (unit_type == 'K') {
		MaxHealth(U) = 60;
		Health(U) = 60;
		Atk(U) = 15;
		MaxMovPoint(U) = 2;
		MovPoint(U) = 2;
		AtkType(U) = 'm';
		AtkChance(U) = true;
		/* Location(U) = */
		RecCost(U) = 0;
	} else if (unit_type == 'S') {
		MaxHealth(U) = 55;
		Health(U) = 55;
		Atk(U) = 16;
		MaxMovPoint(U) = 2;
		MovPoint(U) = 2;
		AtkType(U) = 'm';
		AtkChance(U) = true;
		/* Location(U) = */
		RecCost(U) = 25;
	} else if (unit_type == 'W') {
		MaxHealth(U) = 35;
		Health(U) = 35;
		Atk(U) = 12;
		MaxMovPoint(U) = 2;
		MovPoint(U) = 2;
		AtkType(U) = 'm';
		AtkChance(U) = true;
		/* Location(U) = */
		RecCost(U) = 40;
	}
	Type(U) = unit_type;
	
	return U;
}


