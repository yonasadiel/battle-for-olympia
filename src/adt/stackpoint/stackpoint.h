#ifndef STACK_POINT_H
#define STACK_POINT_H

#include "../boolean/boolean.h"
#include "../point/point.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Deklarasi SInfoType */
typedef Point SInfoType;

/* Stack dengan representasi berkait dengan pointer */
typedef struct TElmtStack* SAddress;
typedef struct TElmtStack {
  SInfoType Info;
  SAddress Next;
} ElmtStack;

/* Type stack dengan ciri TOP : */
typedef struct {
  SAddress Top; /* alamat Top: elemen puncak */
} Stack;

/* Selektor */
#define STop(S) (S).Top
#define SInfoTop(S) (S).Top->Info
#define SNext(P) (P)->Next
#define SInfo(S) (S)->Info

/* Prototype manajemen memori */
void SAlokasi(SAddress* P, SInfoType X);
/**
 * I.S. Sembarang
 * F.S. Alamat P dialokasi, jika berhasil maka SInfo(P)=X
 *      dan Next(P) = Nil
 *      P=Nil jika alokasi gagal
 */
void SDealokasi(SAddress P);
/**
 * I.S. P adalah hasil alokasi, P != Nil
 * F.S. Alamat P didealokasi, dikembalikan ke sistem
 */
boolean SIsEmpty(Stack S);
/**
 * Mengirim true jika S kosong: STop(S) = Nil
 */

/* *** Kreator *** */
void SCreateEmpty(Stack* S);
/**
 * I.S. Sembarang
 * F.S. Membuat sebuah stack S yang kosong
 */

/* *** Primitif Push/Pop *** */
void SPush(Stack* S, SInfoType X);
/**
 * Menambahkan X sebagai elemen Stack S
 * I.S. S mungkin kosong, S terdefinisi
 * F.S. X menjadi Top yang batu jika alokasi C berhasil,
 *      jika tidak, S tetap
 *      Pada dasarnya adalah operasi InsertFirst pada List Linier
 */
void SPop(Stack* S, SInfoType* X);
/**
 * Menghapus X dari Stack S
 * I.S. S tidak mungkin kosong
 * F.S. X adalah nilai elemen Top yang lama
 *      Elemen Top yang lama didealokasi
 * Pada dasarnya adalah operasi DeleteFirst pada list linier
 */

Stack SReverse(Stack S);
/**
  * S mungkin kosong
  * Mengembalikan Stack yang urutannya berkebalikan dengan S
  * Seluruh elemen di alokasi
  */

void PopAll(Stack* S);
/**
 * I.S. S terdefinisi, mungkin kosong
 * F.S. S kosong
 */

#endif