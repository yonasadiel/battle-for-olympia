/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "mesinkata.h"
#include "../boolean/boolean.h"
#include <stdio.h>

/* #define NMax 50 */
/* #define BLANK ' ' */

/* typedef struct { */
/*   char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
/*     int Length; */
/* } Kata */

/* State Mesin Kata */
boolean EndKata;
Kata CKata;

boolean IsBlank() {
  return (CC == BLANK || CC == 10);
}

void IgnoreBlank() {
  while (IsBlank() && !EOP) {
    ADV();
  }
}

boolean STARTKATA(char* filename) {
  boolean success = START(filename);

  IgnoreBlank();
  if (CC == MARK) {
    EndKata = true;
  } else /* CC != MARK */ {
    EndKata = false;
    SalinKata();
  }

  return success;
}

void ADVKATA() {
  IgnoreBlank();
  if (EOP) {
    EndKata = true;
  } else /* CC != MARK */ {
    EndKata = false;
    SalinKata();
    IgnoreBlank();
  }
}

void SalinKata() {
  int i = 1;

  while(1) {
    CKata.TabKata[i] = CC;
    ADV();
    if (IsBlank() || EOP || i == NMax) { 
      break;
    } else {
      i++;
    }
  }
  CKata.Length = i;
  CKata.TabKata[i+1] = 0;
}

void ToInteger(int* X, boolean* err) {
  int i, j;
  boolean negative;

  *err = false;
  *X = 0;

  negative = false;
  i = 1;
  while(i <= CKata.Length && *err == false) {
    j = CKata.TabKata[i] - 48;
    if(j >= 0 && j <= 9) {
      *X = *X * 10 + j;
      i++;
    } else if(CKata.TabKata[i] == '-') {
      negative = true;
      i++;
    } else {
      printf("ERROR WHEN READING %d\n", CKata.TabKata[i]);
      *err = true;
    }
  }

  if(negative) {
    *X = *X * -1;
  }
}

void CLOSEKATA() {
  CLOSE();
}
