#include "map.h"
#include "../color/color.h"
#include "../point/point.h"
#include "../boolean/boolean.h"

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
/* typedef int IdxMap; /* indeks baris, kolom */
/* typedef struct { */
/*   Sel Mem[MapBrsMax+1][MapKolMax+1]; */
/*   int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
/*   int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
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
  //
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
  //
}

/* *** Selektor: Untuk sebuah Map M yang terdefinisi: *** */
IdxMap GetMapFirstIdxBrs(Map M) {
  //
}

IdxMap GetMapFirstIdxKol(Map M) {
  //
}

IdxMap GetMapLastIdxBrs(Map M) {
  //
}

IdxMap GetMapLastIdxKol(Map M) {
  //
}

boolean IsIdxMapEff(Map M, IdxMap i, IdxMap j) {
  //
}

/* *** Kelompok Baca/Tulis *** */
void TulisMap(Map M) {
  //
}

/* *** Kelompok Operasi Map *** */
void InitMap(Map* M) {
  //
}
