@echo off
gcc^
    "src\adt\queue\queue_driver.c"^
    "src\adt\queue\queue.c"^
  -o^
    "bin\driver\queue"