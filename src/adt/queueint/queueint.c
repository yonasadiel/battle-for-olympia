#include "queueint.h"
#include "../boolean/boolean.h"

#define Nil NULL

/* deklarasi tipe info */
/* typedef int QInfoType; */

/* Queue dengan representasi berkait dengan pointer */
/* typedef struct TElmtQueue* QAddress; */
/* typedef struct TElmtQueue { */
/*   QInfoType Info; */
/*   QAddress Next; */
/* } ElmtQueue; */

/* Type Queue dengan ciri Head dan Tail */
/* typedef struct { */
/*   QAddress Head; /* alamat penghapusan */
/*   QAddress Tail; /* alamat penambahan */
/* } Queue; */

/* Selektor */
/* #define QHead(Q) (Q).Head */
/* #define QTail(Q) (Q).Tail */
/* #define QInfoHead(Q) (Q).Head->Info */
/* #define QInfoTail(Q) (Q).Tail->Info */
/* #define QNext(P) (P)->Next */
/* #define QInfo(P) (P)->Info */

/* Prototype manajemen memori */
void QAlokasi(QAddress* P, QInfoType X) {
  //
}

void QDealokasi(QAddress P) {
  //
}

boolean QIsEmpty(Queue Q) {
  //
}

/* *** Kreator *** */
void QCreateEmpty(Queue* Q) {
  //
}

/* *** Primitif Add/Delete *** */
void QAdd(Queue* Q, QInfoType X) {
  //
}

void QDel(Queue* Q, QInfoType X) {
  //
}