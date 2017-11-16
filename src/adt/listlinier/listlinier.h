/* File : listlinier.h */
/* contoh ADT ListLinier berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "../boolean/boolean.h"
#include "stdlib.h"

#define Nil NULL

typedef void* infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist {
	infotype info;
	address next;
} ElmtList;
typedef struct {
	address First;
} ListLinier;

/* Definisi ListLinier : */
/* ListLinier kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir ListLinier : jika addressnya Last, maka Next(Last)=Nil */
#define LLInfo(P) (P)->info
#define LLNext(P) (P)->next
#define LLFirst(L) ((L).First)

/* PROTOTYPE */
/****************** TEST ListLinier KOSONG ******************/
boolean LLIsEmpty (ListLinier L);
/* Mengirim true jika ListLinier kosong */

/****************** PEMBUATAN ListLinier KOSONG ******************/
void LLCreateEmpty (ListLinier *L);
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinier kosong */

/****************** Manajemen Memori ******************/
address LLAlokasi (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void LLDealokasi (address *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN ListLinier ******************/
address LLSearch (ListLinier L, infotype X);
/* Mencari apakah ada elemen ListLinier dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
boolean LLFSearch (ListLinier L, address P);
/* Mencari apakah ada elemen ListLinier yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
address LLSearchPrec (ListLinier L, infotype X);
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen ListLinier dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN ***/
void LLInsVFirst (ListLinier *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void LLInsVLast (ListLinier *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListLinier di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void LLDelVFirst (ListLinier *L, infotype *X);
/* I.S. ListLinier L tidak kosong  */
/* F.S. Elemen pertama ListLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void LLDelVLast (ListLinier *L, infotype *X);
/* I.S. ListLinier tidak kosong */
/* F.S. Elemen terakhir ListLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void LLInsFirst (ListLinier *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void LLInsAfter (ListLinier *L, address P, address Prec);
/* I.S. Prec pastilah elemen ListLinier dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void LLInsLast (ListLinier *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void LLDelFirst (ListLinier *L, address *P);
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen pertama ListLinier sebelum penghapusan */
/*      Elemen ListLinier berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void LLDelP (ListLinier *L, infotype X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListLinier beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari ListLinier dan di-dealokasi */
/* Jika tidak ada elemen ListLinier dengan info(P)=X, maka ListLinier tetap */
/* ListLinier mungkin menjadi kosong karena penghapusan */
void LLDelLast (ListLinier *L, address *P);
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListLinier sebelum penghapusan  */
/*      Elemen ListLinier berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void LLDelAfter (ListLinier *L, address *Pdel, address Prec);
/* I.S. ListLinier tidak kosong. Prec adalah anggota ListLinier  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen ListLinier yang dihapus  */

int LLNbElmt (ListLinier L);
/* Mengirimkan banyaknya elemen ListLinier; mengirimkan 0 jika ListLinier kosong */

/****************** PROSES TERHADAP ListLinier ******************/
void LLDelAll (ListLinier *L);
/* Delete semua elemen ListLinier dan alamat elemen di-dealokasi */

void LLInverse (ListLinier *L);
/* I.S. sembarang. */
/* F.S. elemen ListLinier dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen ListLinier, tanpa melakukan alokasi/dealokasi. */

ListLinier LLFInverse (ListLinier L);
/* Mengirimkan ListLinier baru, hasil invers dari L */
/* dengan menyalin semua elemn ListLinier. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya ListLinier kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */

ListLinier LLFCopy (ListLinier L);
/* Mengirimkan ListLinier yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya ListLinier kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */

void LLCopy (ListLinier Lin, ListLinier *Lout);
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah ListLinier kosong jika ada alokasi elemen yang gagal */

void LLKonkat (ListLinier L1, ListLinier L2, ListLinier * L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah ListLinier : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */

void LLKonkat1 (ListLinier *L1, ListLinier *L2, ListLinier *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah ListLinier : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen ListLinier L1 dan L2) */
/* dan L1 serta L2 menjadi ListLinier kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

void LLPecahList (ListLinier *L1, ListLinier *L2, ListLinier L);
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah ListLinier L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah LLNbElmt(L) div 2 */

#endif
