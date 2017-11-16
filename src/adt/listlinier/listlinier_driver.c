#include "listlinier.h"
#include <stdio.h>

typedef struct {
	int x;
	int y;
} Point;

Point createPoint(int x, int y) {
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

void PrintPoint(Point point) {
	printf("<%d %d>", point.x, point.y);
}

int main() {
	Point point1 = createPoint(1, 2);
	Point point2 = createPoint(2, 3);
	Point point3 = createPoint(3, 4);

	List L;

	LLCreateEmpty(&L);

	LLInsVFirst(&L, &point1);
	LLInsVFirst(&L, &point2);
	LLInsVFirst(&L, &point3);

	address p = LLFirst(L);
	while(p != Nil) {
		Point* pointerToPoint = (Point*) LLInfo(p);
		Point isiPointerPoint = *pointerToPoint; 

		PrintPoint(isiPointerPoint);
		p = LLNext(p);
	}

	return 0;
}