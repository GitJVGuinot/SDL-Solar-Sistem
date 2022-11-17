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
@echo  Objetos eliminados
@echo -----------------------------------------------------------------------

REM COMPILER
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\esfera_3d.cc
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\mv_math.cc
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\my_window.cc
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\SDL_event_control.cc
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\solar_sistem.cc
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\render.cc

cl /nologo /Zi /EHs /GR- /MDd -I ..\deps\includes\SDL2 /c ..\deps\includes\IMGUI\*.cpp

REM LINKER
cl /nologo /Zi /EHs /GR- /MDd /Fe:../bin/%name%.exe *.obj /link /SUBSYSTEM:CONSOLE ..\deps\libs\Win_SDL2\x86\SDL2.lib ..\deps\libs\Win_SDL2\x86\SDL2main.lib ..\deps\libs\Win_SDL2\x86\SDL2_TTF.lib opengl32.lib shell32.lib user32.lib gdi32.lib

@echo -----------------------------------------------------------------------
@echo  Proceso por lotes finalizado.
@echo -----------------------------------------------------------------------
pause
