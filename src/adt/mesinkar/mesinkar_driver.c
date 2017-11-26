#include "mesinkar.h"
#include <stdio.h>

int main() {
	char a, b, c;
	char k, m, n;

	printf("Masukan karakter: ");
	START(0);
	a = CC;
	CLEAR();
	k = CC;
	printf("Masukan karakter: ");
	START(0);
	b = CC;
	CLEAR();
	m = CC;
	printf("Masukan karakter: ");
	START(0);
	c = CC;
	CLEAR();
	n = CC;
	printf("Karakter yang dimasukan: %d %d %d\n", a, b, c);
	printf("Karakter yang lain: %d %d %d\n", k, m, n);
}