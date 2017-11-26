@echo off
gcc^
    "src\adt\gamecoordinator\gamecoordinator_driver.c"^
    "src\adt\gamecoordinator\gamecoordinator.c"^
    "src\adt\listlinier\listlinier.c"^
    "src\adt\listsirkuler\listsirkuler.c"^
    "src\adt\map\map.c"^
    "src\adt\player\player.c"^
    "src\adt\queue\queue.c"^
    "src\adt\stackpoint\stackpoint.c"^
    "src\adt\mesinkata\mesinkata.c"^
  -o^
    "bin\driver\gamecoordinator"