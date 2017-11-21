#include "listsirkuler.h"

/**
 * #define Nil NULL

 * typedef void* infotype;
 * typedef struct tElmtListSirkuler *LSAddress;
 * typedef struct tElmtListSirkuler {
 *   infotype info;
 *   LSAddress next;
 * } ElmtListSirkuler;
 * typedef struct {
 *   LSAddress LSFirst;
 * } ListSirkuler;

/** 
 * Definisi list :
 * ListSirkuler kosong : LSFirst(L) = Nil 
 * Setiap elemen dengan LSAddress P dapat diacu LSInfo(P), LSNext(P) 
 * Elemen terakhir list: jika LSAddressnya Last, maka LSNext(Last)=LSFirst(L)
 */

/**
 * *** Notasi Akses ***
 * #define LSInfo(P) (P)->info
 * #define LSNext(P) (P)->next
 * #define LSFirst(L) ((L).LSFirst)
 */

boolean LSIsEmpty (ListSirkuler L) {
    return (LSFirst(L) == Nil);
}

void LSCreateEmpty (ListSirkuler *L) {
    LSFirst(*L) = Nil;
}

LSAddress LSAlokasi (infotype X) {
    LSAddress p = (LSAddress) malloc(sizeof(LSAddress));
    LSInfo(p) = X;
    LSNext(p) = Nil;
}

void LSDealokasi (LSAddress P) {
    free(P);
}

LSAddress LSSearch (ListSirkuler L, infotype X) {
    LSAddress p = LSFirst(L);
    if(LSInfo(p) == X) {
        return p;
    } else {
        p = LSNext(p);
    }
    while(p != LSFirst(L) && LSInfo(p) != X) {
        p = LSNext(p);
    }
    if(p == LSFirst(L)) {
        return Nil;
    } else {
        return p;
    }
}

void LSInsVFirst (ListSirkuler *L, infotype X) {
    if(LSIsEmpty(*L)) {
        LSAddress p = LSAlokasi(X);
        LSNext(p) = p;
        LSFirst(*L) = p;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        while(LSNext(p) != LSFirst(*L)) {
            p = LSNext(p);
        }
        LSAddress c = LSAlokasi(X);
        LSNext(c) = LSFirst(*L);
        LSNext(p) = c;
        LSFirst(*L) = c;
    }
}

void LSInsVLast (ListSirkuler *L, infotype X) {
    if(LSIsEmpty(*L)) {
        LSAddress p = LSAlokasi(X);
        LSNext(p) = p;
        LSFirst(*L) = p;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        while(LSNext(p) != LSFirst(*L)) {
            p = LSNext(p);
        }
        LSAddress c = LSAlokasi(X);
        LSNext(c) = LSFirst(*L);
        LSNext(p) = c;
    }
}

void LSDelVFirst (ListSirkuler *L, infotype * X) {
    *X = LSInfo(LSFirst(*L));
    if(LSNext(LSFirst(*L)) == LSFirst(*L)) {
        LSDealokasi(LSFirst(*L));
        LSFirst(*L) = Nil;
    } else {
        LSAddress last = LSFirst(*L);
        while(LSNext(last) != LSFirst(*L)) {
            last = LSNext(last);
        }
        LSFirst(*L) = LSNext(LSFirst(*L));
        LSDealokasi(LSNext(last));
        LSNext(last) = LSFirst(*L);
    }
}

void LSDelVLast (ListSirkuler *L, infotype * X) {
    if(LSNext(LSFirst(*L)) == LSFirst(*L)) {
        *X = LSInfo(LSFirst(*L));
        LSDealokasi(LSFirst(*L));
        LSFirst(*L) = Nil;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        LSAddress c = LSFirst(*L);
        while(LSNext(p) != LSFirst(*L)) {
            c = p;
            p = LSNext(p);
        }
        LSNext(c) = LSNext(p);
        *X = LSInfo(p);
        LSDealokasi(p);
    }
}

void LSInsFirst (ListSirkuler *L, LSAddress P) {
    if(LSIsEmpty(*L)) {
        LSFirst(*L) = P;
        LSNext(P) = P;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        while(LSNext(p) != LSFirst(*L)) {
            p = LSNext(p);
        }
        LSNext(P) = LSFirst(*L);
        LSNext(p) = P;
        LSFirst(*L) = P;
    }
}

void LSInsLast (ListSirkuler *L, LSAddress P) {
    if(LSIsEmpty(*L)) {
        LSFirst(*L) = P;
        LSNext(P) = P;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        while(LSNext(p) != LSFirst(*L)) {
            p = LSNext(p);
        }
        LSNext(P) = LSFirst(*L);
        LSNext(p) = P;
    }
}

void LSInsAfter (ListSirkuler *L, LSAddress P, LSAddress Prec) {
    LSNext(P) = LSNext(Prec);
    LSNext(Prec) = P;
}

void LSDelFirst (ListSirkuler *L, LSAddress *P) {
    *P = LSFirst(*L);
    if(LSNext(LSFirst(*L)) == LSFirst(*L)) {
        LSFirst(*L) = Nil;
    } else {
        LSAddress last = LSFirst(*L);
        while(LSNext(last) != LSFirst(*L)) {
            last = LSNext(last);
        }
        LSFirst(*L) = LSNext(LSFirst(*L));
        LSNext(last) = LSFirst(*L);
    }
}

void LSDelLast (ListSirkuler *L, LSAddress *P) {
    if(LSNext(LSFirst(*L)) == LSFirst(*L)) {
        *P = LSFirst(*L);
        LSFirst(*L) = Nil;
    } else {
        LSAddress p = LSNext(LSFirst(*L));
        LSAddress c = LSFirst(*L);
        while(LSNext(p) != LSFirst(*L)) {
            c = p;
            p = LSNext(p);
        }
        LSNext(c) = LSFirst(*L);
        *P = p;
    }
}

void LSDelAfter (ListSirkuler *L, LSAddress *Pdel, LSAddress Prec) {
    if(LSNext(LSFirst(*L)) == LSFirst(*L)) {
        *Pdel = LSFirst(*L);
        LSFirst(*L) = Nil;
    } else {
        LSAddress p = LSFirst(*L);
        while(p != Prec) {
            p = LSNext(p);
        }
        *Pdel = LSNext(p);
        LSNext(p) = LSNext(LSNext(p));
        if(*Pdel == LSFirst(*L)) {
            LSFirst(*L) = LSNext(p);
        }
    }
}

void LSDelP (ListSirkuler *L, infotype X) {
    if (!LSIsEmpty(*L)) {
        if(LSInfo(LSFirst(*L)) == X) {
            infotype x;
            LSDelVFirst(L, &x);
        } else {
            LSAddress p = LSNext(LSFirst(*L));
            LSAddress c = LSFirst(*L);
            while(p != LSFirst(*L) && LSInfo(p) != X) {
                c = p;
                p = LSNext(p);
            }
            if(LSNext(p) == LSFirst(*L)) {
                infotype x;
                LSDelVLast(L, &x);
            } else if(p != LSFirst(*L)) {
                LSNext(c) = LSNext(p);
                LSDealokasi(p);
            }
        }
    }
}