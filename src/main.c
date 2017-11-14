#include <stdio.h>
#include "adt/boolean/boolean.h"
#include "adt/gamecoordinator/gamecoordinator.h"

int main() {
  boolean isUp;
  int pilmenu;
  GameCoordinator GC;

  isUp = true;
  InitGame(&GC);
  while (isUp) {
    PrintMenu();

    printf(">>> ");
    scanf("%d", &pilmenu);
    if (pilmenu == 1) {
      /* memulai game */
      RunGame(&GC);
    } else if (pilmenu == 2) {
      /* load game */
      LoadGame(&GC);
    } else if (pilmenu == 3) {
      /* save game */
      SaveGame(GC);
    } else if (pilmenu == 4) {
      /* keluar dari game */
      isUp = false;
    } else {
      /* pilihan tidak terdaftar */
      printf("Input salah, coba lagi\n");
      PrintMenu();
    }
  }
  printf("Game diakhiri, terima kasih sudah bermain!");

  return 0;
}