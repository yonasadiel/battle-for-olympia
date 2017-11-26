#include "mesinkata.h"
#include <stdio.h>

int main() {
	char s[256], t[256];
	int i, j;
	boolean err;

	printf("Masukan kata: "); 
	STARTKATA(0);
	Salin(s);
	printf("Kata yang diterima %s\n", s);
	printf("Masukan kata lainnyna: ");
	STARTKATA(0);
	Salin(t);
	printf("Kata yang diterima %s\n", t);
	
	printf("Masukan angka: ");
	STARTKATA(0);
	ToInteger(&i, &err);
	printf("Masukan angka: ");
	STARTKATA(0);
	ToInteger(&j, &err);
	printf("Angka yang dimasukan: %d %d \n", i, j);
}