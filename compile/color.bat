@echo off
gcc^
    "src\adt\color\color_driver.c"^
    "src\adt\pcolor\pcolor.c"^
    "src\adt\color\color.c"^
  -o^
    "bin\driver\color"