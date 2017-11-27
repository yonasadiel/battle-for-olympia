#include "mesinkata.h"
#include <stdio.h>

int main() {
	char s[256];
	int i, j;
	boolean err;
	char fname[10];

	printf("Masukan angka: ");
	STARTKATA(0);
	ToInteger(&i, &err);
	printf("Masukan angka: ");
	STARTKATA(0);
	ToInteger(&j, &err);
	printf("Angka yang dimasukan: %d %d \n", i, j);
	
	printf("Masukkan nama file:");
	scanf("%s",fname);
	STARTKATA(fname);
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	ADVKATA();
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	ADVKATA();
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	ADVKATA();
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	ADVKATA();
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	ADVKATA();
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	CLOSEKATA();
	
	return 0;
}