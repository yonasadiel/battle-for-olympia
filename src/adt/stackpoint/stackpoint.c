#include "stackpoint.h"
#include "../boolean/boolean.h"
#include "../point/point.h"
#include <stdio.h>

/* Konstanta */
/* #define Nil NULL

/* Deklarasi SInfoType */
/* typedef Point SInfoType; */

/* Stack dengan representasi berkait dengan pointer */
/* typedef struct TElmtStack* SAddress; */
/* typedef struct TElmtStack { */
/*   SInfoType Info; */
/*   SAddress Next; */
/* } ElmtStack; */

/* Type stack dengan ciri TOP : */
/* typedef struct { */
/*   SAddress Top; /* alamat Top: elemen puncak */
/* } Stack; */

/* Selektor */
/* #define STop(S) (S).Top */
/* #define SInfoTop(S) (S).Top->Info */
/* #define SNext(P) (P)->Next */
/* #define SInfo(S) (S)->Info */

/* Prototype manajemen memori */
void SAlokasi(SAddress* P, SInfoType X) {
  //
}

void SDealokasi(SAddress P) {
  //
}

boolean SIsEmpty(Stack S) {
  //
}

/* *** Kreator *** */
void SCreateEmpty(Stack* S) {
  //
}

/* *** Primitif Push/Pop *** */
void SPush(Stack* S, SInfoType X) {
  //
}

void SPop(Stack* S, SInfoType X) {
  //
}

Stack SReverse(Stack S) {
  Stack R;
  SCreateEmpty(&R);
  if(!SIsEmpty(S)) {
    SAddress addr;
    addr = STop(S);
    while(addr != Nil) {
      SPush(&R, SInfo(addr));
      addr = SNext(addr);
    }
  }
  return R;
}

int SNbElmt(Stack S) {
  if(SIsEmpty(S)) {
    return 0;
  } else {
    SAddress p = STop(S);
    int count = 0;
    while(p != Nil) {
      p = SNext(p);
      printf("%d\n", count);
      count++;
    }
    return count;
  }
}