/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

void START() {
  pita = fopen("save.dat","r");
  ADV();
}

void ADV() {
  retval = fscanf(pita,"%c",&CC);
  EOP = (CC == MARK);
  if (EOP) {
       fclose(pita);
  }
}
