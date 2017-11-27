#include "unit.h"
#include "../point/point.h"
#include <stdio.h>

int main(){
	Unit U;
	Point P;
	int G;
	char C;
	MakePoint(1,2,&P);
	CreateUnit(&U,'K',P);
	PrintUnitName(U);
	printf("\n");
	printInfoUnit(U);
	printf("\n");
	C='A';
	G=CheckGold(C);
	printf("%d\n",G);
	C='S';
	G=CheckGold(C);
	printf("%d\n",G);
	C='W';
	G=CheckGold(C);
	printf("%d\n",G);
	G=16;
	PrintAvailRecruit(G);
	G=17;
	PrintAvailRecruit(G);
	G=26;
	PrintAvailRecruit(G);
	G=41;
	PrintAvailRecruit(G);
	return 0;
}
