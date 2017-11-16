/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "mesinkata.h"
#include "../boolean/boolean.h"

/* #define NMax 50 */
/* #define BLANK ' ' */

/* typedef struct { */
/*   char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
/*     int Length; */
/* } Kata */

/* State Mesin Kata */
boolean EndKata;
Kata CKata;

void IgnoreBlank() {
  while (CC == BLANK && CC != MARK) {
    ADV();
  }
}

void STARTKATA() {
  START();
  IgnoreBlank();
  if (CC == MARK) {
    EndKata = true;
  } else /* CC != MARK */ {
    EndKata = false;
    SalinKata();
  }
}

void ADVKATA() {
  IgnoreBlank();
  if (CC == MARK) {
    EndKata = true;
  } else /* CC != MARK */ {
    EndKata = false;
    SalinKata();
    IgnoreBlank();
  }
}

void SalinKata() {
  int i = 1;

  for (;;) {
    CKata.TabKata[i] = CC;
    ADV();
    if (CC == BLANK || CC == MARK || i == NMax) {
      break;
    } else {
      i++;
    }
  }

  CKata.Length = i;
}
