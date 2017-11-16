#include "queueint.h"
#include <stdio.h>

void PrintIsiQueue(Queue Q) {
  if (QIsEmpty(Q)) {
    printf("NULL\n");
  } else {
    QAddress P = QHead(Q);
    while (P != QTail(Q)) {
      printf("%d ", QInfo(P));
      P = QNext(P);
    }
    printf("%d\n", QInfo(P));
  }
}

int main() {
  Queue Q;
  QInfoType X;

  QCreateEmpty(&Q);
  QAdd(&Q, 5);   PrintIsiQueue(Q);         /* 5               */
  if (!QIsEmpty(Q)) { printf("Queue tidak kosong\n"); }
  QAdd(&Q, 6);   PrintIsiQueue(Q);         /* 5 6             */
  QAdd(&Q, 8);   PrintIsiQueue(Q);         /* 5 6 8           */
  QAdd(&Q, 2);   PrintIsiQueue(Q);         /* 5 6 8 2         */
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 6 8 2           */ printf("Deleted: %d\n", X);
  QAdd(&Q, 10);  PrintIsiQueue(Q);         /* 6 8 2 10        */
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 8 2 10          */ printf("Deleted: %d\n", X);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 2 10            */ printf("Deleted: %d\n", X);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /* 10              */ printf("Deleted: %d\n", X);
  QDel(&Q, &X);  PrintIsiQueue(Q);         /*                 */ printf("Deleted: %d\n", X);
  if (QIsEmpty(Q)) { printf("Queue sudah kosong\n"); }
  //printf("%x %x\n", QHead(Q), QTail(Q));

  return 0;
}