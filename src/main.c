#include <stdio.h>
#ifdef __unix__
  #include <unistd.h>
#elif defined _WIN32
  #include <windows.h>
  #define sleep(x) Sleep(1000 * x)
#endif
#include "adt/boolean/boolean.h"
#include "adt/gamecoordinator/gamecoordinator.h"

int main() {
  boolean isUp;
  int pilmenu;
  int MapBrs, MapKol;
  GameCoordinator GC;

  isUp = true;
  InitGame(&GC, 8, 8);
  while (isUp) {
    PrintMenu();

    printf(">>> ");
    scanf("%d", &pilmenu);
    if (pilmenu == 1) {
      /* memulai game */
      MapBrs = 0; MapKol = 0;
      for (;;) {
        printf("Input jumlah baris di map: "); scanf("%d", &MapBrs);
        printf("Input jumlah kolom di map: "); scanf("%d", &MapKol);
        if (!IsMapSizeValid(MapBrs, MapKol)) {
          printf("Ukuran map tidak valid\n");
        } else {
          break;
        }
      }
      InitGame(&GC, MapBrs, MapKol);
      RunGame(&GC);
    } else if (pilmenu == 2) {
      /* load game */
      if(LoadGame(&GC)) {
        sleep(2);
        RunGame(&GC);
      } else {
        sleep(2);
      }
    } else if (pilmenu == 3) {
      /* save game */
      SaveGame(GC);
      sleep(2);
    } else if (pilmenu == 4) {
      /* keluar dari game */
      isUp = false;
    } else {
      /* pilihan tidak terdaftar */
      printf("Input salah, coba lagi\n");
      PrintMenu();
    }
  }
  printf("Game diakhiri, terima kasih sudah bermain!\n");

  return 0;
}