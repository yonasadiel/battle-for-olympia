#include "mesinkar.h"
#include <stdio.h>

int main() {
	char a, b, c;
	char k, m, n;
	char fname[64];
	scanf("%s",fname);
	START(fname);
	a=CC;
	printf("%c\n",a);
	ADV();
	b=CC;
	printf("%c\n",b);
	ADV();
	c=CC;
	printf("%c\n",c);
	CLEAR();
	ADV();
	a=CC;
	printf("%c\n",a);
	ADV();
	b=CC;
	printf("%c\n",b);
	ADV();
	c=CC;
	printf("%c\n",c);
	CLOSE();
	return 0;
}