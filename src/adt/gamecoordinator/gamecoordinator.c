#include "gamecoordinator.h"
#include "../boolean/boolean.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../player/player.h"
#include <stdio.h>

/* #define NMaxPlayer 2 */
/* typedef struct { */
/*   Player P[NMaxPlayer+1]; */
/*   QueueInt QI; */
/*   Map GameMap; */
/*   Stack MoveRecord; */
/* } GameCoordinator; */

void PrintFirstMenu(void) {
	printf ("_____________________________________________________T ___H ___E ______________________________________________________________\n");
	printf ("___________####### ___________# ____ # ___# ____________________####### __# ___________________________________________________\n");
	printf ("____________##   ## __________## ____## __## __________________##     ## _##__________________________________## ______________\n");
	printf ("____________##   ## _##### _###### ###### ## ___#### __________##     ## _## __## __## ## ### ### __####### _______##### ______\n");
	printf ("____________###### _# ___## __## ____## __## __##  ## __F O R _##     ## _## __## __## _## _## _## __##   ## _## _# ___## _____\n");
	printf ("____________##   ## _###### __## ____## __## __###### _________##     ## _## __## __## _## _## _## __##   ## _## __###### _____\n");
	printf ("____________##   ## ##   ## __## ____## __## __## _____________##     ## _## ___###### _## _## _## __###### __## _##   ## _____\n");
	printf ("___________####### _###### ___## ____## ___### _##### __________####### ___### ____ ## _## _## _### _## ______## _###### ______\n");
	printf ("_______________________________### ___### ______________________________________###### ______________## _______________________\n");
	printf ("\n==== MAIN MENU ====\n");
	printf ("1. New Game\n");
	printf ("2. Load Game\n");
	printf ("3. Quit\n");
	
}

void PrintNextMenu (void) {
	printf ("\n==== MAIN MENU ====\n");
	printf ("1. New Game\n");
	printf ("2. Load Game\n");
	printf ("3. Save Game\n");
	printf ("4. Quit\n");
}

void InitGame(GameCoordinator* GC) {
  //
}

void LoadGame(GameCoordinator* GC) {
  //
}

void SaveGame(GameCoordinator GC) {
  //
}

void RunGame(GameCoordinator* GC) {
  //
}
