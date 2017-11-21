// DRIVER MAP

#include "map.h"
#include "../color/color.h"

int main() {
	Map M;
	MakeMap(13,13,&M);
	TulisMap(M);
	return 0;
}
	
