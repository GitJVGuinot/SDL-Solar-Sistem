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
del *.obj *.pdb *.ilk *.exe
del ..\bin\*.obj ..\bin\*.pdb ..\bin\*.ilk ..\bin\*.exe
@echo  Objetos eliminados
@echo -----------------------------------------------------------------------

REM COMPILER

REM IMGUI
  cl /nologo /Zi /EHs /GR- /MD /W4 -I ..\deps\includes\SDL2 /c ..\deps\includes\IMGUI\*.cpp

  cl /nologo /Zi /EHs /GR- /MD ^
  -I ..\includes ^
  -I ..\deps\includes ^
  -I ..\deps\includes\IMGUI ^
  -I ..\deps\includes\SDL2 ^
  /c ..\src\*.cc ..\src\*.cc

  REM LINKER
  set "SDL2_Lib=..\deps\libs\Win_SDL2\x86\SDL2.lib"
  set "SDL2main_Lib=..\deps\libs\Win_SDL2\x86\SDL2main.lib"
  set "SDL2ttf_Lib=..\deps\libs\Win_SDL2\x86\SDL2_TTF.lib"
  set "OWN_my_window_lib=..\deps\libs\Win_own\my_window_release.lib"
  set "my_window_Lib=..\deps\libs\Win_own\my_window_release.lib"
  set "Libs=%SDL2_Lib% %SDL2main_Lib% %SDL2ttf_Lib% %SDL2image_lib% %SDL2mixer_lib% %my_window_Lib%"

  cl /nologo /Zi /EHs /GR- /MD /Fe:../bin/%name%.exe *.obj /link /SUBSYSTEM:CONSOLE %Libs% opengl32.lib shell32.lib user32.lib gdi32.lib

@echo -----------------------------------------------------------------------
@echo  Proceso por lotes finalizado.
@echo -----------------------------------------------------------------------
pause
