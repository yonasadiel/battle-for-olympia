#include "building.h"
#include "../point/point.h"
#include <stdio.h>

int main() {
  Building B1,B2,B3;
  Point P;

  P.X = 5;  P.Y = 7; MakeBuilding(&B1, P, 'V');
  P.X = 3;  P.Y = 2; MakeBuilding(&B2, P, 'C');
  P.X = 10; P.Y = 1; MakeBuilding(&B3, P, 'T');

  printf("%c (%d,%d)\n", BType(B1), BCoordinate(B1));; /* V  5 7 */
  printf("%c (%d,%d)\n", BType(B2), BCoordinate(B2));; /* C  3 2 */
  printf("%c (%d,%d)\n", BType(B3), BCoordinate(B3));; /* T 10 1 */
}