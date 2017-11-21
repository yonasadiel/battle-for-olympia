#ifndef QUEUE_INT_H
#define QUEUE_INT_H

#include "../boolean/boolean.h"

#define Nil NULL

/* deklarasi tipe info */
typedef int QInfoType;

/* Queue dengan representasi berkait dengan pointer */
typedef struct TElmtQueue* QAddress;
typedef struct TElmtQueue {
  QInfoType Info;
  QAddress Next;
} ElmtQueue;

/* Type Queue dengan ciri Head dan Tail */
typedef struct {
  QAddress Head; /* alamat penghapusan */
  QAddress Tail; /* alamat penambahan */
} Queue;

/* Selektor */
#define QHead(Q) (Q).Head
#define QTail(Q) (Q).Tail
#define QInfoHead(Q) (Q).Head->Info
#define QInfoTail(Q) (Q).Tail->Info
#define QNext(P) (P)->Next
#define QInfo(P) (P)->Info

/* Prototype manajemen memori */
void QAlokasi(QAddress* P, QInfoType X);
/**
 * I.S. Sembarang
 * F.S. Alamat P dialokasi, jika berhasil maka QInfo(P)=X
 *      dan Next(P) = Nil
 *      P=Nil jika alokasi gagal
 */
void QDealokasi(QAddress P);
/**
 * I.S. P adalah hasil alokasi, P != Nil
 * F.S. Alamat P didealokasi, dikembalikan ke sistem
 */
boolean QIsEmpty(Queue Q);
/**
 * Mengirim true jika Q kosong: QHead(Q)=Nil dan QTail(Q)=Nil
 */

/* *** Kreator *** */
void QCreateEmpty(Queue* Q);
/**
 * I.S. Sembarang
 * F.S. Sebuah Q kosong terbentuk
 */

/* *** Primitif Add/Delete *** */
void QAdd(Queue* Q, QInfoType X);
/**
 * I.S. Q mungkin kosong
 * F.S. X menjadi Tail, Tail "maju"
 * Proses: Mengalokasi X dan menambahkan X pada bagian Tail
 *         dari Q jika alokasi berhasil; jika alokasi gagaL
 *         Q tetap. Pada dasarnya adalah proses InsertLast
 */
void QDel(Queue* Q, QInfoType* X);
/**
 * I.S. Q tidak mungkin kosong
 * F.S. X = Nilai elemen Head pada I.S., Head "mundur"
 * Proses: Menghapus X pada bagian Head dari Q dan mendealokasi
 *         elemen Head
 */

#endif