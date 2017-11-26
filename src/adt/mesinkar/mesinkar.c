/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

boolean START(char* filename) {
  if(filename != 0) {
    pita = fopen(filename,"r");
  } else {
    pita = stdin;
  }
  ADV();
  if(pita) {
  	return true;
  } else {
  	return false; 
  }
}

void ADV() {
  retval = fscanf(pita,"%c",&CC);
  EOP = (CC == MARK || retval != 1);
  if (EOP) {
       fclose(pita);
  }
}

void CLOSE() {
	fclose(pita);
}
