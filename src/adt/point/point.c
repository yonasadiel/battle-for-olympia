#include "point.h"
#include "../boolean/boolean.h"
#include <stdio.h>

/* typedef struct { */
/*   int X; /* absis */
/*   int Y; /* ordinat */
/* } Point; */

/* *** Notasi Akses: Selektor Point *** */
/* #define Absis(P) (P).X */
/* #define Ordinat(P) (P).Y */

/* *** Definisi Prototipe Primitif *** */
/* *** Konstruktor Membentuk Point *** */
void MakePoint(int X, int Y, Point* P) {
/* Membentuk sebuah Point dari komponen-komponennya */
  Absis(*P) = X;
  Ordinat(*P) = Y;
}

/* *** Kelompok Interaksi dengan I/O device, *** */
void BacaPoint(Point* P) {
	int x,y;
	printf("Masukkan nilai x dan y:");
	scanf("%d",&x);
	scanf(" %d",&y);
	MakePoint(x,y,P);
}

void TulisPoint(Point P) {
	printf("(%d,%d)\n",Absis(P),Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQPoint(Point P1, Point P2) {
  //
}

boolean NEQPoint(Point P1, Point P2) {
  //
}

/* *** Kelompok Operasi Lain Terhadap Point *** */
void Geser (Point *P, int DeltaX, int DeltaY) {
	Absis(*P)+=DeltaX;
	Ordinat(*P)+=DeltaY;
}
