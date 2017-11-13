/* File: player.h */
/* ADT untuk merepresentasikan kepemilikan village dan unit dengan list linier dan list sirkuler */
/* Representasi address dengan menggunakan pointer */

#ifndef Player_H
#define Player_H

#include "boolean.h"
#include "building.h"
#include "unit.h"

#define Neul NULL

typedef int color;
typedef building infona;
typedef unit infonya;
typedef struct tEllist *address;

typedef struct tEllist { 
	infona info;
	address next;
} EListbuilding;
typedef struct {
	address Pertama;
} Listbuilding;
/* Definisi list building (list linier) : */
/* List kosong : Pertama(L) = Neul */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Neul */

typedef struct tEllist { 
	infonya info;
	address next;
} EListunit;
typedef struct {
	address Pertama;
} Listunit;
/* Definisi list (list sirkuler) : */
/* List kosong : Pertama(L) = Neul */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list: jika addressnya Last, maka Next(Last)=Pertama(L) */

typedef struct {
	int cash;
	int income;
	int upkeep;
	Listunit listunit;
	Listbuilding listbuilding;
	int movpoint;
	color warna;
} player;

#define Info(P) (P)->info
#define Next(P) (P)->next
#define Pertama(L) ((L).Pertama)

void CreatePlayer(player *Player, color Warna);
//Membuat sebuah variabel player dengan warna tertentu

void AddUnit(player Player, unit Unit);
//Menambahkan sebuah unit pada Listunit player tertentu

/* PROTOTYPE */
/****************** TEST Listbuilding KOSONG ******************/
boolean IsEmpty (Listbuilding L);
/* Mengirim true jika Listbuilding kosong */

/****************** PEMBUATAN Listbuilding KOSONG ******************/
void CreateEmpty (Listbuilding *L);
/* I.S. sembarang             */
/* F.S. Terbentuk Listbuilding kosong */

/****************** Manajemen Memori ******************/
address Alokasi (infona X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak Neul, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Neul */
/* Jika alokasi gagal, mengirimkan Neul */
void Dealokasi (address *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN Listbuilding ******************/
address Search (Listbuilding L, infona X);
/* Mencari apakah ada elemen Listbuilding dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Neul */
boolean FSearch (Listbuilding L, address P);
/* Mencari apakah ada elemen Listbuilding yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
address SearchPrec (Listbuilding L, infona X);
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen Listbuilding dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Neul */
/* Jika P adalah elemen pertama, maka Prec=Neul */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (Listbuilding *L, infona X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (Listbuilding *L, infona X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen Listbuilding di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (Listbuilding *L, infona *X);
/* I.S. Listbuilding L tidak kosong  */
/* F.S. Elemen pertama Listbuilding dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (Listbuilding *L, infona *X);
/* I.S. Listbuilding tidak kosong */
/* F.S. Elemen terakhir Listbuilding dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (Listbuilding *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertAfter (Listbuilding *L, address P, address Prec);
/* I.S. Prec pastilah elemen Listbuilding dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast (Listbuilding *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (Listbuilding *L, address *P);
/* I.S. Listbuilding tidak kosong */
/* F.S. P adalah alamat elemen pertama Listbuilding sebelum penghapusan */
/*      Elemen Listbuilding berkurang satu (mungkin menjadi kosong) */
/* Pertama element yg baru adalah suksesor elemen pertama yang lama */
void DelP (Listbuilding *L, infona X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen Listbuilding beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari Listbuilding dan di-dealokasi */
/* Jika tidak ada elemen Listbuilding dengan info(P)=X, maka Listbuilding tetap */
/* Listbuilding mungkin menjadi kosong karena penghapusan */
void DelLast (Listbuilding *L, address *P);
/* I.S. Listbuilding tidak kosong */
/* F.S. P adalah alamat elemen terakhir Listbuilding sebelum penghapusan  */
/*      Elemen Listbuilding berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (Listbuilding *L, address *Pdel, address Prec);
/* I.S. Listbuilding tidak kosong. Prec adalah anggota Listbuilding  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen Listbuilding yang dihapus  */

/****************** PROSES SEMUA ELEMEN Listbuilding ******************/
void PrintInfo (Listbuilding L);
/* I.S. Listbuilding mungkin kosong */
/* F.S. Jika Listbuilding tidak kosong, iai Listbuilding dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Listbuilding kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmt (Listbuilding L);
/* Mengirimkan banyaknya elemen Listbuilding; mengirimkan 0 jika Listbuilding kosong */

/*** Prekondisi untuk Max/Min/rata-rata : Listbuilding tidak kosong ***/
infona Max (Listbuilding L);
/* Mengirimkan nilai info(P) yang maksimum */
address AdrMax (Listbuilding L);
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
infona Min (Listbuilding L);
/* Mengirimkan nilai info(P) yang minimum */
address AdrMin (Listbuilding L);
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
float Average (Listbuilding L);
/* Mengirimkan nilai rata-rata info(P) */

/****************** PROSES TERHADAP Listbuilding ******************/
void DelAll (Listbuilding *L);
/* Delete semua elemen Listbuilding dan alamat elemen di-dealokasi */

void InversList (Listbuilding *L);
/* I.S. sembarang. */
/* F.S. elemen Listbuilding dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen Listbuilding, tanpa melakukan alokasi/dealokasi. */

Listbuilding FInversList (Listbuilding L);
/* Mengirimkan Listbuilding baru, hasil invers dari L */
/* dengan menyalin semua elemn Listbuilding. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya Listbuilding kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */

void CopyList (Listbuilding *L1, Listbuilding *L2);
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada Listbuilding yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */

Listbuilding FCopyList (Listbuilding L);
/* Mengirimkan Listbuilding yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya Listbuilding kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */

void CpAlokList (Listbuilding Lin, Listbuilding *Lout);
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Neul dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah Listbuilding kosong jika ada alokasi elemen yang gagal */

void Konkat (Listbuilding L1, Listbuilding L2, Listbuilding * L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Neul*/
/* Konkatenasi dua buah Listbuilding : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Neul*/
/* dan semua elemen yang pernah dialokasi didealokasi */

void Konkat1 (Listbuilding *L1, Listbuilding *L2, Listbuilding *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah Listbuilding : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen Listbuilding L1 dan L2) */
/* dan L1 serta L2 menjadi Listbuilding kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

void PecahList (Listbuilding *L1, Listbuilding *L2, Listbuilding L);
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah Listbuilding L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */


/* PROTOTYPE */
/****************** TEST Listunit KOSONG ******************/
boolean IsEmpty (Listunit L);
/* Mengirim true jika Listunit kosong. Lihat definisi di atas. */

/****************** PEMBUATAN Listunit KOSONG ******************/
void CreateEmpty (Listunit *L);
/* I.S. L sembarang             */
/* F.S. Terbentuk Listunit kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
address Alokasi (infonya X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak Neul, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Neul */
/* Jika alokasi gagal, mengirimkan Neul */
void Dealokasi (address P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN Listunit ******************/
address Search (Listunit L, infonya X);
/* Mencari apakah ada elemen Listunit dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Neul */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (Listunit *L, infonya X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (Listunit *L, infonya X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen Listunit di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (Listunit *L, infonya * X);
/* I.S. Listunit L tidak kosong  */
/* F.S. Elemen pertama Listunit dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (Listunit *L, infonya * X);
/* I.S. Listunit tidak kosong */
/* F.S. Elemen terakhir Listunit dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (Listunit *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertLast (Listunit *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertAfter (Listunit *L, address P, address Prec);
/* I.S. Prec pastilah elemen Listunit dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (Listunit *L, address *P);
/* I.S. Listunit tidak kosong */
/* F.S. P adalah alamat elemen pertama Listunit sebelum penghapusan */
/*      Elemen Listunit berkurang satu (mungkin menjadi kosong) */
/* Pertama element yg baru adalah suksesor elemen pertama yang lama */
void DelLast (Listunit *L, address *P);
/* I.S. Listunit tidak kosong */
/* F.S. P adalah alamat elemen terakhir Listunit sebelum penghapusan  */
/*      Elemen Listunit berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfter (Listunit *L, address *Pdel, address Prec);
/* I.S. Listunit tidak kosong. Prec adalah anggota Listunit  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen Listunit yang dihapus  */
void DelP (Listunit *L, infonya X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen Listunit beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari Listunit dan di-dealokasi */
/* Jika tidak ada elemen Listunit dengan Info(P)=X, maka Listunit tetap */
/* Listunit mungkin menjadi kosong karena penghapusan */

/****************** PROSES SEMUA ELEMEN Listunit ******************/
void PrintInfo (Listunit L);
/* I.S. Listunit mungkin kosong */
/* F.S. Jika Listunit tidak kosong, iai Listunit dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Listunit kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

#endif