@echo off
gcc^
    "src\adt\player\player_driver.c"^
    "src\adt\building\building.c"^
    "src\adt\listlinier\listlinier.c"^
    "src\adt\listsirkuler\listsirkuler.c"^
    "src\adt\map\map.c"^
    "src\adt\color\color.c"^
    "src\adt\point\point.c"^
    "src\adt\unit\unit.c"^
    "src\adt\player\player.c"^
    "src\adt\pcolor\pcolor.c"^
  -o^
    "bin\driver\player"