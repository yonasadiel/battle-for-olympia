#ifndef listlinier_H
#define listlinier_H

#include "../boolean/boolean.h"
#include <stdlib.h>

#define Nil NULL

typedef void* infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
	infotype info;
	address next;
} ElmtListLinear;
typedef struct {
	address First;
} ListLinear;

/**
 * Definisi list :
 * ListLinear kosong : First(L) = Nil
 * Setiap elemen dengan address P dapat diacu Info(P), Next(P)
 * Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil 
 */
#define LLInfo(P) (P)->info
#define LLNext(P) (P)->next
#define LLFirst(L) ((L).First)

/* *** TEST LIST KOSONG *** */
boolean LLIsEmpty (ListLinear L);
/**
 * Mengirim true jika list kosong 
 */

/* *** PEMBUATAN LIST KOSONG *** */
void LLCreateEmpty (ListLinear *L);
/** 
 * I.S. sembarang 
 * F.S. Terbentuk list kosong 
 */

/* *** Manajemen Memori *** */
address LLAlokasi (infotype X);
/** 
 * Mengirimkan address hasil alokasi sebuah elemen
 * Jika alokasi berhasil, maka address tidak nil, dan misalnya
 * menghasilkan P, maka info(P)=X, Next(P)=Nil
 * Jika alokasi gagal, mengirimkan Nil
 */

void LLDealokasi (address *P);
/**
 * I.S. P terdefinisi
 * F.S. P dikembalikan ke sistem 
 * Melakukan dealokasi/pengembalian address P
 */

/* *** PENCARIAN SEBUAH ELEMEN LIST *** */
address LLSearch (ListLinear L, infotype X);
/**
 * Mencari apakah ada elemen list dengan info(P)= X
 * Jika ada, mengirimkan address elemen tersebut.
 * Jika tidak ada, mengirimkan Nil 
 */

boolean LLFSearch (ListLinear L, address P);
/** 
 * Mencari apakah ada elemen list yang beralamat P
 * Mengirimkan true jika ada, false jika tidak ada 
 */

address LLSearchPrec (ListLinear L, infotype X);
/** 
 * Mengirimkan address elemen sebelum elemen yang nilainya=X
 * Mencari apakah ada elemen list dengan Info(P)=X
 * Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X.
 * Jika tidak ada, mengirimkan Nil
 * Jika P adalah elemen pertama, maka Prec=Nil
 * Search dengan spesifikasi seperti ini menghindari
 * traversal ulang jika setelah Search akan dilakukan operasi lain
 */

/* *** PENAMBAHAN ELEMEN *** */
void LLInsVFirst (ListLinear *L, infotype X);
/* 
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen pertama dengan nilai X jika alokasi berhasil 
 */

void LLInsVLast (ListLinear *L, infotype X);
/**
 * I.S. L mungkin kosong
 * F.S. Melakukan alokasi sebuah elemen dan
 * menambahkan elemen list di akhir: elemen terakhir yang baru
 * bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S.
 */

/* *** PENGHAPUSAN ELEMEN *** */
void LLDelVFirst (ListLinear *L, infotype *X);
/** 
 * I.S. ListLinear L tidak kosong 
 * F.S. Elemen pertama list dihapus: nilai info disimpan pada X
 *      dan alamat elemen pertama di-dealokasi
 */
void LLDelVLast (ListLinear *L, infotype *X);
/** 
 * I.S. list tidak kosong
 * F.S. Elemen terakhir list dihapus: nilai info disimpan pada X
 *      dan alamat elemen terakhir di-dealokasi
 */

/* *** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT *** */
void LLInsFirst (ListLinear *L, address P);
/** 
 * I.S. Sembarang, P sudah dialokasi 
 * F.S. Menambahkan elemen ber-address P sebagai elemen pertama 
 */

void LLInsAfter (ListLinear *L, address P, address Prec);
/** 
 * I.S. Prec pastilah elemen list dan bukan elemen terakhir,
 *      P sudah dialokasi
 * F.S. Insert P sebagai elemen sesudah elemen beralamat Prec 
 */

void LLInsLast (ListLinear *L, address P);
/**
 * I.S. Sembarang, P sudah dialokasi
 * F.S. P ditambahkan sebagai elemen terakhir yang baru 
 */

/* *** PENGHAPUSAN SEBUAH ELEMEN *** */
void LLDelFirst (ListLinear *L, address *P);
/** 
 * I.S. ListLinear tidak kosong
 * F.S. P adalah alamat elemen pertama list sebelum penghapusan
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * First element yg baru adalah suksesor elemen pertama yang lama 
 */

void LLDelP (ListLinear *L, infotype X);
/** 
 * I.S. Sembarang
 * F.S. Jika ada elemen list beraddress P, dengan info(P)=X
 * Maka P dihapus dari list dan di-dealokasi
 * Jika tidak ada elemen list dengan info(P)=X, maka list tetap
 * ListLinear mungkin menjadi kosong karena penghapusan 
 */

void LLDelLast (ListLinear *L, address *P);
/** 
 * I.S. ListLinear tidak kosong
 * F.S. P adalah alamat elemen terakhir list sebelum penghapusan
 *      Elemen list berkurang satu (mungkin menjadi kosong)
 * Last element baru adalah predesesor elemen terakhir yg lama,
 * jika ada 
 */

void LLDelAfter (ListLinear *L, address *Pdel, address Prec);
/** 
 * I.S. ListLinear tidak kosong. Prec adalah anggota list
 * F.S. Menghapus Next(Prec):
 *      Pdel adalah alamat elemen list yang dihapus
 */

int LLNbElmt (ListLinear L);
/** 
 * Mengirimkan banyaknya elemen list; 
 * mengirimkan 0 jika list kosong 
 */

/* *** PROSES TERHADAP LIST *** */
void LLDelAll (ListLinear *L);
/* Delete semua elemen list dan alamat
 * elemen di-dealokasi 
 */

void LLInverse (ListLinear *L);
/** 
 * I.S. sembarang.
 * F.S. elemen list dibalik :
 * Elemen terakhir menjadi elemen pertama, dan seterusnya.
 * Membalik elemen list, tanpa melakukan alokasi/dealokasi. 
 */

ListLinear LLFInverse (ListLinear L);
/** 
 * Mengirimkan list baru, hasil invers dari L
 * dengan menyalin semua elemn list. Alokasi mungkin gagal.
 * Jika alokasi gagal, hasilnya list kosong
 * dan semua elemen yang terlanjur di-alokasi, harus didealokasi 
 */

ListLinear LLFCopy (ListLinear L);
/** 
 * Mengirimkan list yang merupakan salinan L
 * dengan melakukan alokasi.
 * Jika ada alokasi gagal, hasilnya list kosong dan
 * semua elemen yang terlanjur di-alokasi, harus didealokasi 
 */

void LLCopy (ListLinear Lin, ListLinear *Lout);
/**
 * I.S. Lin sembarang.
 * F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin
 * Jika ada alokasi yang gagal, 
 * maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi
 * dengan melakukan alokasi elemen.
 * Lout adalah list kosong jika ada alokasi elemen yang gagal
 */

void LLKonkat (ListLinear L1, ListLinear L2, ListLinear * L3);
/** 
 * I.S. L1 dan L2 sembarang
 * F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2
 * Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi
 * Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi
 * harus di-dealokasi dan L3=Nil
 * Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru"
 * Elemen L3 adalah hasil alokasi elemen yang “baru”.
 * Jika ada alokasi yang gagal, maka L3 harus bernilai Nil
 * dan semua elemen yang pernah dialokasi didealokasi 
 */

void LLKonkat1 (ListLinear *L1, ListLinear *L2, ListLinear *L3);
/** 
 * I.S. L1 dan L2 sembarang
 * F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2
 * Konkatenasi dua buah list : L1 dan L2
 * menghasilkan L3 yang baru (dengan elemen list L1 dan L2)
 * dan L1 serta L2 menjadi list kosong.
 * Tidak ada alokasi/dealokasi pada prosedur ini 
 */

void LLPecahList (ListLinear *L1, ListLinear *L2, ListLinear L);
/**
 *  I.S. L mungkin kosong
 * F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2
 * L tidak berubah: untuk membentuk L1 dan L2 harus alokasi
 * L1 berisi separuh elemen L dan L2 berisi sisa elemen L
 * Jika elemen L ganjil, maka separuh adalah LLNbElmt(L) div 2
 */

#endif
