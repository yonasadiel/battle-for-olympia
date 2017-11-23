#include "unit.h"
#include "../boolean/boolean.h"
#include "../point/point.h"
#include <stdio.h>

/* typedef struct { */
/*   int MaxHealth;     /* darah unit saat pertama kali direkrut */
/*   int Health;        /* darah yang tersisa */
/*   int Atk;           /* Besar damage yang diterima unit lain yang diserang */
/*   int Heal		    /* Besar pertambahan darah yang diberikan kepada pemain sekutu (kemampuan khusus White Mage) */
/*   int MovPoint;      /* banyak gerakan yang tersisa */
/*   char AtkType;      /* 'm' = melee, 'r' = ranged */
/*   boolean AtkChance; /* true = unit belum menyerang */
/*   Point Location;    /* posisi(baris,kolom) sebuah unit */
/*   int RecCost;       /* harga untuk merekrut unit */
/*   char Type;         /* TipeUnit [K]ing, [A]cher, [S]wordsman, [W]hite mage */
/* } Unit; */

/* *** Selektor Unit *** */
/* #define MaxHealth(U) (U).MaxHealth */
/* #define Health(U) (U).Health */
/* #define Atk(U) (U).Atk */
/* #define Heal(U) (U).Heal */
/* #define MovPoint(U) (U).MovPoint */
/* #define AtkType(U) (U).AtkType */
/* #define AtkChance(U) (U).AtkChance */
/* #define Location(U) (U).Location */
/* #define RecCost(U) (U).RecCost */
/* #define Type(U) (U).Type */
/* #define Location(U) (U).Location */

/* *** Definisi Prototipe Primitif *** */
void CreateUnit (Unit* U, char UnitType, Point P) {
  if (UnitType == 'A') {
    MaxHealth(*U)   = 29;
    Health(*U)      = 29;
    Atk(*U)         = 10;
    Heal(*U)        = 0;
    AtkType(*U)     = 'r';
    RecCost(*U)     = 17;
  } else if (UnitType == 'K') {
    MaxHealth(*U)   = 60;
    Health(*U)      = 60;
    Atk(*U)         = 15;
    Heal(*U)        = 0;
    AtkType(*U)     = 'm';
    RecCost(*U)     = 0;
  } else if (UnitType == 'S') {
    MaxHealth(*U)   = 55;
    Health(*U)      = 55;
    Atk(*U)         = 16;
    Heal(*U)        = 0;
    AtkType(*U)     = 'm';
    RecCost(*U)     = 25;
  } else if (UnitType == 'W') {
    MaxHealth(*U)   = 35;
    Health(*U)      = 35;
    Heal(*U)        = 8;
    Atk(*U)         = 12;
    AtkType(*U)     = 'm';
    RecCost(*U)     = 40;
  }
  AtkChance(*U)   = true;
  MovPoint(*U)    = 0;
  Location(*U)    = P;
  Type(*U) = UnitType;
}

void PrintUnitName(Unit U) {
  if      (Type(U) == 'A') { printf("Archer");     }
  else if (Type(U) == 'K') { printf("King");       }
  else if (Type(U) == 'S') { printf("Swordsman");  }
  else if (Type(U) == 'W') { printf("White Mage"); }
}

void printInfoUnit(Unit U) {
	printf("Unit : ");
	PrintUnitName(U);
	printf(", ");
	printf("Maximum Health : %d, ",MaxHealth(U));
	printf("Health : %d, ",Health(U));
	printf("Heal : %d, ",Heal(U));
	printf("Attack : %d, ",Atk(U));
	printf("Attack Type : %d, ",Atk(U));
	printf("Attack Chance: ");
	if (AtkChance(U)){
		printf("true, ");
	}else{
		printf("false, ");
	}
	printf("Location : ");
	TulisPoint(Location(U));
	printf(", ");
	printf("Recruit Cost : %d, ",RecCost(U));	
}
