#include "gamecoordinator.h"
#include "../boolean/boolean.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../queue/queue.h"
#include "../player/player.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* #define NMaxPlayer 2 */
/* typedef struct { */
/*   Player P[NMaxPlayer+1]; */
/*   Queue QPlayer; */
/*   Map GameMap; */
/*   ListLinier ListVillage; */
/*   Stack MoveRecord; */
/*   Unit* CurrentUnit; */
/*   int State; */
/* } GameCoordinator; */

/* *** Selektor *** */
/* #define Pi(GC,i) (GC).P[(i)] */
/* #define QPlayer(GC) (GC).QPlayer */
/* #define GameMap(GC) (GC).GameMap */
/* #define ListVliiage(GC) (GC).ListVliiage */
/* #define MoveRecord(GC) (GC).MoveRecord */
/* #define CurrentUnit(GC) (GC).CurrentUnit */
/* #define State(GC) (GC).State */

/* Simplify LoadGame */
#define VALID_ADV(ERR, GOTO) if(ERR){goto GOTO;}ADVKATA()
#define ADV_INT(VAR,ERR,GOTO) ToInteger(&VAR, &ERR);VALID_ADV(ERR,GOTO)
#define endl printf("\n")
#define abs(x) ((x >= 0)? (x) : -1*(x))

/* Global Variable to Use FormattedPrint */
int arg[16];
/* Global Variable to use ToInteger */
boolean ERR;

void PrintMenu(GameCoordinator GC) {
  system("cls");
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
  if (State(GC) == 1) {
    printf ("1. Resume Game\n");
  	printf ("2. New Game\n");
  	printf ("3. Load Game\n");
  	printf ("4. Save Game\n");
  	printf ("5. Quit\n");
  } else {
    printf ("1. New Game\n");
    printf ("2. Load Game\n");
    printf ("3. Save Game\n");
    printf ("4. Quit\n");
  }
	
}

void InitGame(GameCoordinator* GC, int NInitBaris, int NInitKolom) {
  Point P1, P2;
  Building *V;
  int i,x,y;

  system("cls");

  MakeMap(NInitBaris,NInitKolom, &GameMap(*GC));
  MakePoint(NInitBaris-1, 2, &P1);
  MakePoint(2, NInitKolom-1, &P2);

  MakePlayer(&Pi(*GC, 1), CRED, P1, &GameMap(*GC));
  MakePlayer(&Pi(*GC, 2), CBLUE, P2, &GameMap(*GC));

  QCreateEmpty(&QPlayer(*GC));
  QAdd(&QPlayer(*GC), &Pi(*GC, 1));
  QAdd(&QPlayer(*GC), &Pi(*GC, 2));

  LLCreateEmpty(&ListVillage(*GC));
  V = (Building*) malloc(1 * sizeof (Building));
  srand(time(NULL));
  for (i=0; i<(NInitBaris*NInitKolom)/20; i++) {
    do {
      x = rand() % NInitBaris; x++;
      y = rand() % NInitKolom; y++;
    } while (Building(GameMap(*GC), x, y) != ' ');
    MakePoint(x, y, &P1);
    MakeBuilding(V, P1, 'V');
    LLInsVFirst(&ListVillage(*GC), V);
    Building(GameMap(*GC), x, y) = 'V';
    ColorBuilding(GameMap(*GC), x, y) = CWHITE;
  }

  SCreateEmpty(&MoveRecord(*GC));
  CurrentUnit(*GC) = (Unit*) LSInfo(LSFirst(ListUnit(*((Player*) QInfoHead(QPlayer(*GC))))));
  State(*GC) = 0;
}

void FormattedPrint(char* s, char aes, int size, int* arg) {
  int idx = 0;
  int iArg = 0;
  int numbAddedSpace = 0;

  if(s != 0) {
    while(s[idx] != 0) {
      if(s[idx] == '%' && s[idx+1] == 'd') {
        printf("%d", arg[iArg]);
        idx += 2;

        int xCount = 0;
        while(arg[iArg] > 0) {
          arg[iArg] /= 10;
          xCount++;
        }
        if(xCount > 1) {
          numbAddedSpace++;
        }

        iArg++;
      } else {
        printf("%c", s[idx]);
        idx++;
      }
    }
    idx += numbAddedSpace - iArg;
  }
  while(idx < size) {
    printf("%c", aes);
    idx++;
  }
}

boolean IsValidInput(char c) {
  return  (c >= '0' && c <= '9') ||
          (c >= 'a' && c <= 'z') ||
          (c >= 'A' && c <= 'Z');
}

char* GetSavedFileName() {
  char* res;
  char* filename = (char*) malloc(sizeof(char) * 31);
  char* dir = (char*) malloc(sizeof(char) * 40);
  char c;
  boolean valid;
  int len;

  printf("Input file name. Maximum 30 Character. Alphabet and Number only.\n");
  printf("File Name: ");

  len = 0;
  valid = true;
  do {
    START(0);
    c = CC;
    if(c != 10 && c != 0) {
      valid = valid && IsValidInput(c) && (len < 31);
      if(valid) {
        filename[len] = c;
        len++; 
      }
    }
  } while(c != 10 && c != 0);

  if(valid) {
    filename[len] = 0;
    strcpy(dir, "saved\\");
    strcat(dir, filename);
    strcat(dir, ".dat");
    res = dir;
  } else {
    res = 0;
    printf("Invalid file name.\n");
  }
  return res;
}

char* GetLoadedFileName() {
  FILE* file;
  int size;
  char* res;

  file = fopen("size.sdat", "r");
  STARTKATA("size.sdat");
  if(file) {
    ToInteger(&size, &ERR);
    CLOSEKATA();
  } else {
    size = 0;
  }
  if(size == 0) {
    printf("You have no saved file.\n");
    res = 0;
  } else {
    printf("You have %d saved game.\n", size);
    char filenames[size][40];
    int count;
    int n;

    STARTKATA("saved.sdat");
    count = 0;
    while(count <= size) {
      int idx = 1;
      while(idx <= CKata.Length) {
        filenames[count][idx-1] = CKata.TabKata[idx];
        idx++;
      }
      filenames[count][idx-1] = 0;
      printf("%d. %s\n", count+1, filenames[count]);
      ADVKATA();
      count++;
    }
    CLOSEKATA();
    count--;

    printf("Choose file to load.\n");
    printf("File number: ");
    STARTKATA(0);
    ToInteger(&n, &ERR); endl;
    if(n > 0 && n <= size) {
      n--;
      int idx = 0;
      res = (char*) malloc(sizeof(char) * 255);
      do {
        res[idx] = filenames[n][idx];
        printf("RES %d\n", res[idx]);
        idx++;
      } while(filenames[n][idx] != 0);
      res[idx] = 0;
    } else {
      res = 0;
    }
  }

  return res;
}

boolean LoadGame(GameCoordinator* GC) {
  char* filename = GetLoadedFileName();
  boolean err;
  int NBrsMap, NKolMap;
  int count, i;

  if(filename == 0) {
    goto INVAlID_NAME;
  }

  printf("Load file %s\n", filename);
  // Start to read file
  if(!STARTKATA(filename)) {
    goto ERROR_READ;
  }

  // Init GameCoordinator
  QCreateEmpty(&QPlayer(*GC));

  // Load Map 
  FormattedPrint("Loading Map Data.", '.', 50, 0);
  ADV_INT(NBrsMap, err, ERROR_READ);
  ADV_INT(NKolMap, err, ERROR_READ);
  MakeMap(NBrsMap, NKolMap, &GameMap(*GC));
  printf("Success\n");

  // Load Players
  count = 1;
  while(count <= 2) {
    count++;
    FormattedPrint(0, '=', 57, 0); endl;

    Player* player;
    int playerNumber;
    int playerCash;
    int playerIncome;
    Color playerWarna;
    int unitCount;
    int buildingCount;
    ListSirkuler* playerUnits;
    ListLinier* playerBuildings;

    // Init Player
    playerUnits = (ListSirkuler*) malloc(sizeof(ListSirkuler));
    playerBuildings = (ListLinier*) malloc(sizeof(ListLinier));
    player = (Player*) malloc(sizeof(Player));
    LSCreateEmpty(playerUnits);
    LLCreateEmpty(playerBuildings);
    ADV_INT(playerNumber, err, ERROR_READ);

    // Load Player Basic Properties
    arg[0] = playerNumber;
    FormattedPrint("Loading Player %d Properties", '.', 50, arg);
    ADV_INT(playerCash, err, ERROR_READ);
    ADV_INT(playerIncome, err, ERROR_READ);
    ADV_INT(playerWarna, err, ERROR_READ);
    Cash(*player) = playerCash;
    Income(*player) = playerIncome;
    ListUnit(*player) = *playerUnits;
    ListBuilding(*player) = *playerBuildings;
    Warna(*player) = playerWarna;
    printf("Success\n");

    // Load Player's Units
    ADV_INT(unitCount, err, ERROR_READ);
    printf("Loading %d Player's Units.\n", unitCount);
    i = 0;
    while(i < unitCount) {
      i++;
      arg[0] = i; 
      FormattedPrint("Loading Unit %d", '.', 50, arg);

      Unit* unit;
      int unitMaxHealth;
      int unitHealth;
      int unitAtk;
      int unitHeal;
      int unitMovPoint;
      int unitAtkType;
      int unitAtkChance;
      int unitAbsis;
      int unitOrdinat;
      int unitRecCost;
      int unitType;
      Point* unitPoint;
     // Init Units
      unitPoint = (Point*) malloc(sizeof(Point));
      unit = (Unit*) malloc(sizeof(Unit));

      ADV_INT(unitMaxHealth, err, ERROR_READ);
      ADV_INT(unitHeal, err, ERROR_READ);
      ADV_INT(unitAtk, err, ERROR_READ);
      ADV_INT(unitHeal, err, ERROR_READ);
      ADV_INT(unitMovPoint, err, ERROR_READ);
      ADV_INT(unitAtkType, err, ERROR_READ);
      ADV_INT(unitAtkChance, err, ERROR_READ);
      ADV_INT(unitAbsis, err, ERROR_READ);
      ADV_INT(unitOrdinat, err, ERROR_READ);
      ADV_INT(unitRecCost, err, ERROR_READ);
      ADV_INT(unitType, err, ERROR_READ);
      
      MakePoint(unitAbsis, unitOrdinat, unitPoint);
      CreateUnit(unit, unitType, *unitPoint);
      MaxHealth(*unit) = unitMaxHealth;
      Health(*unit) = unitHealth;
      Atk(*unit) = unitAtk;
      Heal(*unit) = unitHeal;
      MovPoint(*unit) = unitMovPoint;
      AtkType(*unit) = unitAtkType;
      AtkChance(*unit) = unitAtkChance;
      RecCost(*unit) = unitRecCost;

      LSInsVFirst(playerUnits, unit);
      printf("Success\n");

      // Load Player's Buldings
      printf("Loading %d Player's Building.\n", buildingCount);
      ADV_INT(buildingCount, err, ERROR_READ);
      i = 0;
      while(i < buildingCount) {
        i++; 
        arg[0] = i;
        FormattedPrint("Loading Bulding %d", '.', 50, arg);

        Building* building;
        int buildingAbsis;
        int buildingOrdinat;
        int buildingType;
        Point* buildingPoint;

        // Init Building
        buildingPoint = (Point*) malloc(sizeof(Point));
        building = (Building*) malloc(sizeof(Building));

        ADV_INT(buildingAbsis, err, ERROR_READ);
        ADV_INT(buildingOrdinat, err, ERROR_READ);
        ADV_INT(buildingType, err, ERROR_READ);

        MakePoint(buildingAbsis, buildingOrdinat, buildingPoint);
        MakeBuilding(building, *buildingPoint, buildingType);
        LLInsVFirst(playerBuildings, building);

        printf("Success\n");
      }
    }

    // Add Player to GameCoordinator
    Pi(*GC, playerNumber) = *player;
    QAdd(&QPlayer(*GC), player);
  }

  // Load MoveRecord
  FormattedPrint(0, '=', 57, 0); endl;
  FormattedPrint("Loading Move Records", '.', 50, 0);
  ADV_INT(count, err, ERROR_READ);
  while(count > 0) {
    int moveAbsis;
    int moveOrdinat;
    Point* movePoint;

    // Init Point
    movePoint = (Point*) malloc(sizeof(Point));

    ADV_INT(moveAbsis, err, ERROR_READ);
    ADV_INT(moveOrdinat, err, ERROR_READ);

    MakePoint(moveAbsis, moveOrdinat, movePoint);
    SPush(&MoveRecord(*GC), *movePoint);

    count--;
  }
  printf("Success\n");

  // Load Current Unit
  Unit* cUnit;
  int cUnitMaxHealth;
  int cUnitHealth;
  int cUnitAtk;
  int cUnitHeal;
  int cUnitMovPoint;
  int cUnitAtkType;
  int cUnitAtkChance;
  int cUnitAbsis;
  int cUnitOrdinat;
  int cUnitRecCost;
  int cUnitType;
  Point* cUnitPoint;

  ADV_INT(cUnitMaxHealth, err, ERROR_READ);
  ADV_INT(cUnitHeal, err, ERROR_READ);
  ADV_INT(cUnitAtk, err, ERROR_READ);
  ADV_INT(cUnitHeal, err, ERROR_READ);
  ADV_INT(cUnitMovPoint, err, ERROR_READ);
  ADV_INT(cUnitAtkType, err, ERROR_READ);
  ADV_INT(cUnitAtkChance, err, ERROR_READ);
  ADV_INT(cUnitAbsis, err, ERROR_READ);
  ADV_INT(cUnitOrdinat, err, ERROR_READ);
  ADV_INT(cUnitRecCost, err, ERROR_READ);
  ADV_INT(cUnitType, err, ERROR_READ);

  cUnitPoint = (Point*) malloc(sizeof(Point));
  MakePoint(cUnitAbsis, cUnitOrdinat, cUnitPoint);
  cUnit = (Unit*) malloc(sizeof(Unit));
  CreateUnit(cUnit, cUnitType, *cUnitPoint);
  MaxHealth(*cUnit) = cUnitMaxHealth;
  Health(*cUnit) = cUnitHealth;
  Atk(*cUnit) = cUnitAtk;
  Heal(*cUnit) = cUnitHeal;
  MovPoint(*cUnit) = cUnitMovPoint;
  AtkType(*cUnit) = cUnitAtkType;
  AtkChance(*cUnit) = cUnitAtkChance;
  RecCost(*cUnit) = cUnitRecCost;

  CurrentUnit(*GC) = cUnit;

  // End of Loading
  FormattedPrint(0, '=', 57, 0); endl;
  printf("Game is loaded succesfully.\n");
  goto LOAD_FINISH;

  INVAlID_NAME:
    printf("Invalid number.\n");
    return false;

  // Print error message when error occured
  ERROR_READ:
    printf("Error has been occured. Cannot load game file.\n");
    return false;

  // Finishing
  LOAD_FINISH:
    printf("Loading finished.\n");
    return true;
}


void SaveGame(GameCoordinator GC) {
  char* filename = GetSavedFileName();
  char c = 'y';
  boolean isNew;
  int size;

  if(filename != 0) {
    // Check if file already exist
    FILE *file = fopen(filename, "r");
    if(file) {
      CLEAR();
      printf("File already exist. Do you want to replace? (y/n) ");
      START(0);
      c = CC;
      isNew = false;
    } else {
      isNew = true;
    }

    // Updating list of saved file and
    // number of saved file
    if(c == 'y') {
      if(isNew) {
        file = fopen("saved.sdat", "a+");
        if(file) {
          fprintf(file, "%s\n", filename);
          fclose(file);
        }
        file = fopen("size.sdat", "r");
        if(file) {
          fscanf(file, "%d", &size);
          fclose(file);
        } else {
          size = 0;
        }
        file = fopen("size.sdat", "w");
        if(file) {
          size++;
          fprintf(file, "%d", size);
          fclose(file);
        }
      }

      // Writing data to file
      file = fopen(filename, "w");
      if(file) {
        Queue queue;
        Player player;
        QInfoType playerQueue;
        int count;
        int unitCount, buildingCount;
        int i;
        ListSirkuler units;
        ListLinier buildings;
        LSAddress addrUnit;
        LLAddress addrBuilding;
        Stack moves;
        Unit currentUnit;

        // Saving Map Size
        FormattedPrint("Saving Map Data", '.', 50, 0);
        fprintf(file, "%d %d\n", NBrsEffMap(GameMap(GC)), NKolEffMap(GameMap(GC)));
        printf("Success\n");

        // Getting Player Queue
        queue = QPlayer(GC);

        // Saving Player from Head of Queue
        count = 0;
        while(count < 2) {
          FormattedPrint(0, '=', 57, 0); endl;

          QDel(&queue, &playerQueue);
          player = *((Player*) playerQueue);
          units = ListUnit(player);
          unitCount = LSNbElmt(units);
          buildings = ListBuilding(player);
          buildingCount = LLNbElmt(buildings);

          // Saving player properties
          arg[0] = (QInfoHead(QPlayer(GC)) == &Pi(GC, 1))? 1 : 2;
          FormattedPrint("Saving Player %d Data", '.', 50, arg);
          fprintf(file, "%d\n", playerQueue);
          fprintf(file, "%d %d %d\n", Cash(player), Income(player), Warna(player));
          printf("Success\n");

          // Saving every player's units
          printf("Saving %d Units.\n", unitCount);
          fprintf(file, "%d\n", unitCount);
          if(!LSIsEmpty(units)) {
            i = 1;
            addrUnit = LSFirst(units);
            do {
              arg[0] = i;
              FormattedPrint("Saving Unit %d", '.', 50, arg);
              Unit unit = (*(Unit*) LSInfo(addrUnit));
              fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d\n", 
                MaxHealth(unit), Health(unit), Atk(unit), Heal(unit), MovPoint(unit), 
                AtkType(unit), AtkChance(unit), Absis(Location(unit)), Ordinat(Location(unit)),
                RecCost(unit), Type(unit));
              addrUnit = LSNext(addrUnit);
              i++;
              printf("Success\n");
            } while(addrUnit != LSFirst(units));
          }

          // Saving every player's buildings
          printf("Saving %d Buildings.\n", buildingCount);
          fprintf(file, "%d\n", buildingCount);
          i = 1;
          addrBuilding = LLFirst(buildings);
          while(addrBuilding != Nil) {
            arg[0] = i;
            FormattedPrint("Saving Building %d", '.', 50, arg);
            Building building = *((Building*) LLInfo(addrBuilding));
            fprintf(file, "%d %d %d\n", Absis(BCoordinate(building)), Ordinat(BCoordinate(building)), BType(building));
            addrBuilding = LLNext(addrBuilding); 
            i++;
            printf("Success\n");
          }

          QAdd(&queue, playerQueue);
          count++;
        }

        // Saving Move Record
        FormattedPrint(0, '=', 57, 0); endl;
        FormattedPrint("Saving Move Records", '.', 50, 0);
        fprintf(file, "%d\n", SNbElmt(MoveRecord(GC)));
        moves = SReverse(MoveRecord(GC));
        while(!SIsEmpty(moves)) {
          SInfoType info;
          SPop(&moves, &info);
          fprintf(file, "%d %d ", Absis(info), Ordinat(info));
        }
        printf("Success\n");

        // Saving Current Unit
        currentUnit = *CurrentUnit(GC);
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d\n", 
          MaxHealth(currentUnit), Health(currentUnit), Atk(currentUnit), Heal(currentUnit), MovPoint(currentUnit), 
          AtkType(currentUnit), AtkChance(currentUnit), Absis(Location(currentUnit)), Ordinat(Location(currentUnit)),
          RecCost(currentUnit), Type(currentUnit));
        printf("Current unit saved.\n");

        // End of File
        FormattedPrint(0, '=', 57, 0); endl;
        fprintf(file, "#");
        printf("All data has been saved succesfully.\n");
        fclose(file);
      } else {
        printf("Cannot save game file. Please make sure you have folder /saved.\n"); 
      }
    }
  }
}

void RunGame(GameCoordinator* GC) {
  system("cls");
  char cmd[100];
  boolean IsRunning;
  int MapBrs, MapKol;

  IsRunning = true;
  State(*GC) = 1;
  ReduceCash(QInfoHead(QPlayer(*GC)));
  while (IsRunning) {
    TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));

    if (State(*GC) == 1) {
      printf("Player %d's Turn\n", (QInfoHead(QPlayer(*GC)) == &Pi(*GC, 1))? 1:2);
      
      printPlayerInfo(*((Player*) QInfoHead(QPlayer(*GC))));
      printCurrentUnitInfo(*CurrentUnit(*GC));
      printf("Command List: | MOVE | RECRUIT | CHANGE_UNIT | INFO     | SAVE |\n");
      printf("              | UNDO | ATTACK  | NEXT_UNIT   | END_TURN | EXIT |\n");
      printf("Your input: "); 
      STARTKATA(0); Salin(cmd);

      if (strcmp(cmd, "MOVE") && strcmp(cmd, "MAP") && strcmp(cmd, "INFO") && strcmp(cmd, "UNDO")) {
        SPopAll(&MoveRecord(*GC));
      }

      system("cls");
      if (!strcmp(cmd, "MOVE")) {
        MakeMovement(GC);
      } else if (!strcmp(cmd, "RECRUIT")) {
        TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
        RecruitUnit(GC);
      } else if (!strcmp(cmd, "UNDO")) {
        UndoMovement(GC);
      } else if (!strcmp(cmd, "CHANGE_UNIT")) {
        TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
        ChangeUnit(GC);
      } else if (!strcmp(cmd, "INFO")) {
        TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
        ShowInfo(*GC);
      } else if (!strcmp(cmd, "NEXT_UNIT")) {
        NextUnit(GC);
      } else if (!strcmp(cmd, "MAP")) {
        TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
      } else if (!strcmp(cmd, "END_TURN")) {
        EndTurn(GC);
        printf("Next Turn!\n");
      } else if (!strcmp(cmd, "EXIT")) {
        IsRunning = false;
      } else if (!strcmp(cmd, "ATTACK")) {
        Attack(GC);
      } else {
        printf("Command is Not Recognized\n\n\n");
      }
    } else {
      printf("Congratulations! You have won the battle\n");
      printf("Command List: | SAVE | EXIT |\n");
      printf("Your input: "); 
      STARTKATA(0); Salin(cmd);

      system("cls");
      if (!strcmp(cmd, "EXIT")) {
        IsRunning = false;
      } else {
        printf("Command is Not Recognized\n\n\n");
      }
    }
  }
}

void printPlayerInfo(Player P) {
  printf("Cash: %dG | Income: %dG | UpKeep: %dG\n", Cash(P), Income(P), UpKeep(P));
}

void printCurrentUnitInfo(Unit U) {
  printf("Unit: ");
  PrintUnitName(U);
  TulisPoint(Location(U));
  printf(" | Health: %d/%d | Movement Point: %d | Can Attack: ", Health(U), MaxHealth(U), MovPoint(U));
  if (AtkChance(U)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}

void EndTurn(GameCoordinator* GC) {
  QInfoType X;

  QDel(&QPlayer(*GC), &X);
  QAdd(&QPlayer(*GC), X);

  CurrentUnit(*GC) = (Unit*) LSInfo(LSFirst(ListUnit(*((Player*) QInfoHead(QPlayer(*GC))))));

  ResetMovPointAllUnit(QInfoHead(QPlayer(*GC)));
  ReduceCash(QInfoHead(QPlayer(*GC)));
  Cash(*((Player*) QInfoHead(QPlayer(*GC)))) += Income(*((Player*) QInfoHead(QPlayer(*GC))));
}

void ReduceCash(Player* P) {
  Cash(*P) -= UpKeep(*P);
  if (Cash(*P) < 0) Cash(*P) = 0;
}

void RecruitUnit(GameCoordinator *GC) {
  Player *P = (Player*) QInfoHead(QPlayer(*GC));
  Map* M = &GameMap(*GC);
	int x,y,pil;
  char UnitType;
  Point P1;
  Unit U;
  Unit *U1;

	U1=CurrentUnit(*GC);
	if ((Type(*U1))=='K') {
		if (Building(*M,Absis(Location(*U1)),Ordinat(Location(*U1)))=='T') {
			printf("Input castle coordinate: ");
      STARTKATA(0); ToInteger(&x, &ERR);
      STARTKATA(0); ToInteger(&y, &ERR);
      x++; y++;
			if (IsPlayerCastle(*M,x,y,Warna(*P))) {
				if (IsLocEmpty(*M,x,y)) {
					PrintAvailRecruit(Cash(*P)); printf("\n");
          for (;;) {
					  printf("What unit you want to recruit?\n");
            printf("1. Archer\n");
            printf("2. Swordsman\n");
            printf("3. White Mage\n");
            printf("Your choice [1-3]: ");
            STARTKATA(0); ToInteger(&pil, &ERR);
            if (pil >= 1 && pil <= 3) {
              break;
            } else {
              printf("Input salah\n");
            }
          }

          if      (pil == 1) UnitType = 'A';
          else if (pil == 2) UnitType = 'S';
          else               UnitType = 'W';

					if (CheckGold(UnitType) <= Cash(*P)) {
						MakePoint(x,y,&P1);
						AddUnit(P, P1, UnitType, &GameMap(*GC));
						Cash(*P) -= CheckGold(UnitType);
            system("cls");
            printf("Recruit Success\n");
					} else {
            system("cls");
						printf("You do not have enough gold.\n");
					}
				} else {
          system("cls");
					printf("The location is not empty.\n");
				}
			} else {
        system("cls");
				printf("That is not your castle.\n");
			}
		} else {
      system("cls");
			printf("To recruit a unit, your King must be in the tower.\n");
		}
	} else {
    system("cls");
		printf("To recruit a unit, your current unit must be the King.\n");
	}
}

void UndoMovement(GameCoordinator* GC) {
  Point X;

  if (SIsEmpty(MoveRecord(*GC))) {
    printf("Error: Current unit hasn't moved yet\n\n");
  } else {
    X = SInfoTop(MoveRecord(*GC));

    PrintUnitName(*CurrentUnit(*GC));
    printf(" berhasil UNDO dari ");
    TulisPoint(Location(*CurrentUnit(*GC)));
    printf(" ke ");
    TulisPoint(X);
    printf("\n\n");

    MovPoint(*CurrentUnit(*GC)) += abs(Absis(X) - Absis(Location(*CurrentUnit(*GC))));
    MovPoint(*CurrentUnit(*GC)) += abs(Ordinat(X) - Ordinat(Location(*CurrentUnit(*GC))));
    MoveUnit(&GameMap(*GC), CurrentUnit(*GC), X);
    SPop(&MoveRecord(*GC), &X);
  }
}

void MakeMovement(GameCoordinator *GC) {
  Point P, PU, *PT;
  int x,y,dist,i,j;
  Map MNew;
  Queue Q;
  QInfoType X;
  int dx[] = {0,1,-1,0};
  int dy[] = {1,0,0,-1};

  PU = Location(*CurrentUnit(*GC));
  MCopy(GameMap(*GC), &MNew);
  MakePoint(Absis(PU), Ordinat(PU), &P);
  QCreateEmpty(&Q);
  QAdd(&Q, &P);

  while (!QIsEmpty(Q)) {
    QDel(&Q, &X);
    P = *((Point*) X);
    free(X);

    for (i=0; i<4; i++) {
      int nx = Absis(P) + dx[i];
      int ny = Ordinat(P) + dy[i];
      if (IsIdxMapEff(MNew, nx, ny) &&
          (Unit(MNew, nx, ny) == ' ' ||
           (Unit(MNew, nx, ny) != ' ' &&
           ColorUnit(MNew, nx, ny) == Warna(*((Player*) QInfoHead(QPlayer(*GC)))))) &&
          abs(nx-Absis(PU)) + abs(ny-Ordinat(PU)) <= MovPoint(*CurrentUnit(*GC))) {
        PT = (Point*) malloc(1 * sizeof(Point));
        MakePoint(nx, ny, PT);
        Unit(MNew,nx,ny) = '#';
        ColorUnit(MNew,nx,ny) = CGREEN;
        QAdd(&Q, PT);
      }
    }
  }

  for (i = GetMapFirstIdxBrs(MNew); i<=GetMapLastIdxBrs(MNew); i++) {
    for (j = GetMapFirstIdxKol(MNew); j<=GetMapLastIdxKol(MNew); j++) {
      if (Unit(GameMap(*GC), i, j) != ' ') {
        Unit(MNew, i, j) = Unit(GameMap(*GC), i, j);
        ColorUnit(MNew, i, j) = ColorUnit(GameMap(*GC), i, j);
      }
    }
  }

  TulisMap(MNew, Location(*CurrentUnit(*GC)));

  for (;;) {
    printf("Please enter cell's coordinate x y ((-1,-1) to cancel): "); scanf("%d%d",&x,&y);
    x++; y++;
    if (!(x == 0 && y == 0) && Unit(MNew, x, y) != '#') {
      printf("You can't move there\n");
    } else {
      break;
    }
  }

  system("cls");
  if (!(x == 0 && y == 0)) {
    MakePoint(x,y,&P);
    SPush(&MoveRecord(*GC), Location(*CurrentUnit(*GC)));
    MoveUnit(&GameMap(*GC), CurrentUnit(*GC), P);
    MovPoint(*CurrentUnit(*GC)) -= abs(x-Absis(PU)) + abs(y-Ordinat(PU));

    if (Building(GameMap(*GC), Absis(P), Ordinat(P)) == 'V') {
      if      (ColorBuilding(GameMap(*GC), Absis(P), Ordinat(P)) == Warna(Pi(*GC, 1))) { Income(Pi(*GC, 1)) -= GoldPerVillage; }
      else if (ColorBuilding(GameMap(*GC), Absis(P), Ordinat(P)) == Warna(Pi(*GC, 2))) { Income(Pi(*GC, 2)) -= GoldPerVillage; }
      Income(*((Player*) QInfoHead(QPlayer(*GC)))) += GoldPerVillage;
      ColorBuilding(GameMap(*GC), Absis(P), Ordinat(P)) = Warna(*((Player*) QInfoHead(QPlayer(*GC))));
      SPopAll(&MoveRecord(*GC));
    }
  } else {
    printf("cancel MOVE...\n");
  }
}

void MoveUnit(Map* M, Unit* U, Point Dest) {
  char temp;
  Point Source;

  Source = Location(*U);
  Location(*U) = Dest;
  temp = Unit(*M, Absis(Source), Ordinat(Source));
  Unit(*M, Absis(Source), Ordinat(Source)) = ' ';
  Unit(*M, Absis(Dest), Ordinat(Dest)) = temp;
  ColorUnit(*M, Absis(Dest), Ordinat(Dest)) = ColorUnit(*M, Absis(Source), Ordinat(Source));
}

ListSirkuler GetListSurroundingUnit(GameCoordinator GC) {
	ListSirkuler LS;
	Point P,Pa,Pb,Pc,Pd;
	Player Enemy;
	Unit* checkUnit;
	int Px,Py;
	if (Warna(*((Player*) QInfoHead(QPlayer(GC)))) == Warna(Pi(GC,1))) {
		Enemy = Pi(GC,2);
	} else {
		Enemy = Pi(GC,1);
	}
	
	P = Location(*CurrentUnit(GC));
	MakePoint(Absis(P)+1,Ordinat(P),&Pa);
	MakePoint(Absis(P)-1,Ordinat(P),&Pb);
	MakePoint(Absis(P),Ordinat(P)+1,&Pc);
	MakePoint(Absis(P),Ordinat(P)-1,&Pd);

	LSCreateEmpty(&LS);
	if (!LSIsEmpty(ListUnit(Enemy))) {
		LSAddress p = LSFirst(ListUnit(Enemy));
		do {
			checkUnit = (Unit*) LSInfo(p);
			if(EQPoint(Location(*checkUnit), Pa) || EQPoint(Location(*checkUnit), Pb) || EQPoint(Location(*checkUnit), Pc) || EQPoint(Location(*checkUnit), Pd)) {
				LSInsVLast(&LS,checkUnit);
			}
			p = LSNext(p);
		}
		while (p != LSFirst(ListUnit(Enemy)));
	}
	return LS;
}
	
void Attack(GameCoordinator *GC) {
	if (AtkChance(*CurrentUnit(*GC))) {
		ListSirkuler LS;
		LSCreateEmpty(&LS);
		LS = GetListSurroundingUnit(*GC);
		boolean Retaliate[100], ret;
		LSAddress p;
		int i,j,option;
		Unit* checkUnit;
		Unit* attackedUnit;
    Player* Enemy;

    if (Warna(*((Player*) QInfoHead(QPlayer(*GC)))) == Warna(Pi(*GC,1))) {
      Enemy = &Pi(*GC,2);
    } else {
      Enemy = &Pi(*GC,1);
    }
		if (LSIsEmpty(LS)) {
			printf ("No enemy to attack\n");
		} else {
			printf ("Please select enemy you want to attack:\n");
			p = LSFirst(LS);
			i = 0;
			do {
				i++;
				checkUnit = (Unit*) LSInfo(p);
				printf ("%d. ",i);
				PrintUnitName(*checkUnit);
				printf(" ");
				TulisPoint(Location(*checkUnit));
				printf (" | Health %d/%d (",Health(*checkUnit),MaxHealth(*checkUnit));
				if ((AtkType(*CurrentUnit(*GC)) == AtkType(*checkUnit)) || (Type(*checkUnit) == 'K')) {
					printf ("Retaliates)\n");
					Retaliate[i] = true;
				} else {
					printf ("Doesn't retaliate)\n");
					Retaliate[i] = false;
				}
				p = LSNext(p);
			}
			while (p != LSFirst(LS));
			
			do {
				printf ("Select enemy you want to attack: ");
				STARTKATA(0); ToInteger(&option, &ERR);
				if ((option > i) || (option <= 0)) {
					printf ("Wrong input, please select attackable enemy\n");
				}
			}
			while ((option > i) || (option <= 0));
			
      printf("\n");
			j = 1;
			p = LSFirst(LS);
			while(j<option) {
				p = LSNext(p);
				j++;
			}
			ret = Retaliate[j];
			attackedUnit = (Unit*) LSInfo(p);
			Health(*attackedUnit) -= Atk(*CurrentUnit(*GC));
			printf("Enemy's ");
			PrintUnitName(*attackedUnit);
			printf(" is damaged by %d.\n",Atk(*CurrentUnit(*GC)));
			if (Health(*attackedUnit) > 0) {
				if (ret) {
					printf("Enemy's ");
					PrintUnitName(*attackedUnit);
					printf(" retaliates.\n");
					Health(*CurrentUnit(*GC)) -= Atk(*attackedUnit);
					printf("Your ");
					PrintUnitName(*CurrentUnit(*GC));
					printf(" is damaged by %d.\n",Atk(*attackedUnit));
				}
				if (Health(*CurrentUnit(*GC)) <= 0) {
					printf("Your ");
					PrintUnitName(*CurrentUnit(*GC));
					printf(" is dead :(\n");
          DeleteUnit(QInfoHead(QPlayer(*GC)), CurrentUnit(*GC), &GameMap(*GC));
          CurrentUnit(*GC) = (Unit*) LSInfo(LSFirst(ListUnit(*((Player*) QInfoHead(QPlayer(*GC))))));
				}
			} else {
				printf("Enemy's ");
        if (Type(*attackedUnit) == 'K') State(*GC) = 2;
				PrintUnitName(*attackedUnit);
				printf(" is dead :)\n");
        DeleteUnit(Enemy, attackedUnit, &GameMap(*GC));
			}
      AtkChance(*CurrentUnit(*GC)) = false;
      MovPoint(*CurrentUnit(*GC)) = 0;
		}
	} else {
		printf("Your ");
		PrintUnitName(*CurrentUnit(*GC));
		printf(" can't attack anymore in this turn\n");
	}
}
			
void ChangeUnit(GameCoordinator* GC) {
  int NUnit;
  int pil;

  NUnit = LSNbElmt(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))));
  PrintAllUnitInfo(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))));

  for (;;) {
    printf("Please enter the no. of unit you want to select: ");
    STARTKATA(0);
    ToInteger(&pil, &ERR);
    if (pil > NUnit || pil < 1) {
      printf("Wrong input, please choose between 1 to %d\n", NUnit);
    } else {
      break;
    }
  }

  system("cls");
  if (CurrentUnit(*GC) == LSInfo(LSNthAddress(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))), pil))) {
    printf("Selected unit is current unit, canceling\n");
  } else {
    CurrentUnit(*GC) = LSInfo(LSNthAddress(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))), pil));
  }
  printf("\n");

}

void NextUnit(GameCoordinator* GC) {
  int NUnit;
  LSAddress AddrCurUnit, PAddr;

  NUnit = LSNbElmt(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))));
  if (NUnit == 0) {
    printf("You dont have any unit, canceling...\n");
  } else if (NUnit == 1) {
    printf("You only have one unit, canceling...\n");
  } else {
    AddrCurUnit = LSSearch(ListUnit(*((Player*) QInfoHead(QPlayer(*GC)))), CurrentUnit(*GC));
    PAddr = AddrCurUnit;
    do {
      PAddr = LSNext(PAddr);
    } while (PAddr != AddrCurUnit && MovPoint(*((Unit*) LSInfo(PAddr))) == 0 && !AtkChance(*((Unit*) LSInfo(PAddr))));
    CurrentUnit(*GC) = LSInfo(PAddr);
  }
  printf("\n");

}

void PrintAllUnitInfo(ListSirkuler LU) {
  LSAddress P;
  Unit* U;
  int i;

  printf("== List of Units ==\n");
  if (LSIsEmpty(LU)) {
    printf("No Unit\n");
  } else {
    P = LSFirst(LU);
    i = 1;
    do {
      U = (Unit*) LSInfo(P);

      printf("%d. ", i++);
      PrintUnitName(*U);
      printf(" ");
      TulisPoint(Location(*U));
      printf(" | Health %d\n", Health(*U));

      P = LSNext(P);
    } while(P != LSFirst(LU));
  }
}

void ShowInfo(GameCoordinator GC) {
  int x,y;
  Point P;

  for (;;) {
    printf("Enter the coordinate of the cell: ");
    STARTKATA(0); ToInteger(&x, &ERR);
    STARTKATA(0); ToInteger(&y, &ERR);

    if (IsIdxMapEff(GameMap(GC), x+1, y+1)) {
      break;
    } else {
      printf("Coordinate isn't valid\n");
    }
  }
  system("cls");
  MakePoint(x+1, y+1, &P);
  printInfo(GC,P);
  printf("\n");
}

void printInfo(GameCoordinator GC, Point P) {
  LSAddress LSP;
  LLAddress LLP;
  Unit* U;

  printf("== Cell Info ==\n");
  if (Building(GameMap(GC),Absis(P),Ordinat(P)) == 'V'){
    printf("Village\n");
    if      (ColorBuilding(GameMap(GC),Absis(P),Ordinat(P)) == CRED ) { printf("Owned by Player 1\n"); }
    else if (ColorBuilding(GameMap(GC),Absis(P),Ordinat(P)) == CBLUE) { printf("Owned by Player 2\n"); }
    else                                                              { printf("Not Owned\n"); }
  }else if (Building(GameMap(GC),Absis(P),Ordinat(P)) == 'C'){
    printf("Castle\n");
    printf("Owned by ");
    if (ColorBuilding(GameMap(GC),Absis(P),Ordinat(P)) == CBLUE) { printf("Player 2\n"); }
    else                                                         { printf("Player 1\n"); }
  }else if (Building(GameMap(GC),Absis(P),Ordinat(P)) == 'T'){
    printf("Tower\n");
    printf("Owned by ");
    if (ColorBuilding(GameMap(GC),Absis(P),Ordinat(P)) == CBLUE) { printf("Player 2\n"); }
    else                                                         { printf("Player 1\n"); }
  }
  printf("\n");

  printf("== Unit Info ==\n");
  LSP = LSFirst(ListUnit(Pi(GC,1)));
  do {
    U = (Unit*) LSInfo(LSP);
    if (EQPoint(Location(*U), P)) {
      printInfoUnit(*U); printf("\n");
      printf("Owned by Player 1");
    }
    LSP = LSNext(LSP);
  } while (LSP != LSFirst(ListUnit(Pi(GC,1))));
  LSP = LSFirst(ListUnit(Pi(GC,2)));
  do {
    U = (Unit*) LSInfo(LSP);
    if (EQPoint(Location(*U), P)) {
      printInfoUnit(*U); printf("\n");
      printf("Owned by Player 2");
    }
    LSP = LSNext(LSP);
  } while (LSP != LSFirst(ListUnit(Pi(GC,2))));
  printf("\n");
  
}
