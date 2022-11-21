@echo off

cls

set "name=%~n0"

REM Compilación y Enlace con librería gráfica.
@cls
@echo -----------------------------------------------------------------------
@echo  ESAT Curso 2022-2023 Asignatura PRG Primero
@echo -----------------------------------------------------------------------
@echo  Proceso por lotes iniciado.
@echo -----------------------------------------------------------------------
@echo  Eliminando objetos....
del *.obj *.pdb *.ilk
del ..\bin\*.obj ..\bin\*.pdb ..\bin\*.ilk
@echo  Objetos eliminados
@echo -----------------------------------------------------------------------

REM COMPILER
  cl /nologo /Zi /EHs /GR- /MDd /W4 -I ..\deps\includes\SDL2 /c ..\deps\includes\IMGUI\*.cpp

  cl /nologo /Zi /EHs /GR- /MDd ^
  -I ..\includes ^
  -I ..\deps\includes ^
  -I ..\deps\includes\IMGUI ^
  -I ..\deps\includes\SDL2 ^
  /c ..\src\*.cc

 REM LINKER
  set "SDL2_Lib=..\deps\libs\Win_SDL2\x86\SDL2.lib"
  set "SDL2main_Lib=..\deps\libs\Win_SDL2\x86\SDL2main.lib"
  set "SDL2ttf_Lib=..\deps\libs\Win_SDL2\x86\SDL2_TTF.lib"
  set "Libs=%SDL2_Lib% %SDL2main_Lib% %SDL2ttf_Lib%"

  cl /nologo /Zi /EHs /GR- /MDd /Fe:../bin/%name%.exe *.obj /link /SUBSYSTEM:CONSOLE %Libs% opengl32.lib shell32.lib user32.lib gdi32.lib

@echo -----------------------------------------------------------------------
@echo  Proceso por lotes finalizado.
@echo -----------------------------------------------------------------------
pause
