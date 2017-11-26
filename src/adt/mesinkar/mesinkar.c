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
  EOP = (CC == MARK || CC == 10 || CC == 0 || retval != 1);
  if (EOP) {
    if(pita != stdin) {
      fclose(pita);
    }
  }
}

void CLOSE() {
	fclose(pita);
}

void CLEAR() {
  while(CC != 10) {
     fscanf(pita, "%c", &CC);   
  }
}
