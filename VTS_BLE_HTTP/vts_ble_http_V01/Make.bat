@echo off
@copy coreSW\scat6252.txt  build\scat6252.txt
@copy coreSW\rom.exe  rom.exe
@copy coreSW\neoway_remote.exe  neoway_remote.exe
@echo coreSW\NEOWAY61A_MOD_11C_PCB01_gprs_MT6261_S00.sym> ./build/~coresymlnk.tmp
@if "%1"=="" (echo please input "make help") else coreSW\make.exe %1 %2 %3 

@if exist build\ROM1  (del build\ROM1)
@if exist build\Neoway_Remote.bin  (del build\Neoway_Remote.bin)
@if exist build\ROM  (del build\ROM)
@if exist build\NEOWAY61A_MOD_11C_BB.cfg  (del build\NEOWAY61A_MOD_11C_BB.cfg)

@echo f|xcopy  build\*.bin  NEOWAY_CUSTOM_V01.bin
@if exist "NEOWAY_CUSTOM_V01.bin" (call rom.exe)
@if exist "ROM1" (call neoway_remote.exe)
@copy ROM1 build\ROM1 
@copy Neoway_Remote.bin build\Neoway_Remote.bin 


@if exist build\ROM1  (copy coreSW\ROM  build\ROM)
@if exist build\ROM1  (copy coreSW\NEOWAY61A_MOD_11C_BB.cfg  build\NEOWAY61A_MOD_11C_BB.cfg)

@if exist build\NEOWAY_CUSTOM_V01.bin  (del build\NEOWAY_CUSTOM_V01.bin)
@if exist build\NEOWAY_CUSTOM_V01.elf  (del build\NEOWAY_CUSTOM_V01.elf)
@if exist build\NEOWAY_CUSTOM_V01.sym  (del build\NEOWAY_CUSTOM_V01.sym)
@if exist build\scat6252.txt  (del build\scat6252.txt)

@del NEOWAY_CUSTOM_V01.bin ROM1 rom.exe neoway_remote.exe Neoway_Remote.bin


