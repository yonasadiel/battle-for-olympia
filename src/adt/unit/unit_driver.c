#include "unit.h"
#include "../point/point.h"

int main(){
	Unit U;
	Point P;
	MakePoint(1,2,&P);
	CreateUnit(&U,'K',P);
	PrintUnitName(U);
	printInfoUnit(U);
	return 0;
}
