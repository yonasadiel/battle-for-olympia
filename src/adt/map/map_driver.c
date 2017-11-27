#include <stdio.h>
#include "map.h"
#include "../color/color.h"
#include "../point/point.h"

int main() {
	Map M1, M2;
  Point P1, P2;
  Unit U;
  Building B;
  int a,b;

  a = -1; b = 2; if (IsIdxValid(a, b)) { printf("(%d,%d) adalah titik yang valid\n",a,b); }
  a =  0; b = 2; if (IsIdxValid(a, b)) { printf("(%d,%d) adalah titik yang valid\n",a,b); }
  a =  2; b = 2; if (IsIdxValid(a, b)) { printf("(%d,%d) adalah titik yang valid\n",a,b); }
  a = 16; b = 2; if (IsIdxValid(a, b)) { printf("(%d,%d) adalah titik yang valid\n",a,b); }
  a = 2; b = 50; if (IsIdxValid(a, b)) { printf("(%d,%d) adalah titik yang valid\n",a,b); }

  a = -1; b = 8; if (IsMapSizeValid(a, b)) { printf("%dx%d adalah ukuran yang valid\n",a,b); }
  a =  0; b = 8; if (IsMapSizeValid(a, b)) { printf("%dx%d adalah ukuran yang valid\n",a,b); }
  a =  8; b = 8; if (IsMapSizeValid(a, b)) { printf("%dx%d adalah ukuran yang valid\n",a,b); }
  a = 16; b = 8; if (IsMapSizeValid(a, b)) { printf("%dx%d adalah ukuran yang valid\n",a,b); }
  a = 2; b = 50; if (IsMapSizeValid(a, b)) { printf("%dx%d adalah ukuran yang valid\n",a,b); }

	MakeMap(8,8,&M1);
  P1.X = 2; P1.Y = 7;
  printf("Terbentuk Map ukuran %dx%d\n", NBrsEffMap(M1), NKolEffMap(M1));
	TulisMap(M1, P1);

  P2.X = 2; P2.Y = 7; U.Location = P2; U.Type = 'K'; MapPutUnit(&M1, U, CBLUE);
  P2.X = 3; P2.Y = 3; U.Location = P2; U.Type = 'S'; MapPutUnit(&M1, U, CRED);
  P2.X = 2; P2.Y = 7; B.Coordinate = P2; B.Type = 'C'; MapPutBuilding(&M1, B, CBLUE);
  P2.X = 4; P2.Y = 4; B.Coordinate = P2; B.Type = 'T'; MapPutBuilding(&M1, B, CRED);

  TulisMap(M1, P1);

  if ( IsPlayerCastle(M1, 2, 7, CBLUE)) { printf("Castle milik Biru\n"); }
  if (!IsPlayerCastle(M1, 2, 7, CRED )) { printf("Castle bukan milik Merah\n"); }
  if (!IsLocEmpty(M1, 2, 7)) { printf("(2,7) tidak kosong\n"); }
  if ( IsLocEmpty(M1, 4, 4)) { printf("(4,4) kosong\n"); }

  MCopy(M1, &M2);
  printf("Hasil Copy:\n");
  TulisMap(M2, P1);

	return 0;
}
	
