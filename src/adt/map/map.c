#include "map.h"
#include "../color/color.h"
#include "../point/point.h"
#include "../boolean/boolean.h"
#include "../building/building.h"
#include <stdio.h>

/* Ukuran minimum dan maksimum baris dan kolom */
/* #define MapBrsMin 1 */
/* #define MapBrsMax 100 */
/* #define MapKolMin 1 */
/* #define MapKolMax 100 */

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
			Building(*M, i, j) = 'C';
			Unit(*M, i, j) = 'A';
			ColorBuilding(*M, i, j) = CGREEN;
			ColorUnit(*M, i, j) = CRED;
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
void TulisMap(Map M) {
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
			PrintInColor(Unit(M,i,j), ColorUnit(M,i,j));
			printf (" *");
		}
		printf("\n");
		
		/* untuk baris 3 */		
		printf ("    *");
		for (j=1; j<=GetMapLastIdxKol(M); j++) {
			printf ("   *");
		}
		printf("\n");

		/* untuk baris 4 */		
		printf ("    *");
		for (j=1; j<=GetMapLastIdxKol(M)*4; j++) {
			printf ("*");
		}
		printf("\n");
	}
}	  
		
/* *** Kelompok Operasi Map *** */
void InitMap(Map* M) {
  //
}

