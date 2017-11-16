#include "queueint.h"
#include "../boolean/boolean.h"
#include <stdlib.h>

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
  *P = (QAddress) malloc(1 * sizeof(ElmtQueue));
  if (*P != Nil) {
    QInfo(*P) = X;
    QNext(*P) = Nil;
  }
}

void QDealokasi(QAddress P) {
  free(P);
}

boolean QIsEmpty(Queue Q) {
  return QHead(Q)==Nil && QTail(Q)==Nil;
}

/* *** Kreator *** */
void QCreateEmpty(Queue* Q) {
  QHead(*Q) = Nil;
  QTail(*Q) = Nil;
}

/* *** Primitif Add/Delete *** */
void QAdd(Queue* Q, QInfoType X) {
  QAddress P;

  QAlokasi(&P, X);
  if (P != Nil) {
    if (!QIsEmpty(*Q)) {
      QNext(QTail(*Q)) = P;
    } else /* L kosong */ {
      QHead(*Q) = P;
    }
    QTail(*Q) = P;
  } /* else : alokasi gagal, Q tetap */
}

void QDel(Queue* Q, QInfoType* X) {
  QAddress P;

  *X = QInfoHead(*Q);
  P = QHead(*Q);
  QHead(*Q) = QNext(QHead(*Q));
  if (QHead(*Q) == Nil) { /* L hanya 1 elemen */
    QTail(*Q) = Nil;
  }
  QDealokasi(P);
}