#include "stackpoint.h"
#include <stdio.h>

void PrintStack(Stack S) {
	SAddress B=STop(S);
	if (SIsEmpty(S)) {
			printf("Ini stack kosong loh\n");
		}
	else {
			printf("Ini isi stacknya:\n");
			TulisPoint(SInfo(STop(S)));
			while (SNext(B)!=Nil) {
					if (STop(S)==B) {
						}
					TulisPoint(SInfo(SNext(B)));
					B=SNext(B);
				}
		}
}

void main() {
	Stack S;
	Point X,P;
	SCreateEmpty(&S);
	PrintStack(S);
	
	BacaPoint(&P);
	SPush(&S,P);
	PrintStack(S);
	
	BacaPoint(&P);
	SPush(&S,P);	
	PrintStack(S);
	
	BacaPoint(&P);
	SPush(&S,P);
	PrintStack(S);
	
	BacaPoint(&P);		
	SPush(&S,P);
	PrintStack(S);
	
	SPop(&S,&X);
	printf("Ini point yang dipop:");
	TulisPoint(X);
	PrintStack(S);
		
	SPop(&S,&X);
	printf("Ini point yang dipop:");
	TulisPoint(X);
	PrintStack(S);
		
	SPop(&S,&X);
	printf("Ini point yang dipop:");
	TulisPoint(X);
	PrintStack(S);
		
	SPop(&S,&X);
	printf("Ini point yang dipop:");
	TulisPoint(X);
	PrintStack(S);
		
}

