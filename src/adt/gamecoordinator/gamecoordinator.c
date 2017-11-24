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

boolean isValidInput(char c) {
  return  (c >= 48 && c <= 57) ||
          (c >= 65 && c <= 90) ||
          (c >= 97 && c <= 122);
}

char* getSavedFileName() {
  char* res;
  char filename[31];
  char dir[37];
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
      if(isValidInput(c)) {
        if(len < 31) {
          filename[len] = c;
          len++;  
        } else {
          valid = false;
        } 
      } else {
        valid = false;
      }
    }
  } while(c != 10 && c != 0 && valid);

  if(valid || filename[0] == 0) {
    filename[len] = 0;
    strcpy(dir, "saved\\");
    strcat(dir, filename);
    res = dir;
  } else {
    filename[0] = 0;
    res = filename;
    printf("Invalid file name.\n");
  }
  return res;
}

char* getLoadedFileName() {
  FILE* file;
  int size;
  char* res;

  res = 0;
  file = fopen("size.sdat", "r");
  if(file) {
    fscanf(file, "%d", &size);
    fclose(file);
  } else {
    size = 0;
  }
  if(size == 0) {
    printf("You have no saved file.\n");
  } else {
    char filenames[size][31];
    int count;
    int n;

    STARTKATA("size.sdat");
    count = 0;
    while(!EndKata) {
      int idx = 6;
      while(idx <= CKata.Length) {
        filenames[count][idx-6] = CKata.TabKata[idx];
        idx++;
      }
      filenames[count][idx] = 0;
      printf("%d. %s\n", (count+1), filenames[count]);
      ADVKATA();
    }

    printf("Choose file to load.\n");
    printf("File number: ");
    scanf("%d", &n);

    if(n >= 0 && n <= size) {
      res = filenames[n];
    } else {
      printf("Invalid number.");
    }
  }

  return res;
}

void PrintMenu(void) {
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

void LoadGame(GameCoordinator* GC) {
  char* filename = getLoadedFileName();
  if(filename != 0) {
    
  }
}

void SaveGame(GameCoordinator GC) {
  char* filename = getSavedFileName();
  char c = 'y';
  boolean isNew;
  int size;

  if(filename[0] != 0) {
    FILE *file = fopen(filename, "r");
    if(file) {
      printf("File already exist. Do you want to replace? (y/n) ");
      scanf("%c", c);
      isNew = false;
    } else {
      isNew = true;
    }
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
          fprintf(file, "%d", size);
        }
      }
      file = fopen(filename, "w");
      if(file) {
        Queue queue;
        Player player;
        int playerQueue;
        ListSirkuler units;
        ListLinier buildings;
        LSAddress addrUnit;
        LLAddress addrBuilding;
        int count;
        Stack moves;
        Unit currentUnit;

        // Getting Player Queue
        queue = QI(GC);
        // Saving Player from Head of Queue
        count = 0;
        while(count < 2) {
          QDel(&queue, &playerQueue);
          player = Pi(GC, playerQueue);

          // Saving player number
          fprintf(file, "%d\n", playerQueue);
          // Saving player properties
          fprintf(file, "%d %d %d %d\n", Cash(player), Income(player), UpKeep(player), Warna(player));

          // Saving every player's units
          units = ListUnit(player);
          if(!LSIsEmpty(units)) {
            addrUnit = LSFirst(units);
            do {
              Unit unit = (*(Unit*) LSInfo(addrUnit));
              fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d\n", 
                MaxHealth(unit), Health(unit), Atk(unit), Heal(unit), MovPoint(unit), 
                AtkType(unit), AtkChance(unit), Absis(Location(unit)), Ordinat(Location(unit)),
                RecCost(unit), Type(unit));
              addrUnit = LSNext(addrUnit);
            } while(addrUnit != LSFirst(units));
          }
          fprintf(file, "#\n");

          // Saving every player's buildings
          buildings = ListBuilding(player);
          addrBuilding = LLFirst(buildings);
          while(addrBuilding != Nil) {
            Building building = (*(Building*) LLInfo(addrBuilding));
            fprintf(file, "%d %d %d\n", Absis(BCoordinate(building)), Ordinat(BCoordinate(building)), BType(building));
            addrBuilding = LLNext(addrBuilding); 
          }
          fprintf(stderr, "#\n");

          QAdd(&queue, playerQueue);
          count++;
        }

        // Saving Move Record
        moves = SReverse(MoveRecord(GC));
        while(!SIsEmpty(moves)) {
          SInfoType info;
          SPop(&moves, &info);
          fprintf(file, "%d %d ", Absis(info), Ordinat(info));
        }

        // Saving Current Unit
        currentUnit = *CurrentUnit(GC);
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d\n", 
          MaxHealth(currentUnit), Health(currentUnit), Atk(currentUnit), Heal(currentUnit), MovPoint(currentUnit), 
          AtkType(currentUnit), AtkChance(currentUnit), Absis(Location(currentUnit)), Ordinat(Location(currentUnit)),
        RecCost(currentUnit), Type(currentUnit));
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

    if (strcmp(cmd, "MOVE") && strcmp(cmd, "MAP") && strcmp(cmd, "INFO") && strcmp(cmd, "ATTACK")) {
      SPopAll(&MoveRecord(*GC));
    }

    system("cls");
    if (!strcmp(cmd, "MAP")) {
      TulisMap(GameMap(*GC), Location(*CurrentUnit(*GC)));
    } else if (!strcmp(cmd, "UNDO")) {
      UndoMovement(GC);
    } else if (!strcmp(cmd, "END_TURN")) {
      EndTurn(GC);
      printf("Player %d's turn!\n", QInfoHead(QI(*GC)));
    } else if (!strcmp(cmd, "EXIT")) {
      IsRunning = false;
    } else if (!strcmp(cmd, "ATTACK")) {
      Attack(GC);
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

ListSirkuler GetListSurroundingUnit(GameCoordinator GC) {
	ListSirkuler LS;
	Point P,Pa,Pb,Pc,Pd;
	Player Enemy;
	Unit* checkUnit;
	int Px,Py;
	if (QInfoHead(QI(GC)) == 1) {
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
				printf ("Select enemy you want to attack:");
				scanf ("%d",&option);
				if ((option > i) || (option <= 0)) {
					printf ("Wrong input, please select attackable enemy\n");
				}
			}
			while ((option > i) || (option <= 0));
			
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
				}
			} else {
				printf("Enemy's ");
				PrintUnitName(*attackedUnit);
				printf(" is dead :)\n");
			}
		}
		AtkChance(*CurrentUnit(*GC)) = false;
		MovPoint(*CurrentUnit(*GC)) = 0;
	} else {
		printf("Your ");
		PrintUnitName(*CurrentUnit(*GC));
		printf(" can't attack anymore in this turn\n");
	}
}
			
				
				
	
	
	
	
