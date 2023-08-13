@echo off
del dragon.exe
C:\Users\Kai\Documents\program\tcc\tcc main.c -lSDL2 -lSDL2_ttf -lSDL2_Image -o dragon.exe 
pause
dragon
rem del dragon.exe