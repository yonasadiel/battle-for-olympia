#include "listsirkuler.h"
#include <stdio.h>

void PrintIsiList(ListSirkuler L) {
	LSAddress P = LSFirst(L);
	do {
		printf("%d ", *((int*) LSInfo(P)));
		P = LSNext(P);
	} while (P != LSFirst(L));
	printf("\n");
}

int main() {
	int u1, u2, u3, u4, u5, u6;
	int *p1, *p2;

	u1 = 1; u2 = 2; u3 = 3;
	u4 = 4; u5 = 5; u6 = 6;

	ListSirkuler L, L2;
	LSAddress LP;

	LSCreateEmpty(&L);
	if (LSIsEmpty(L)) { printf("List terbuat, kosong\n"); }

	LSInsVFirst(&L, &u1);
	LSInsVFirst(&L, &u2);
	LSInsVLast(&L, &u3);
	LSInsVLast(&L, &u4);

	PrintIsiList(L);

	if (LSSearch(L, &u1)) {
		printf("u1 ditemukan pada alamat %x\n", LSSearch(L, &u1));
	}

	LSDelVFirst(&L,(void**) &p1);
	printf("elemen pertama dihapus dengan nilai %d\n", *(p1));
	LSDelVLast(&L,(void**) &p1);
	printf("elemen terakhir dihapus dengan nilai %d\n", *(p1));

	LP = LSAlokasi(&u5); LSInsFirst(&L, LP);
	LP = LSAlokasi(&u6); LSInsLast(&L, LP);

	printf("saat ini elemen list berjumlah %d\n", LSNbElmt(L));
	PrintIsiList(L);

	p1 = (int*) LSInfo(LSNthAddress(L, 1)); printf("elemen 1 = %d\n", *p1);
	p1 = (int*) LSInfo(LSNthAddress(L, 2)); printf("elemen 2 = %d\n", *p1);

	return 0;
}