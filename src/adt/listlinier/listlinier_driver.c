#include "listlinier.h"
#include <stdio.h>

void PrintIsiList(ListLinier L) {
	LLAddress P = LLFirst(L);
	while (P != Nil) {
		printf("%d ", *((int*) LLInfo(P)));
		P = LLNext(P);
	} printf("\n");
}

int main() {
	int u1, u2, u3, u4, u5, u6;
	int *p1, *p2;

	u1 = 1; u2 = 2; u3 = 3;
	u4 = 4; u5 = 5; u6 = 6;

	ListLinier L, L2;
	LLAddress LP;

	LLCreateEmpty(&L);
	if (LLIsEmpty(L)) { printf("List terbuat, kosong\n"); }

	LLInsVFirst(&L, &u1);
	LLInsVFirst(&L, &u2);
	LLInsVLast(&L, &u3);
	LLInsVLast(&L, &u4);

	PrintIsiList(L);

	if (LLFSearch(L, LLSearch(L, &u1))) {
		printf("u1 ditemukan pada alamat %x\n", LLSearch(L, &u1));
		printf("elemen sebelumnya adalah %d\n", *((int*) LLInfo(LLSearchPrec(L, &u1))));
	}

	LLDelVFirst(&L,(void**) &p1);
	printf("elemen pertama dihapus dengan nilai %d\n", *(p1));
	LLDelVLast(&L,(void**) &p1);
	printf("elemen terakhir dihapus dengan nilai %d\n", *(p1));

	LP = LLAlokasi(&u5); LLInsFirst(&L, LP);
	LP = LLAlokasi(&u6); LLInsLast(&L, LP);

	printf("saat ini elemen list berjumlah %d\n", LLNbElmt(L));
	PrintIsiList(L);

	LLInverse(&L);
	printf("Setelah dibalik:\n");
	PrintIsiList(L);

	p1 = (int*) LLInfo(LLNthAddress(L, 1)); printf("elemen 1 = %d\n", *p1);
	p1 = (int*) LLInfo(LLNthAddress(L, 2)); printf("elemen 2 = %d\n", *p1);

	LLCopy(L, &L2);
	LLDelAll(&L);

	printf("Hasil Copy:\n");
	PrintIsiList(L2);

	return 0;
}