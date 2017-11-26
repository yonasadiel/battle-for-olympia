@echo off
gcc^
    "src\adt\unit\unit_driver.c"^
    "src\adt\point\point.c"^
    "src\adt\unit\unit.c"^
  -o^
    "bin\driver\unit"