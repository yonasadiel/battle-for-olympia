#include "listlinier.h"
#include "stdlib.h"

/* Mengirim true jika ListLinier kosong */
boolean LLIsEmpty (ListLinier L) {
    return (LLFirst(L) == Nil);
}

/* I.S. sembarang             */
/* F.S. Terbentuk ListLinier kosong */
void LLCreateEmpty (ListLinier *L) {
    LLFirst(*L) = Nil;
}

/* Mengirimkan address hasil alokasi sebuah elemen *h/
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

/* Mencari apakah ada elemen ListLinier dengan LLInfo(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
address LLSearch (ListLinier L, infotype X) {
    address p = LLFirst(L);
    while(p != Nil && LLInfo(p) != X) {
        p = LLNext(p);
    }
    return p;
}

/* Mencari apakah ada elemen ListLinier yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
boolean LLFSearch (ListLinier L, address P) {
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
void LLInsVFirst (ListLinier *L, infotype X) {
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
address LLSearchPrec (ListLinier L, infotype X) {
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
/* menambahkan elemen ListLinier di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
void LLInsVLast (ListLinier *L, infotype X) {
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

/* I.S. ListLinier L tidak kosong  */
/* F.S. Elemen pertama ListLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void LLDelVFirst (ListLinier *L, infotype *X) {
    address p = LLFirst(*L);
    LLFirst(*L) = LLNext(p);
    *X = LLInfo(p);
    free(p);
}

/* I.S. ListLinier tidak kosong */
/* F.S. Elemen terakhir ListLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
void LLDelVLast (ListLinier *L, infotype *X) {
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
void LLInsFirst (ListLinier *L, address P) {
    LLNext(P) = LLFirst(*L);
    LLFirst(*L) = P;
}

/* I.S. Prec pastilah elemen ListLinier dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void LLInsAfter (ListLinier *L, address P, address Prec) {
    LLNext(P) = LLNext(Prec);
    LLNext(Prec) = P;
}

/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void LLInsLast (ListLinier *L, address P) {
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

/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen pertama ListLinier sebelum penghapusan */
/*      Elemen ListLinier berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void LLDelFirst (ListLinier *L, address *P) {
    *P = LLFirst(*L);
    LLFirst(*L) = LLNext(LLFirst(*L));
}

/* I.S. Sembarang */
/* F.S. Jika ada elemen ListLinier beraddress P, dengan LLInfo(P)=X  */
/* Maka P dihapus dari ListLinier dan di-dealokasi */
/* Jika tidak ada elemen ListLinier dengan LLInfo(P)=X, maka ListLinier tetap */
/* ListLinier mungkin menjadi kosong karena penghapusan */
void LLDelP (ListLinier *L, infotype X) {
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

/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListLinier sebelum penghapusan  */
/*      Elemen ListLinier berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void LLDelLast (ListLinier *L, address *P) {
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

/* I.S. ListLinier tidak kosong. Prec adalah anggota ListLinier  */
/* F.S. Menghapus LLNext(Prec): */
/*      Pdel adalah alamat elemen ListLinier yang dihapus  */
void LLDelAfter (ListLinier *L, address *Pdel, address Prec) {
    if(LLNext(Prec) != Nil) {
        *Pdel = LLNext(Prec);
        LLNext(Prec) = LLNext(LLNext(Prec));
    } else {
        *Pdel = Nil;
    }
}

/* Mengirimkan banyaknya elemen ListLinier; mengirimkan 0 jika ListLinier kosong */
int LLNbElmt (ListLinier L) {
    int counter = 0;
    address p = LLFirst(L);
    while(p != Nil) {
        counter++;
        p = LLNext(p);
    }
    return counter;
}

/* Delete semua elemen ListLinier dan alamat elemen di-dealokasi */
void LLDelAll (ListLinier *L) {
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
/* F.S. elemen ListLinier dibalik : */
void LLInverse (ListLinier *L) {
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

/* Mengirimkan ListLinier baru, hasil invers dari L */
ListLinier LLFInverse (ListLinier L) {
	ListLinier inversed;

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

/* Mengirimkan ListLinier yang merupakan salinan L */
/* dengan melakukan alokasi. */
ListLinier LLFCopy (ListLinier L) {
	ListLinier res;

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
/* Lout adalah ListLinier kosong jika ada alokasi elemen yang gagal */
void LLCopy (ListLinier Lin, ListLinier *Lout) {
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
void LLKonkat (ListLinier L1, ListLinier L2, ListLinier * L3) {
	ListLinier D1, D2;

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
/* LLKonkatenasi dua buah ListLinier : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen ListLinier L1 dan L2) */
/* dan L1 serta L2 menjadi ListLinier kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
void LLKonkat1 (ListLinier *L1, ListLinier *L2, ListLinier *L3) {
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
/* F.S. Berdasarkan L, dibentuk dua buah ListLinier L1 dan L2 */
void LLPecahList (ListLinier *L1, ListLinier *L2, ListLinier L) {
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







