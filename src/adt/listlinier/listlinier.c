#include "listlinier.h"
#include "stdlib.h"

/* Mengirim true jika list kosong */
boolean LLIsEmpty (List L) {
    return (LLFirst(L) == Nil);
}

/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void LLCreateEmpty (List *L) {
    LLFirst(*L) = Nil;
}

/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka LLInfo(P)=X, LLNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
address LLAlokasi (infotype X) {
    address p = (address) malloc(sizeof(address));
    if(p) {
        LLInfo(p) = X;
        LLNext(p) = Nil;
        return p;
    }

    return Nil;
}

/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
void LLDealokasi (address *P) {
    free(*P);
}

/* Mencari apakah ada elemen list dengan LLInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
address LLSearch (List L, infotype X) {
    address p = LLFirst(L);
    while(p != Nil && LLInfo(p) != X) {
        p = LLNext(p);
    }
    return p;
}

/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
boolean LLFSearch (List L, address P) {
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

/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void LLInsVFirst (List *L, infotype X) {
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

/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
address LLSearchPrec (List L, infotype X) {
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

/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
void LLInsVLast (List *L, infotype X) {
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

/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void LLDelVFirst (List *L, infotype *X) {
    address p = LLFirst(*L);
    LLFirst(*L) = LLNext(p);
    *X = LLInfo(p);
    free(p);
}

/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
void LLDelVLast (List *L, infotype *X) {
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

/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void LLInsFirst (List *L, address P) {
    LLNext(P) = LLFirst(*L);
    LLFirst(*L) = P;
}

/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void LLInsAfter (List *L, address P, address Prec) {
    LLNext(P) = LLNext(Prec);
    LLNext(Prec) = P;
}

/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void LLInsLast (List *L, address P) {
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

/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void LLDelFirst (List *L, address *P) {
    *P = LLFirst(*L);
    LLFirst(*L) = LLNext(LLFirst(*L));
}

/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan LLInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan LLInfo(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void LLDelP (List *L, infotype X) {
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

/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void LLDelLast (List *L, address *P) {
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

/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus LLNext(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
void LLDelAfter (List *L, address *Pdel, address Prec) {
    if(LLNext(Prec) != Nil) {
        *Pdel = LLNext(Prec);
        LLNext(Prec) = LLNext(LLNext(Prec));
    } else {
        *Pdel = Nil;
    }
}

/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
int LLNbElmt (List L) {
    int counter = 0;
    address p = LLFirst(L);
    while(p != Nil) {
        counter++;
        p = LLNext(p);
    }
    return counter;
}

/* Delete semua elemen list dan alamat elemen di-dealokasi */
void LLDelAll (List *L) {
	address p = LLFirst(*L);
	address c = p;
	while(c != Nil) {
		p = LLNext(p);
		LLDealokasi(&c);
		c = p;
	}
	LLCreateEmpty(L);
}

/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
void LLInverse (List *L) {
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

/* Mengirimkan list baru, hasil invers dari L */
List LLFInverse (List L) {
	List inversed;

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

/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
List LLFCopy (List L) {
	List res;

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

/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
void LLCopy (List Lin, List *Lout) {
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

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
void LLKonkat (List L1, List L2, List * L3) {
	List D1, D2;

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

/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* LLKonkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
void LLKonkat1 (List *L1, List *L2, List *L3) {
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

/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
void LLPecahList (List *L1, List *L2, List L) {
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







