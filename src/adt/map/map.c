#include "map.h"
#include "../color/color.h"
#include "../point/point.h"
#include "../boolean/boolean.h"
#include "../building/building.h"
#include "../unit/unit.h"
#include <stdio.h>

/* Ukuran minimum dan maksimum baris dan kolom */
/* #define MapBrsMin 1 */
/* #define MapBrsMax 15 */
/* #define MapKolMin 1 */
/* #define MapKolMax 45 */

/* typedef struct { */
/*   char Building; */
/*   Color ColorBuilding; */
/*   char Unit; */
/*   Color ColorUnit; */
/* } Sel; */
/* typedef int IdxMap;  indeks baris, kolom */
/* typedef struct { */
/*   Sel Mem[MapBrsMax+1][MapKolMax+1]; */
/*   int NBrsEff;  banyaknya/ukuran baris yg terdefinisi */
/*   int NKolEff;  banyaknya/ukuran kolom yg terdefinisi */
/* } Map; */

/**
 * Definisi Map kosong :
 *   semua Building dan Unit adalah karakter spasi
 *   ColorBuilding dan ColorUnit bernilai sembarang 1-6
 * Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax]
 * Memori matriks yang dipakai selalu di "ujung kiri atas"
 */

/* *** Konstruktor Membentuk Map *** */
void MakeMap(int NB, int NK, Map* M) {
	int i,j;
	
  NBrsEffMap(*M) = NB;
  NKolEffMap(*M) = NK;
  
  for (i = GetMapFirstIdxBrs(*M); i<=GetMapLastIdxBrs(*M); i++) {
		for (j = GetMapFirstIdxKol(*M); j<=GetMapLastIdxKol(*M); j++) {
			Building(*M, i, j) = ' ';
			Unit(*M, i, j) = ' ';
			ColorBuilding(*M, i, j) = CWHITE;
			ColorUnit(*M, i, j) = CWHITE;
		}
	}
}

/* *** Selektor *** */
/* #define NBrsEffMap(M) (M).NBrsEff */
/* #define NKolEffMap(M) (M).NKolEff */
/* #define Building(M,i,j) (M).Mem[(i)][(j)].Building */
/* #define ColorBuilding(M,i,j) (M).Mem[(i)][(j)].ColorBuilding */
/* #define Unit(M,i,j) (M).Mem[(i)][(j)].Unit */
/* #define ColorUnit(M,i,j) (M).Mem[(i)][(j)].ColorUnit */

/* *** Selektor "Dunia Map" *** */
boolean IsIdxValid(IdxMap i, IdxMap j) {
/**
 * Mengembalikan true jika i, j adalah indeks yang valid untuk Map apapun
 */
  return ((i >= MapBrsMin && i <= MapBrsMax) && (j >= MapKolMin && j <= MapKolMax));
}
boolean IsMapSizeValid(int Brs, int Kol) {
/**
 * Mengembalikan true jika i, j adalah indeks yang valid untuk Map apapun
 */
  return (Brs <= MapBrsMax - MapBrsMin && Kol <= MapKolMax - MapKolMin && Brs >= 8 && Kol >= 8);
}

/* *** Selektor: Untuk sebuah Map M yang terdefinisi: *** */
IdxMap GetMapFirstIdxBrs(Map M) {
  return 1;
}

IdxMap GetMapFirstIdxKol(Map M) {
  return 1;
}

IdxMap GetMapLastIdxBrs(Map M) {
  return NBrsEffMap(M);
}

IdxMap GetMapLastIdxKol(Map M) {
  return NKolEffMap(M);
}

boolean IsIdxMapEff(Map M, IdxMap i, IdxMap j) {
  return (i>=1) && (i<=GetMapLastIdxBrs(M)) && (j>=1) && (j<=GetMapLastIdxKol(M));
}

/* *** Kelompok Baca/Tulis *** */
void TulisMap(Map M, Point CurrentUnitLoc) {
  IdxMap i,j;
  
  printf ("      ");
  for (i=1; i<=GetMapLastIdxKol(M); i++) {
		printf ("%d",i-1);
		if (i<10) {
			printf ("   ");
		} else {
			printf ("  ");
		}
  }
  
  printf ("\n    ");
  for (j=1; j<=GetMapLastIdxKol(M)*4+1; j++) {
		printf ("*");
	}
	printf("\n");
	
  for (i=1; i<=GetMapLastIdxBrs(M); i++) {
				
		/* untuk baris 1*/
		printf ("    *");
		for (j = 1; j<=GetMapLastIdxKol(M); j++) {
			printf (" ");
			PrintInColor (Building(M,i,j), ColorBuilding(M,i,j));
			printf (" *");
		}
		printf("\n");
	
	/* untuk baris 2 */
		if (i>=11) {
			printf (" %d *",i-1);
		} else {
			printf ("  %d *",i-1);
		}
		for (j = 1; j<=GetMapLastIdxKol(M); j++) {
			printf (" ");
      if (i == Absis(CurrentUnitLoc) && j == Ordinat(CurrentUnitLoc)) {
			  printf("\033[01;42m"); PrintInColor(Unit(M,i,j), ColorUnit(M,i,j)); printf("\033[0m");
      } else {
        PrintInColor(Unit(M,i,j), ColorUnit(M,i,j));
      }
			printf (" *");
		}
		printf("\n");
		
		/* untuk baris 3
		printf ("    *");
		for (j=1; j<=GetMapLastIdxKol(M); j++) {
			printf ("   *");
		}
		printf("\n"); */

		/* untuk baris 4 */		
		printf ("    *");
		for (j=1; j<=GetMapLastIdxKol(M)*4; j++) {
			printf ("*");
		}
		printf("\n");
	}
}	  
		
/* *** Kelompok Operasi Map *** */
void MapPutUnit(Map* M, Unit U, Color Warna) {
  Unit(*M, Absis(Location(U)), Ordinat(Location(U))) = Type(U);
  ColorUnit(*M, Absis(Location(U)), Ordinat(Location(U))) = Warna;
}

void MapPutBuilding(Map* M, Building B, Color Warna) {
  Building(*M, Absis(BCoordinate(B)), Ordinat(BCoordinate(B))) = BType(B);
  ColorBuilding(*M, Absis(BCoordinate(B)), Ordinat(BCoordinate(B))) = Warna;
}

boolean IsPlayerCastle(Map M, int x, int y, Color Warna) {
	return ((ColorBuilding(M,x,y) == Warna)&&(Building(M,x,y)=='C'));
}

boolean IsLocEmpty(Map M, int x, int y) {
	return (Unit(M, x, y) == ' ');
}

void MCopy(Map M1, Map* M2) {
  MakeMap(NBrsEffMap(M1), NKolEffMap(M1), M2);
  int i,j;
  
  for (i = GetMapFirstIdxBrs(M1); i<=GetMapLastIdxBrs(M1); i++) {
    for (j = GetMapFirstIdxKol(M1); j<=GetMapLastIdxKol(M1); j++) {
      Building(*M2, i, j) = Building(M1, i, j);
      Unit(*M2, i, j) = Unit(M1, i, j);
      ColorBuilding(*M2, i, j) = ColorBuilding(M1, i, j);
      ColorUnit(*M2, i, j) = ColorUnit(M1, i, j);
    }
  }
}