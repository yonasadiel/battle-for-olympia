@echo off
gcc^
    "src\adt\map\map_driver.c"^
    "src\adt\building\building.c"^
    "src\adt\color\color.c"^
    "src\adt\point\point.c"^
    "src\adt\unit\unit.c"^
  -o^
    "bin\driver\map"