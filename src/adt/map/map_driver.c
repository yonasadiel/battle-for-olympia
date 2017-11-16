// DRIVER MAP

#include "map.h"
#include "../color/color.h"

int main() {
	Map M;
	MakeMap(8,8,&M);
	TulisMap(M);
	return 0;
}
	
