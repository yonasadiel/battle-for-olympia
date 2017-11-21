#include "listlinier.h"

/**
 * #define Nil NULL
 *
 * typedef void* infotype;
 * typedef struct tElmtListLinier *LLAddress;
 * typedef struct tElmtListLinier {
 *	 infotype info;
 *	 LLAddress next;
 * } ElmtList;
 * typedef struct {
 * 	 LLAddress First;
 * } ListLinier;

/**
 * Definisi list :
 * ListLinier kosong : First(L) = Nil
 * Setiap elemen dengan LLAddress P dapat diacu Info(P), Next(P)
 * Elemen terakhir list : jika LLAddressnya Last, maka Next(Last)=Nil 
 
 * #define LLInfo(P) (P)->info
 * #define LLNext(P) (P)->next
 * #define LLFirst(L) ((L).First)
 */

boolean LLIsEmpty (ListLinier L) {
    return (LLFirst(L) == Nil);
}

void LLCreateEmpty (ListLinier *L) {
    LLFirst(*L) = Nil;
}

LLAddress LLAlokasi (infotype X) {
    LLAddress p = (LLAddress) malloc(sizeof(LLAddress));
    if(p) {
        LLInfo(p) = X;
        LLNext(p) = Nil;
        return p;
    }

    return Nil;
}

void LLDealokasi (LLAddress *P) {
    free(*P);
}

LLAddress LLSearch (ListLinier L, infotype X) {
    LLAddress p = LLFirst(L);
    while(p != Nil && LLInfo(p) != X) {
        p = LLNext(p);
    }
    return p;
}

boolean LLFSearch (ListLinier L, LLAddress P) {
	LLAddress p = LLFirst(L);
	while(p != Nil && p != P) {
		p = LLNext(p);
	}
	if(p == Nil) {
		return false;
	} else {
		return true;
	}
}

void LLInsVFirst (ListLinier *L, infotype X) {
    LLAddress p = LLAlokasi(X);
    if(p) {
        if(LLIsEmpty(*L)) {
            LLFirst(*L) = p;
        } else {
            LLNext(p) = LLFirst(*L);
            LLFirst(*L) = p;
        }
    }
}

LLAddress LLSearchPrec (ListLinier L, infotype X) {
	LLAddress c = Nil;
	LLAddress p = LLFirst(L);
	while(p != Nil && LLInfo(p) != X) {
		c = p;
		p = LLNext(p);
	}
	if(p == Nil) {
		return Nil;
	} else {
		return c;
	}
}

void LLInsVLast (ListLinier *L, infotype X) {
    LLAddress p = LLAlokasi(X);
    if(p) {
        if(LLIsEmpty(*L)) {
            LLFirst(*L) = p;
        } else {
            LLAddress c = LLFirst(*L);
            while(LLNext(c) != Nil) {
                c = LLNext(c);
            }
            LLNext(c) = p;
        }
    }
}

void LLDelVFirst (ListLinier *L, infotype *X) {
    LLAddress p = LLFirst(*L);
    LLFirst(*L) = LLNext(p);
    *X = LLInfo(p);
    free(p);
}

void LLDelVLast (ListLinier *L, infotype *X) {
    LLAddress prev = Nil;
    LLAddress p = LLFirst(*L);
    while(LLNext(p) != Nil) {
        prev = p;
        p = LLNext(p);
    }
    *X = LLInfo(p);
    if(prev != Nil) {
        LLNext(prev) = Nil;
    } else {
        LLFirst(*L) = Nil;
    }

    LLDealokasi(&p);
}

void LLInsFirst (ListLinier *L, LLAddress P) {
    LLNext(P) = LLFirst(*L);
    LLFirst(*L) = P;
}

void LLInsAfter (ListLinier *L, LLAddress P, LLAddress Prec) {
    LLNext(P) = LLNext(Prec);
    LLNext(Prec) = P;
}

void LLInsLast (ListLinier *L, LLAddress P) {
    if(LLIsEmpty(*L)) {
        LLFirst(*L) = P;
    } else {
        LLAddress c = LLFirst(*L);
        while(LLNext(c) != Nil) {
            c = LLNext(c);
        }
        LLNext(c) = P;
    }
}

void LLDelFirst (ListLinier *L, LLAddress *P) {
    *P = LLFirst(*L);
    LLFirst(*L) = LLNext(LLFirst(*L));
}

void LLDelP (ListLinier *L, infotype X) {
    if(!LLIsEmpty(*L)) {
        if(LLInfo(LLFirst(*L)) == X) {
            LLAddress p = LLFirst(*L);
            LLFirst(*L) = LLNext(LLFirst(*L));
            LLDealokasi(&p);
        } else {
            LLAddress prec = Nil;
            LLAddress p = LLFirst(*L);
            while(LLNext(p) != Nil && LLInfo(LLNext(p)) != X) {
                prec = p;
                p = LLNext(p);
            }
            if(p != Nil && LLNext(p) != Nil) {
                LLAddress c = LLNext(p);
                LLNext(p) = LLNext(c);
                LLDealokasi(&c);
            }
        }
    }
}

void LLDelLast (ListLinier *L, LLAddress *P) {
    if(LLNext(LLFirst(*L)) == Nil) {
        *P = LLFirst(*L);
        LLFirst(*L) = Nil;
    } else {
        LLAddress c = LLFirst(*L);
        while(LLNext(LLNext(c)) != Nil) {
            c = LLNext(c);
        }
        *P = LLNext(c);
        LLNext(c) = Nil;
    }
}

void LLDelAfter (ListLinier *L, LLAddress *Pdel, LLAddress Prec) {
    if(LLNext(Prec) != Nil) {
        *Pdel = LLNext(Prec);
        LLNext(Prec) = LLNext(LLNext(Prec));
    } else {
        *Pdel = Nil;
    }
}

int LLNbElmt (ListLinier L) {
    int counter = 0;
    LLAddress p = LLFirst(L);
    while(p != Nil) {
        counter++;
        p = LLNext(p);
    }
    return counter;
}

void LLDelAll (ListLinier *L) {
	LLAddress p = LLFirst(*L);
	LLAddress c = p;
	while(c != Nil) {
		p = LLNext(p);
		LLDealokasi(&c);
		c = p;
	}
	LLCreateEmpty(L);
}

void LLInverse (ListLinier *L) {
	LLAddress pNext;
	LLAddress p = LLFirst(*L);
	LLAddress pPrev = Nil;
	while(p != Nil) {
		pNext = LLNext(p);
		LLNext(p) = pPrev;
		pPrev = p;
		p = pNext;
	}
	LLFirst(*L) = pPrev;
}

ListLinier LLFInverse (ListLinier L) {
	ListLinier inversed;

	LLCreateEmpty(&inversed);

	LLAddress p = LLFirst(L);
	LLAddress pPrev = Nil;
	LLAddress i;
	LLAddress iPrev = Nil;
	boolean fail = false;

	while(p != Nil && !fail) {
		i = LLAlokasi(LLInfo(p));
		if(i == Nil) {
			fail = true;
		} else {
			LLNext(i) = iPrev;
			iPrev = i;
			pPrev = p;
			p = LLNext(p);
		}
	}

	if(fail) {
		i = iPrev;
		while(i != Nil) {
            iPrev = LLNext(i);
			LLDealokasi(&i);
            i = iPrev;
		}
	} else {
		LLFirst(inversed) = i;
	}

	return inversed;
}

ListLinier LLFCopy (ListLinier L) {
	ListLinier res;

	LLCreateEmpty(&res);

	LLAddress p = LLFirst(L);
	LLAddress i, iPrev, iStart;
	boolean fail;

	if(p == Nil) {
		return res;
	} else {
		iStart = LLAlokasi(LLInfo(p));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			LLFirst(res) = iStart;
		}
	}

    iPrev = iStart;
	p = LLNext(p);
	while(p != Nil && !fail) {
		i = LLAlokasi(LLInfo(p));
		if(i == Nil) {
			fail = true;
		} else {
			LLNext(iPrev) = i;
			iPrev = i;
			p = LLNext(p);
		}
	}

	if(fail) {
		LLDelAll(&res);
	}

	return res;
}

void LLCopy (ListLinier Lin, ListLinier *Lout) {
	LLCreateEmpty(Lout);

	LLAddress p = LLFirst(Lin);
	LLAddress i, iPrev, iStart;
	boolean fail;

	if(p != Nil) {
		iStart = LLAlokasi(LLInfo(p));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			LLFirst(*Lout) = iStart;
		}
	}

	iPrev = iStart;
	p = LLNext(p);
	while(p != Nil && !fail) {
		i = LLAlokasi(LLInfo(p));
		if(i == Nil) {
			fail = true;
		} else {
			LLNext(iPrev) = i;
			iPrev = i;
			p = LLNext(p);
		}
	}

	if(fail) {
		LLDelAll(Lout);
	}
}

void LLKonkat (ListLinier L1, ListLinier L2, ListLinier * L3) {
	ListLinier D1, D2;

	LLAddress p;
	LLAddress i, iPrev, iStart;
	boolean fail, e1, e2;

	LLCreateEmpty(L3);

	e1 = LLIsEmpty(L1);
	e2 = LLIsEmpty(L2);

	if(!e1) {
		iStart = LLAlokasi(LLInfo(LLFirst(L1)));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			LLFirst(*L3) = iStart;
		}
	} else if(!e2) {
		iStart = LLAlokasi(LLInfo(LLFirst(L2)));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			LLFirst(*L3) = iStart;
		}
	} else {
        fail = false;
	}

	if(fail) {
		L3 = Nil;
	} else {
		if(!e1) {
			iPrev = iStart;
			p = LLNext(LLFirst(L1));
			while(p != Nil && !fail) {
				i = LLAlokasi(LLInfo(p));
				if(i == Nil) {
					fail = true;
				} else {
					LLNext(iPrev) = i;
					iPrev = i;
					p = LLNext(p);
				}

			}

			p = LLFirst(L2);
			while(p != Nil && !fail) {
				i = LLAlokasi(LLInfo(p));
				if(i == Nil) {
					fail = true;
				} else {
					LLNext(iPrev) = i;
					iPrev = i;
					p = LLNext(p);
				}
			}
		} else if(!e2) {
			iPrev = iStart;
			p = LLNext(LLFirst(L2));
			while(p != Nil && !fail) {
				i = LLAlokasi(LLInfo(p));
				if(i == Nil) {
					fail = true;
				} else {
					LLNext(iPrev) = i;
					iPrev = i;
					p = LLNext(p);
				}
			}
		}
	}

	if(fail) {
		LLDelAll(L3);
		L3 = Nil;
	}
}

void LLKonkat1 (ListLinier *L1, ListLinier *L2, ListLinier *L3) {
    if(!LLIsEmpty(*L1)) {
        LLFirst(*L3) = LLFirst(*L1);
        LLAddress p = LLFirst(*L1);
        while(LLNext(p) != Nil) {
            p = LLNext(p);
        }
        LLNext(p) = LLFirst(*L2);
    } else if(!LLIsEmpty(*L2)) {
        LLFirst(*L3) = LLFirst(*L2);
    } else {
        LLFirst(*L3) = Nil;
    }

	LLCreateEmpty(L1);
	LLCreateEmpty(L2);
}

void LLPecahListLinier (ListLinier *L1, ListLinier *L2, ListLinier L) {
	LLCreateEmpty(L1);
	LLCreateEmpty(L2);

	if(!LLIsEmpty(L)) {
		LLAddress p = LLFirst(L);
		LLAddress i, iPrev;
		int sizeOne = LLNbElmt(L) / 2;
		int count = 1;

		i = LLAlokasi(LLInfo(p));
		iPrev = i;
		p = LLNext(p);
		LLFirst(*L1) = i;
		while(count < sizeOne) {
			i = LLAlokasi(LLInfo(p));
			LLNext(iPrev) = i;
			iPrev = i;
			p = LLNext(p);
			count++;
		}

		i = LLAlokasi(LLInfo(p));
		iPrev = i;
		LLFirst(*L2) = i;
		p = LLNext(p);
		while(p != Nil) {
			i = LLAlokasi(LLInfo(p));
			LLNext(iPrev) = i;
			iPrev = i;
			p = LLNext(p);
		}
	}
}