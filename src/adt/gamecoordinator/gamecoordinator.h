#ifndef gamecoordinator_h
#define gamecoordinator_h

#include "../boolean/boolean.h"
#include "../listsirkuler/listsirkuler.h
#include "../map/map.h
#include "../stackt/stackt.h
#include "../player/player.h

typedef struct {
    ListSirkuler players;
    Player currentPlayer;
    Map gameMap;
    Stack moveRecord;
} Coordinator;

void CreateGame(Coordinator &coordinator);
/* I.S. Coordinator sembarang; */
/* F.S. Membuat Game baru dengan menginisialisasi Game Coordinator */
/*      sebagai Coordinator yang terdefinisi kosong */

#endif
