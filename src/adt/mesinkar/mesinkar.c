/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

void START(char* filename) {
  pita = fopen(filename,"r");
  ADV();
}

void ADV() {
  retval = fscanf(pita,"%c",&CC);
  EOP = (CC == MARK || retval != 1);
   if (EOP) {
       fclose(pita);
  }
}
