#include "point.h"
#include <stdio.h>

void main() {
	Point P1,P2;
	int dx,dy;
	BacaPoint(&P1);
	TulisPoint(P1);
	BacaPoint(&P2);
	TulisPoint(P2);
	printf("Masukkan pergeseran x dan y P1:");
	scanf("%d",&dx);
	scanf(" %d",&dy);
	Geser(&P1,dx,dy);
	printf("Masukkan pergeseran x dan y P2:");
	scanf("%d",&dx);
	scanf(" %d",&dy);
	Geser(&P2,dx,dy);
	TulisPoint(P1);
	TulisPoint(P2);
	if (EQPoint(P1,P2))
		{
			printf("Pointnya sama cuy\n");
		}
	if (NEQPoint(P1,P2))
		{
			printf("Pointnya beda cuy\n");
		}
}
