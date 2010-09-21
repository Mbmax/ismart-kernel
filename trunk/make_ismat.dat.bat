@echo off
cls

wintools\ndstool.exe -c ismat.dat -r7 0x037f8000 -e7 0x037f8000 -r9 0x02000000 -e9 0x02000000 -7 arm7.bin -9 arm9.bin -b icon.bmp "MoonShell;Version 2.00;RVCT4.0 [Build 471]"

wintools\guidpatch.exe /patch ismat.dat

pause

