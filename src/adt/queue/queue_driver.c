#include "queue.h"
#include <stdio.h>

void PrintIsiQueue(Queue Q) {
  int* X;

  if (QIsEmpty(Q)) {
    printf("NULL\n");
  } else {
    QAddress P = QHead(Q);
    while (P != QTail(Q)) {
      X = (int*) QInfo(P);
      printf("%d ", *X);
      P = QNext(P);
    }
    X = (int*) QInfo(P);
    printf("%d\n", *X);
  }
}

int main() {
  Queue Q;
  int A,B,C,D,E; int* F;
  QInfoType X;

  A = 5; B = 6; C = 8; D = 2; E = 10;

  QCreateEmpty(&Q);
  QAdd(&Q, &A);  PrintIsiQueue(Q);         /* 5               */
  if (!QIsEmpty(Q)) { printf("Queue tidak kosong\n"); }
  QAdd(&Q, &B);  PrintIsiQueue(Q);         /* 5 6             */
  QAdd(&Q, &C);  PrintIsiQueue(Q);         /* 5 6 8           */
  QAdd(&Q, &D);  PrintIsiQueue(Q);         /* 5 6 8 2         */
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 6 8 2           */ F = (int*) X; printf("Deleted: %d\n", *F);
  QAdd(&Q, &E);  PrintIsiQueue(Q);         /* 6 8 2 10        */
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 8 2 10          */ F = (int*) X; printf("Deleted: %d\n", *F);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 2 10            */ F = (int*) X; printf("Deleted: %d\n", *F);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 10              */ F = (int*) X; printf("Deleted: %d\n", *F);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /*                 */ F = (int*) X; printf("Deleted: %d\n", *F);
  if (QIsEmpty(Q)) { printf("Queue sudah kosong\n"); }
  //printf("%x %x\n", QHead(Q), QTail(Q));

  return 0;
}