#ifndef LIST_SIRKULER_H
#define LIST_SIRKULER_H

#include "../boolean/boolean.h"
#include <stdlib.h>

#define Nil NULL

typedef void* infotype;
typedef struct tElmtListSirkuler *LSAddress;
typedef struct tElmtListSirkuler {
	infotype info;
	LSAddress next;
} ElmtListSirkuler;
typedef struct {
	LSAddress LSFirst;
} ListSirkuler;

/** 
 * Definisi list :
 * ListSirkuler kosong : LSFirst(L) = Nil 
 * Setiap elemen dengan LSAddress P dapat diacu LSInfo(P), LSNext(P) 
 * Elemen terakhir list: jika LSAddressnya Last, maka LSNext(Last)=LSFirst(L)
 */

/* *** Notasi Akses *** */
#define LSInfo(P) (P)->info
#define LSNext(P) (P)->next
#define LSFirst(L) ((L).LSFirst)

/* *** TEST LIST KOSONG *** */
boolean LSIsEmpty (ListSirkuler L);
/** 
 * Mengirim true jika list kosong, 
 * sesuai definisi list kosong.
 */

/* *** PEMBUATAN LIST KOSONG *** */
void LSCreateEmpty (ListSirkuler *L);
/**
 * I.S. L sembarang
 * F.S. Terbentuk list kosong.. 
 */

/****************** Manajemen Memori ******************/
LSAddress LSAlokasi (infotype X);
/** 
 * Mengirimkan LSAddress hasil alokasi sebuah elemen
 * Jika alokasi berhasil, maka LSAddress tidak nil, dan misalnya
 * menghasilkan P, maka LSInfo(P)=X, LSNext(P)=Nil
 * Jika alokasi gagal, mengirimkan Nil 
 */
void LSDealokasi (LSAddress P);
/** 
 * I.S. P terdefinisi
 * F.S. P dikembalikan ke sistem
 * Melakukan dealokasi/pengembalian LSAddress P 
 */

/* *** PENCARIAN SEBUAH ELEMEN LIST *** */
LSAddress LSSearch (ListSirkuler L, infotype X);
/** 
 * Mencari apakah ada elemen list dengan LSInfo(P)= X
 * Jika ada, mengirimkan LSAddress elemen tersebut.
 * Jika tidak ada, mengirimkan Nil 
 */

/*** PENAMBAHAN ELEMEN ***/
void LSInsVFirst (ListSirkuler *L, infotype X);
/** 
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen pertama dengan nilai X jika alokasi berhasil 
 */

void LSInsVLast (ListSirkuler *L, infotype X);
/** 
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen list di akhir: elemen terakhir yang baru
 * bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. 
 */

/* *** PENGHAPUSAN ELEMEN *** */
void LSDelVFirst (ListSirkuler *L, infotype * X);
/** 
 * I.S. ListSirkuler L tidak kosong 
 * F.S. Elemen pertama list dihapus: nilai info disimpan pada X
 *      dan alamat elemen pertama di-dealokasi 
 */
void LSDelVLast (ListSirkuler *L, infotype * X);
/** 
 * I.S. list tidak kosong
 * F.S. Elemen terakhir list dihapus: nilai info disimpan pada X
 *      dan alamat elemen terakhir di-dealokasi 
 */

/* *** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT *** */
void LSInsFirst (ListSirkuler *L, LSAddress P);
/**
 * I.S. Sembarang, P sudah dialokasi
 * F.S. Menambahkan elemen ber-LSAddress P sebagai elemen pertama 
 */

void LSInsLast (ListSirkuler *L, LSAddress P);
/** 
 * I.S. Sembarang, P sudah dialokasi 
 * F.S. P ditambahkan sebagai elemen terakhir yang baru 
 */

void LSInsAfter (ListSirkuler *L, LSAddress P, LSAddress Prec);
/** 
 * I.S. Prec pastilah elemen list dan bukan elemen terakhir,
 *      P sudah dialokasi 
 * F.S. Insert P sebagai elemen sesudah elemen beralamat Prec 
 */

/* *** PENGHAPUSAN SEBUAH ELEMEN *** */
void LSDelFirst (ListSirkuler *L, LSAddress *P);
/** 
 * I.S. ListSirkuler tidak kosong
 * F.S. P adalah alamat elemen pertama list sebelum penghapusan 
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * LSFirst element yg baru adalah suksesor elemen pertama yang lama 
 */

void LSDelLast (ListSirkuler *L, LSAddress *P);
/** 
 * I.S. ListSirkuler tidak kosong
 * F.S. P adalah alamat elemen terakhir list sebelum penghapusan
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * Last element baru adalah predesesor elemen pertama yg lama,
 * jika ada
 */

void LSDelAfter (ListSirkuler *L, LSAddress *Pdel, LSAddress Prec);
/** 
 * I.S. ListSirkuler tidak kosong. Prec adalah anggota list
 * F.S. Menghapus LSNext(Prec):
 *      Pdel adalah alamat elemen list yang dihapus  
 */

void LSDelP (ListSirkuler *L, infotype X);
/** 
 * I.S. Sembarang
 * F.S. Jika ada elemen list berLSAddress P, dengan LSInfo(P)=X
 * Maka P dihapus dari list dan di-dealokasi
 * Jika tidak ada elemen list dengan LSInfo(P)=X, maka list tetap
 * ListSirkuler mungkin menjadi kosong karena penghapusan 
 */

int LSNbElmt (ListSirkuler L);
/**
 * Prekondisi: L terdefinisi
 * Kembalian : banyaknya elemen di L
 */

LSAddress LSNthAddress (ListSirkuler L, int N);
/**
 * Prekondisi: L terdefinisi dengan panjang <= N
 * Kembalian : Address dari elemen ke N di L
 */

#endif
