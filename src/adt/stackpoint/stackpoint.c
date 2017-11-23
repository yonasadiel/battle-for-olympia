#include "stackpoint.h"
#include "../boolean/boolean.h"
#include "../point/point.h"

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
	*P=(SAddress)malloc(sizeof(ElmtStack));
	if (*P!=Nil)
		{
			Absis(SInfo(*P))=Absis(X);
			Ordinat(SInfo(*P))=Ordinat(X);
			SNext(*P)=Nil;
		}
}

void SDealokasi(SAddress P) {
  free(P);
}

boolean SIsEmpty(Stack S) {
  return(STop(S)==Nil);
}

/* *** Kreator *** */
void SCreateEmpty(Stack* S) {
	STop(*S)=Nil;
}

/* *** Primitif Push/Pop *** */
void SPush(Stack* S, SInfoType X) {
	SAddress P;
	SAlokasi(&P,X);
	if (P!=Nil)
		{
			SNext(P)=STop(*S);
			STop(*S)=P;
		}
}

void SPop(Stack* S, SInfoType* X) {
	SAddress P=STop(*S);
	Absis(*X)=Absis(SInfo(STop(*S)));
	Ordinat(*X)=Ordinat(SInfo(STop(*S)));
	STop(*S)=SNext(P);
	SDealokasi(P);
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
      count++;
    }
    return count;
  }
}

void SPopAll(Stack* S) {
  SInfoType X;

  while (!SIsEmpty(*S)) {
    SPop(S, &X);
  }
}

