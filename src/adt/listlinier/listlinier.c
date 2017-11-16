#include "listlinier.h"

/* Mengirim true jika list kosong */
boolean LLIsEmpty (List L) {
    return (First(L) == Nil);
}

/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void LLCreateEmpty (List *L) {
    First(*L) = Nil;
}

/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
address LLAlokasi (infotype X) {
    address p = (address) malloc(sizeof(address));
    if(p) {
        Info(p) = X;
        Next(p) = Nil;
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

/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
address LLSearch (List L, infotype X) {
    address p = First(L);
    while(p != Nil && Info(p) != X) {
        p = Next(p);
    }
    return p;
}

/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
boolean LLFSearch (List L, address P) {
	address p = First(L);
	while(p != Nil && p != P) {
		p = Next(p);
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
            First(*L) = p;
        } else {
            Next(p) = First(*L);
            First(*L) = p;
        }
    }
}

/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
address LLSearchPrec (List L, infotype X) {
	address c = Nil;
	address p = First(L);
	while(p != Nil && Info(p) != X) {
		c = p;
		p = Next(p);
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
            First(*L) = p;
        } else {
            address c = First(*L);
            while(Next(c) != Nil) {
                c = Next(c);
            }
            Next(c) = p;
        }
    }
}

/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void LLDelVFirst (List *L, infotype *X) {
    address p = First(*L);
    First(*L) = Next(p);
    *X = Info(p);
    free(p);
}

/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
void LLDelVLast (List *L, infotype *X) {
    address prev = Nil;
    address p = First(*L);
    while(Next(p) != Nil) {
        prev = p;
        p = Next(p);
    }
    *X = Info(p);
    if(prev != Nil) {
        Next(prev) = Nil;
    } else {
        First(*L) = Nil;
    }

    LLDealokasi(&p);
}

/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void LLInsFirst (List *L, address P) {
    Next(P) = First(*L);
    First(*L) = P;
}

/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void LLInsAfter (List *L, address P, address Prec) {
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void LLInsLast (List *L, address P) {
    if(LLIsEmpty(*L)) {
        First(*L) = P;
    } else {
        address c = First(*L);
        while(Next(c) != Nil) {
            c = Next(c);
        }
        Next(c) = P;
    }
}

/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void LLDelFirst (List *L, address *P) {
    *P = First(*L);
    First(*L) = Next(First(*L));
}

/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void LLDelP (List *L, infotype X) {
    if(!LLIsEmpty(*L)) {
        if(Info(First(*L)) == X) {
            address p = First(*L);
            First(*L) = Next(First(*L));
            LLDealokasi(&p);
        } else {
            address prec = Nil;
            address p = First(*L);
            while(Next(p) != Nil && Info(Next(p)) != X) {
                prec = p;
                p = Next(p);
            }
            if(p != Nil && Next(p) != Nil) {
                address c = Next(p);
                Next(p) = Next(c);
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
    if(Next(First(*L)) == Nil) {
        *P = First(*L);
        First(*L) = Nil;
    } else {
        address c = First(*L);
        while(Next(Next(c)) != Nil) {
            c = Next(c);
        }
        *P = Next(c);
        Next(c) = Nil;
    }
}

/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
void LLDelAfter (List *L, address *Pdel, address Prec) {
    if(Next(Prec) != Nil) {
        *Pdel = Next(Prec);
        Next(Prec) = Next(Next(Prec));
    } else {
        *Pdel = Nil;
    }
}

/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
int LLNbElmt (List L) {
    int counter = 0;
    address p = First(L);
    while(p != Nil) {
        counter++;
        p = Next(p);
    }
    return counter;
}

/* Delete semua elemen list dan alamat elemen di-dealokasi */
void LLDelAll (List *L) {
	address p = First(*L);
	address c = p;
	while(c != Nil) {
		p = Next(p);
		LLDealokasi(&c);
		c = p;
	}
	LLCreateEmpty(L);
}

/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
void LLInverse (List *L) {
	address pNext;
	address p = First(*L);
	address pPrev = Nil;
	while(p != Nil) {
		pNext = Next(p);
		Next(p) = pPrev;
		pPrev = p;
		p = pNext;
	}
	First(*L) = pPrev;
}

/* Mengirimkan list baru, hasil invers dari L */
List LLFInverse (List L) {
	List inversed;

	LLCreateEmpty(&inversed);

	address p = First(L);
	address pPrev = Nil;
	address i;
	address iPrev = Nil;
	boolean fail = false;

	while(p != Nil && !fail) {
		i = LLAlokasi(Info(p));
		if(i == Nil) {
			fail = true;
		} else {
			Next(i) = iPrev;
			iPrev = i;
			pPrev = p;
			p = Next(p);
		}
	}

	if(fail) {
		i = iPrev;
		while(i != Nil) {
            iPrev = Next(i);
			LLDealokasi(&i);
            i = iPrev;
		}
	} else {
		First(inversed) = i;
	}

	return inversed;
}

/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
List LLFCopy (List L) {
	List res;

	LLCreateEmpty(&res);

	address p = First(L);
	address i, iPrev, iStart;
	boolean fail;

	if(p == Nil) {
		return res;
	} else {
		iStart = LLAlokasi(Info(p));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			First(res) = iStart;
		}
	}

    iPrev = iStart;
	p = Next(p);
	while(p != Nil && !fail) {
		i = LLAlokasi(Info(p));
		if(i == Nil) {
			fail = true;
		} else {
			Next(iPrev) = i;
			iPrev = i;
			p = Next(p);
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

	address p = First(Lin);
	address i, iPrev, iStart;
	boolean fail;

	if(p != Nil) {
		iStart = LLAlokasi(Info(p));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			First(*Lout) = iStart;
		}
	}

	iPrev = iStart;
	p = Next(p);
	while(p != Nil && !fail) {
		i = LLAlokasi(Info(p));
		if(i == Nil) {
			fail = true;
		} else {
			Next(iPrev) = i;
			iPrev = i;
			p = Next(p);
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
		iStart = LLAlokasi(Info(First(L1)));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			First(*L3) = iStart;
		}
	} else if(!e2) {
		iStart = LLAlokasi(Info(First(L2)));
		if(iStart == Nil) {
			fail = true;
		} else {
			fail = false;
			First(*L3) = iStart;
		}
	} else {
        fail = false;
	}

	if(fail) {
		L3 = Nil;
	} else {
		if(!e1) {
			iPrev = iStart;
			p = Next(First(L1));
			while(p != Nil && !fail) {
				i = LLAlokasi(Info(p));
				if(i == Nil) {
					fail = true;
				} else {
					Next(iPrev) = i;
					iPrev = i;
					p = Next(p);
				}

			}

			p = First(L2);
			while(p != Nil && !fail) {
				i = LLAlokasi(Info(p));
				if(i == Nil) {
					fail = true;
				} else {
					Next(iPrev) = i;
					iPrev = i;
					p = Next(p);
				}
			}
		} else if(!e2) {
			iPrev = iStart;
			p = Next(First(L2));
			while(p != Nil && !fail) {
				i = LLAlokasi(Info(p));
				if(i == Nil) {
					fail = true;
				} else {
					Next(iPrev) = i;
					iPrev = i;
					p = Next(p);
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
        First(*L3) = First(*L1);
        address p = First(*L1);
        while(Next(p) != Nil) {
            p = Next(p);
        }
        Next(p) = First(*L2);
    } else if(!LLIsEmpty(*L2)) {
        First(*L3) = First(*L2);
    } else {
        First(*L3) = Nil;
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
		address p = First(L);
		address i, iPrev;
		int sizeOne = LLNbElmt(L) / 2;
		int count = 1;

		i = LLAlokasi(Info(p));
		iPrev = i;
		p = Next(p);
		First(*L1) = i;
		while(count < sizeOne) {
			i = LLAlokasi(Info(p));
			Next(iPrev) = i;
			iPrev = i;
			p = Next(p);
			count++;
		}

		i = LLAlokasi(Info(p));
		iPrev = i;
		First(*L2) = i;
		p = Next(p);
		while(p != Nil) {
			i = LLAlokasi(Info(p));
			Next(iPrev) = i;
			iPrev = i;
			p = Next(p);
		}
	}
}







