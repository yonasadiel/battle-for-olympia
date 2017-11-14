#include "unit.h"
#include "../boolean/boolean.h"
#include "../point/point.h"

/* typedef struct { */
/*   int MaxHealth;     /* darah unit saat pertama kali direkrut */
/*   int Health;        /* darah yang tersisa */
/*   int Atk;           /* Besar damage yang diterima unit lain yang diserang */
/*   int MaxMovPoint;   /* banyak gerakan maksimum unit dalam 1 turn */
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
/* #define MaxMovPoint(U) (U).MaxMovPoint */
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
    MaxMovPoint(*U) = 2;
    MovPoint(*U)    = 2;
    AtkType(*U)     = 'r';
    AtkChance(*U)   = true;
    RecCost(*U)     = 17;
  } else if (UnitType == 'K') {
    MaxHealth(*U)   = 60;
    Health(*U)      = 60;
    Atk(*U)         = 15;
    MaxMovPoint(*U) = 2;
    MovPoint(*U)    = 2;
    AtkType(*U)     = 'm';
    AtkChance(*U)   = true;
    RecCost(*U)     = 0;
  } else if (UnitType == 'S') {
    MaxHealth(*U)   = 55;
    Health(*U)      = 55;
    Atk(*U)         = 16;
    MaxMovPoint(*U) = 2;
    MovPoint(*U)    = 2;
    AtkType(*U)     = 'm';
    AtkChance(*U)   = true;
    RecCost(*U)     = 25;
  } else if (UnitType == 'W') {
    MaxHealth(*U)   = 35;
    Health(*U)      = 35;
    Atk(*U)         = 12;
    MaxMovPoint(*U) = 2;
    MovPoint(*U)    = 2;
    AtkType(*U)     = 'm';
    AtkChance(*U)   = true;
    RecCost(*U)     = 40;
  }
  Location(*U)    = P;
  Type(*U) = UnitType;
}
