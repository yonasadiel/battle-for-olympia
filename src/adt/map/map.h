#ifndef MAP_H
#define MAP_H

#include "../color/color.h"
#include "../point/point.h"
#include "../boolean/boolean.h"
#include "../building/building.h"
#include "../unit/unit.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define MapBrsMin 1
#define MapBrsMax 100
#define MapKolMin 1
#define MapKolMax 100

typedef struct {
  char Building;
  Color ColorBuilding;
  char Unit;
  Color ColorUnit;
} Sel;
typedef int IdxMap; /* indeks baris, kolom */
typedef struct { 
  Sel Mem[MapBrsMax+1][MapKolMax+1];
  int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
  int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Map;

/**
 * Definisi Map kosong :
 *   semua Building dan Unit adalah karakter spasi
 *   ColorBuilding dan ColorUnit bernilai sembarang 1-6
 * Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax]
 * Memori matriks yang dipakai selalu di "ujung kiri atas"
 */

/* *** Konstruktor Membentuk Map *** */
void MakeMap(int NB, int NK, Map* M);
/**
 * Membentuk MAp "kosong" yang siap diisi berukuran NB x NK  di "ujung kiri" memori
 * I.S. M sembarang, NB dan NK valid
 * F.S. Map M sesuai definisi kosong di atas terbentuk
 */

/* *** Selektor *** */
#define NBrsEffMap(M) (M).NBrsEff
#define NKolEffMap(M) (M).NKolEff
#define Building(M,i,j) (M).Mem[(i)][(j)].Building
#define ColorBuilding(M,i,j) (M).Mem[(i)][(j)].ColorBuilding
#define Unit(M,i,j) (M).Mem[(i)][(j)].Unit
#define ColorUnit(M,i,j) (M).Mem[(i)][(j)].ColorUnit

/* *** Selektor "Dunia Map" *** */
boolean IsIdxValid(IdxMap i, IdxMap j);
/**
 * Mengembalikan true jika i, j adalah indeks yang valid untuk Map apapun
 */
boolean IsMapSizeValid(int Brs, int Kol);
/**
 * Mengembalikan true jika i, j adalah indeks yang valid untuk Map apapun
 */

/* *** Selektor: Untuk sebuah Map M yang terdefinisi: *** */
IdxMap GetMapFirstIdxBrs(Map M);
/* Mengembalikan indeks baris terkecil M */
IdxMap GetMapFirstIdxKol(Map M);
/* Mengembalikan indeks kolom terkecil M */
IdxMap GetMapLastIdxBrs(Map M);
/* Mengembalikan indeks baris terbesar M */
IdxMap GetMapLastIdxKol(Map M);
/* Mengembalikan indeks kolom terbesar M */
boolean IsIdxMapEff(Map M, IdxMap i, IdxMap j);
/* Mengembalikan true jika i, j adalah indeks efektif bagi M */

/* *** Kelompok Baca/Tulis *** */
void TulisMap(Map M, Point CurrentUnitLoc);
/**
 * I.S. M terdefinisi
 * F.S. M ditampilkan ke layar sesuai format di spesifikasi
*       Unit yang sedang dipilih akan berwarna hijau
 */

/* *** Kelompok Operasi Map *** */
void InitMap(Map* M);
/**
 * Menyiapkan Map untuk memulai permainan
 * I.S. M kosong
 * F.S. Tower, Castle, Village dan King terassign di Map beserta warnanya
 */

void MapPutUnit(Map* M, Unit U, Color Warna);
/**
 * I.S. M, U, dan Warna terdefinisi
 * F.S. Tertulis unit U di Map dengan warna Warna
 */

void MapPutBuilding(Map* M, Building B, Color Warna);
/**
 * I.S. M, B, dan Warna terdefinisi
 * F.S. Tertulis building B di Map dengan warna Warna
 */

#endif