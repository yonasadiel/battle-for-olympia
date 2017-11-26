#include "color.h"
#include <stdio.h>

int main() {
  Color C;

  C = CRED;
  PrintInColor('R', C);
  PrintInColor('E', C);
  PrintInColor('D', C); printf("\n");

  C = CGREEN;
  PrintInColor('G', C);
  PrintInColor('R', C);
  PrintInColor('E', C);
  PrintInColor('E', C);
  PrintInColor('N', C); printf("\n");

  C = CYELLOW;
  PrintInColor('Y', C);
  PrintInColor('E', C);
  PrintInColor('L', C);
  PrintInColor('L', C);
  PrintInColor('O', C);
  PrintInColor('W', C); printf("\n");

  C = CBLUE;
  PrintInColor('B', C);
  PrintInColor('L', C);
  PrintInColor('U', C);
  PrintInColor('E', C); printf("\n");

  C = CMAGENTA;
  PrintInColor('M', C);
  PrintInColor('A', C);
  PrintInColor('G', C);
  PrintInColor('E', C);
  PrintInColor('N', C);
  PrintInColor('T', C);
  PrintInColor('A', C); printf("\n");

  C = CCYAN;
  PrintInColor('C', C);
  PrintInColor('Y', C);
  PrintInColor('A', C);
  PrintInColor('N', C); printf("\n");

}