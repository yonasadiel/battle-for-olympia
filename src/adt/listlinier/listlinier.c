#include "listlinier.h"

/**
 * #define Nil NULL
 *
 * typedef void* infotype;
 * typedef struct tElmtlist *address;
 * typedef struct tElmtlist {
 *	 infotype info;
 *	 address next;
 * } ElmtList;
 * typedef struct {
 * 	 address First;
 * } List;

/**
 * Definisi list :
 * ListLinear kosong : First(L) = Nil
 * Setiap elemen dengan address P dapat diacu Info(P), Next(P)
 * Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil 
 
 * #define LLInfo(P) (P)->info
 * #define LLNext(P) (P)->next
 * #define LLFirst(L) ((L).First)
 */

boolean LLIsEmpty (ListLinear L) {
    return (LLFirst(L) == Nil);
}

void LLCreateEmpty (ListLinear *L) {
    LLFirst(*L) = Nil;
}

address LLAlokasi (infotype X) {
    address p = (address) malloc(sizeof(address));
    if(p) {
        LLInfo(p) = X;
        LLNext(p) = Nil;
        return p;
    }

    return Nil;
}

void LLDealokasi (address *P) {
    free(*P);
}

address LLSearch (ListLinear L, infotype X) {
    address p = LLFirst(L);
    while(p != Nil && LLInfo(p) != X) {
        p = LLNext(p);
    }
    return p;
}

boolean LLFSearch (ListLinear L, address P) {
	address p = LLFirst(L);
	while(p != Nil && p != P) {
		p = LLNext(p);
	}
	if(p == Nil) {
		return false;
	} else {
		return true;
	}
}

void LLInsVFirst (ListLinear *L, infotype X) {
    address p = LLAlokasi(X);
    if(p) {
        if(LLIsEmpty(*L)) {
            LLFirst(*L) = p;
        } else {
            LLNext(p) = LLFirst(*L);
            LLFirst(*L) = p;
        }
    }
}

address LLSearchPrec (ListLinear L, infotype X) {
	address c = Nil;
	address p = LLFirst(L);
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

void LLInsVLast (ListLinear *L, infotype X) {
    address p = LLAlokasi(X);
    if(p) {
        if(LLIsEmpty(*L)) {
            LLFirst(*L) = p;
        } else {
            address c = LLFirst(*L);
            while(LLNext(c) != Nil) {
                c = LLNext(c);
            }
            LLNext(c) = p;
        }
    }
}

void LLDelVFirst (ListLinear *L, infotype *X) {
    address p = LLFirst(*L);
    LLFirst(*L) = LLNext(p);
    *X = LLInfo(p);
    free(p);
}

void LLDelVLast (ListLinear *L, infotype *X) {
    address prev = Nil;
    address p = LLFirst(*L);
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

void LLInsFirst (ListLinear *L, address P) {
    LLNext(P) = LLFirst(*L);
    LLFirst(*L) = P;
}

void LLInsAfter (ListLinear *L, address P, address Prec) {
    LLNext(P) = LLNext(Prec);
    LLNext(Prec) = P;
}

void LLInsLast (ListLinear *L, address P) {
    if(LLIsEmpty(*L)) {
        LLFirst(*L) = P;
    } else {
        address c = LLFirst(*L);
        while(LLNext(c) != Nil) {
            c = LLNext(c);
        }
        LLNext(c) = P;
    }
}

void LLDelFirst (ListLinear *L, address *P) {
    *P = LLFirst(*L);
    LLFirst(*L) = LLNext(LLFirst(*L));
}

void LLDelP (ListLinear *L, infotype X) {
    if(!LLIsEmpty(*L)) {
        if(LLInfo(LLFirst(*L)) == X) {
            address p = LLFirst(*L);
            LLFirst(*L) = LLNext(LLFirst(*L));
            LLDealokasi(&p);
        } else {
            address prec = Nil;
            address p = LLFirst(*L);
            while(LLNext(p) != Nil && LLInfo(LLNext(p)) != X) {
                prec = p;
                p = LLNext(p);
            }
            if(p != Nil && LLNext(p) != Nil) {
                address c = LLNext(p);
                LLNext(p) = LLNext(c);
                LLDealokasi(&c);
            }
        }
    }
}

void LLDelLast (ListLinear *L, address *P) {
    if(LLNext(LLFirst(*L)) == Nil) {
        *P = LLFirst(*L);
        LLFirst(*L) = Nil;
    } else {
        address c = LLFirst(*L);
        while(LLNext(LLNext(c)) != Nil) {
            c = LLNext(c);
        }
        *P = LLNext(c);
        LLNext(c) = Nil;
    }
}

void LLDelAfter (ListLinear *L, address *Pdel, address Prec) {
    if(LLNext(Prec) != Nil) {
        *Pdel = LLNext(Prec);
        LLNext(Prec) = LLNext(LLNext(Prec));
    } else {
        *Pdel = Nil;
    }
}

int LLNbElmt (ListLinear L) {
    int counter = 0;
    address p = LLFirst(L);
    while(p != Nil) {
        counter++;
        p = LLNext(p);
    }
    return counter;
}

void LLDelAll (ListLinear *L) {
	address p = LLFirst(*L);
	address c = p;
	while(c != Nil) {
		p = LLNext(p);
		LLDealokasi(&c);
		c = p;
	}
	LLCreateEmpty(L);
}

void LLInverse (ListLinear *L) {
	address pNext;
	address p = LLFirst(*L);
	address pPrev = Nil;
	while(p != Nil) {
		pNext = LLNext(p);
		LLNext(p) = pPrev;
		pPrev = p;
		p = pNext;
	}
	LLFirst(*L) = pPrev;
}

ListLinear LLFInverse (ListLinear L) {
	ListLinear inversed;

	LLCreateEmpty(&inversed);

	address p = LLFirst(L);
	address pPrev = Nil;
	address i;
	address iPrev = Nil;
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

ListLinear LLFCopy (ListLinear L) {
	ListLinear res;

	LLCreateEmpty(&res);

	address p = LLFirst(L);
	address i, iPrev, iStart;
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

void LLCopy (ListLinear Lin, ListLinear *Lout) {
	LLCreateEmpty(Lout);

	address p = LLFirst(Lin);
	address i, iPrev, iStart;
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

void LLKonkat (ListLinear L1, ListLinear L2, ListLinear * L3) {
	ListLinear D1, D2;

	address p;
	address i, iPrev, iStart;
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

void LLKonkat1 (ListLinear *L1, ListLinear *L2, ListLinear *L3) {
    if(!LLIsEmpty(*L1)) {
        LLFirst(*L3) = LLFirst(*L1);
        address p = LLFirst(*L1);
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

void LLPecahListLinear (ListLinear *L1, ListLinear *L2, ListLinear L) {
	LLCreateEmpty(L1);
	LLCreateEmpty(L2);

	if(!LLIsEmpty(L)) {
		address p = LLFirst(L);
		address i, iPrev;
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







