#include "gamecoordinator.h"
#include "../boolean/boolean.h"
#include "../listlinier/listlinier.h"
#include "../listsirkuler/listsirkuler.h"
#include "../map/map.h"
#include "../stackpoint/stackpoint.h"
#include "../queueint/queueint.h"
#include "../player/player.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

/* #define NMaxPlayer 2 */
/* typedef struct { */
/*   Player P[NMaxPlayer+1]; */
/*   Queue QI; */
/*   Map GameMap; */
/*   Stack MoveRecord; */
/*   Unit* CurrentUnit; */
/* } GameCoordinator; */

/* *** Selektor *** */
/* #define Pi(GC,i) (GC).P[(i)] */
/* #define QI(GC) (GC).QI */
/* #define GameMap(GC) (GC).GameMap */
/* #define MoveRecord(GC) (GC).MoveRecord */
/* #define CurrentUnit(GC) (GC).CurrentUnit */

/* Simplify LoadGame */
#define VALID_ADV(ERR, GOTO) if(ERR){goto GOTO;}ADVKATA()
#define ADV_INT(VAR,ERR,GOTO) ToInteger(&VAR, &ERR);VALID_ADV(ERR,GOTO)
#define endl printf("\n")

/* Global Variable to Use FormattedPrint */
int arg[16];

void PrintMenu(void) {
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
	printf ("1. New Game\n");
	printf ("2. Load Game\n");
	printf ("3. Save Game\n");
	printf ("4. Quit\n");
	
}

void InitGame(GameCoordinator* GC, int NInitBaris, int NInitKolom) {
  Point P1, P2;

  system("cls");

  MakeMap(NInitBaris,NInitKolom, &GameMap(*GC));
  MakePoint(NInitBaris-1, 2, &P1);
  MakePoint(2, NInitKolom-1, &P2);

  MakePlayer(&Pi(*GC, 1), CRED, P1, &GameMap(*GC));
  MakePlayer(&Pi(*GC, 2), CBLUE, P2, &GameMap(*GC));

  QCreateEmpty(&QI(*GC));
  QAdd(&QI(*GC), 1);
  QAdd(&QI(*GC), 2);

  SCreateEmpty(&MoveRecord(*GC));
  CurrentUnit(*GC) = (Unit*) LSInfo(LSFirst(ListUnit(Pi(*GC,QInfoHead(QI(*GC))))));
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
  return  (c >= 48 && c <= 57) ||
          (c >= 65 && c <= 90) ||
          (c >= 97 && c <= 122);
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
    scanf("%c", &c);
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
  if(file) {
    fscanf(file, "%d", &size);
    fclose(file);
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
    count = 1;
    while(count <= size) {
      int idx = 1;
      while(idx <= CKata.Length) {
        filenames[count][idx-1] = CKata.TabKata[idx];
        idx++;
      }
      filenames[count][idx-1] = '\0';
      printf("%d. %s\n", count, filenames[count]);
      ADVKATA();
      count++;
    }
    CLOSEKATA();

    printf("Choose file to load.\n");
    printf("File number: ");
    scanf("%d", &n); endl;

    if(n > 0 && n <= size) {
      int idx = 0;
      res = (char*) malloc(sizeof(char) * 40);
      do {
        res[idx] = filenames[n][idx];
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
  QCreateEmpty(&QI(*GC));

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
    QAdd(&QI(*GC), playerNumber);
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
      printf("File already exist. Do you want to replace? (y/n) ");
      scanf("%c", &c);
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
        int playerQueue;
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
        queue = QI(GC);

        // Saving Player from Head of Queue
        count = 0;
        while(count < 2) {
          FormattedPrint(0, '=', 57, 0); endl;

          QDel(&queue, &playerQueue);
          player = Pi(GC, playerQueue);
          units = ListUnit(player);
          unitCount = LSNbElmt(units);
          buildings = ListBuilding(player);
          buildingCount = LLNbElmt(buildings);

          // Saving player properties
          arg[0] = playerQueue;
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
  ReduceCash(&Pi(*GC,QInfoHead(QI(*GC))));
  while (IsRunning) {
    printf("Player %d's Turn\n", QInfoHead(QI(*GC)));
    printPlayerInfo(Pi(*GC,QInfoHead(QI(*GC))));
    printCurrentUnitInfo(*CurrentUnit(*GC));
    printf("Command List: | MOVE | UNDO | CHANGE_UNIT | RECRUIT | ATTACK |\n");
    printf("              | MAP  | INFO | END_TURN    | SAVE    | EXIT   |\n");
    printf("Your input: "); scanf("%s", cmd);

    if (strcmp(cmd, "MOVE") && strcmp(cmd, "MAP") && strcmp(cmd, "INFO")) {
      SPopAll(&MoveRecord(*GC));
    }

    system("cls");
    if (!strcmp(cmd, "MAP")) {
      TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
    } else if (!strcmp(cmd, "UNDO")) {
      UndoMovement(GC);
    } else if (!strcmp(cmd, "CHANGE_UNIT")) {
      ChangeUnit(GC);
    } else if (!strcmp(cmd, "NEXT_UNIT")) {
      NextUnit(GC);
    } else if (!strcmp(cmd, "END_TURN")) {
      EndTurn(GC);
      printf("Player %d's turn!\n", QInfoHead(QI(*GC)));
    } else if (!strcmp(cmd, "EXIT")) {
      IsRunning = false;
    } else {
      printf("Command is Not Recognized\n\n\n");
    } 
  }
  system("cls");
  printf("Thanks for playing! See You!\n");
}

void printPlayerInfo(Player P) {
  printf("Cash: %dG | Income: %dG | UpKeep: %dG\n", Cash(P), Income(P), UpKeep(P));
}

void printCurrentUnitInfo(Unit U) {
  printf("Unit: ");
  PrintUnitName(U);
  TulisPoint(Location(U));
  printf(" | Movement Point: %d | Can Attack: ", MovPoint(U));
  if (AtkChance(U)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}

void EndTurn(GameCoordinator* GC) {
  QInfoType X;

  QAdd(&QI(*GC), QInfoHead(QI(*GC)));
  QDel(&QI(*GC), &X);

  CurrentUnit(*GC) = (Unit*) LSInfo(LSFirst(ListUnit(Pi(*GC,QInfoHead(QI(*GC))))));

  ReduceCash(&Pi(*GC,QInfoHead(QI(*GC))));
}

void ReduceCash(Player* P) {
  Cash(*P) -= UpKeep(*P);
  if (Cash(*P) < 0) Cash(*P) = 0;
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

    MoveUnit(&GameMap(*GC), CurrentUnit(*GC), Location(*CurrentUnit(*GC)), X);
    SPop(&MoveRecord(*GC), &X);
  }
}

void MoveUnit(Map* M, Unit* U, Point Source, Point Dest) {
  char temp;

  Location(*U) = Dest;
  temp = Unit(*M, Absis(Source), Ordinat(Source));
  Unit(*M, Absis(Source), Ordinat(Source)) = ' ';
  Unit(*M, Absis(Dest), Ordinat(Dest)) = temp;
  ColorUnit(*M, Absis(Dest), Ordinat(Dest)) = ColorUnit(*M, Absis(Source), Ordinat(Source));
}

void ChangeUnit(GameCoordinator* GC) {
  int NUnit;
  int pil;

  NUnit = LSNbElmt(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))));
  PrintAllUnitInfo(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))));

  for (;;) {
    printf("Please enter the no. of unit you want to select: ");
    scanf("%d",&pil);
    if (pil > NUnit || pil < 1) {
      printf("Wrong input, please choose between 1 to %d\n", NUnit);
    } else {
      break;
    }
  }

  if (CurrentUnit(*GC) == LSInfo(LSNthAddress(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))), pil))) {
    printf("Selected unit is current unit, canceling\n");
  } else {
    CurrentUnit(*GC) = LSInfo(LSNthAddress(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))), pil));
  }
  printf("\n");

}

void NextUnit(GameCoordinator* GC) {
  int NUnit;
  LSAddress AddrCurUnit;

  NUnit = LSNbElmt(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))));
  if (NUnit == 0) {
    printf("You dont have any unit, canceling...\n");
  } else if (NUnit == 1) {
    printf("You only have one unit, canceling...\n");
  } else {
    AddrCurUnit = LSSearch(ListUnit(Pi(*GC,QInfoHead(QI(*GC)))), CurrentUnit(*GC));
    if (AddrCurUnit == Nil) printf("erroooor\n");
    CurrentUnit(*GC) = LSInfo(LSNext(AddrCurUnit));
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