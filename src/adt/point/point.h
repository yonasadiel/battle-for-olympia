#ifndef POINT_H
#define POINT_H

#include "../boolean/boolean.h"

typedef struct {
  int X; /* absis */
  int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** Definisi Prototipe Primitif *** */
/* *** Konstruktor Membentuk Point *** */
void MakePoint(int X, int Y, Point* P);
/**
 * I.S. P sembarang
 * F.S. Terbentuk sebuah Point dari komponen-komponennya
 */

/* *** Kelompok Interaksi dengan I/O device, *** */
void BacaPoint(Point* P); 
/**
 * Membaca nilai absis dan ordinat dari keyboard dan membentuk
 * Point P berdasarkan dari nilai absis dan ordinat tersebut
 * Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi
 * Contoh: 1 2
 * akan membentuk Point <1,2>
 * I.S. Sembarang
 * F.S. P terdefinisi
 */
void TulisPoint(Point P);
/**
 * Nilai P ditulis ke layar dengan format "(X,Y)"
 * Output X dan Y harus dituliskan dalam bilangan integer.
 * I.S. P terdefinisi
 * F.S. P tertulis di layar dengan format "(X,Y)"
 */

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQPoint(Point P1, Point P2);
/**
 * Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama
 */
boolean NEQPoint(Point P1, Point P2);
/**
 * Mengirimkan true jika P1 tidak sama dengan P2
 */

/* *** Kelompok Operasi Lain Terhadap Point *** */
void Geser(Point *P, int DeltaX, int DeltaY);
/**
 * I.S. P terdefinisi
 * F.S. P digeser, absisnya sebesar DeltaX dan ordinatnya sebesar DeltaY
 */

Point PlusDelta(Point P, int DeltaX, int DeltaY);
/**
 * Prekondisi: P terdefinisi
 * Kembalian: P yang digeser absisnya sebesar DeltaX dan ordinatnya sebesar DeltaY
 */

#endif
