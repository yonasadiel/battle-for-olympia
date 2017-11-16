@echo off
gcc^
    "src\adt\listsirkuler\listsirkuler_driver.c"^
    "src\adt\building\building.c"^
    "src\adt\gamecoordinator\gamecoordinator.c"^
    "src\adt\listlinier\listlinier.c"^
    "src\adt\listsirkuler\listsirkuler.c"^
    "src\adt\map\map.c"^
    "src\adt\pcolor\pcolor.c"^
    "src\adt\color\color.c"^
    "src\adt\player\player.c"^
    "src\adt\point\point.c"^
    "src\adt\queueint\queueint.c"^
    "src\adt\stackpoint\stackpoint.c"^
    "src\adt\unit\unit.c"^
  -o^
    "bin\driver\listsirkuler"