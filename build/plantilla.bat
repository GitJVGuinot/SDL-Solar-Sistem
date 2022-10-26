@echo off

pushd "%VS160COMNTOOLS%"\..\..\VC\Auxiliary\Build\vcvarsall.bat x86
popd

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
cl /nologo /Zi /EHs /GR- /MDd -I ..\includes -I ..\deps\includes /c ..\src\*.cc

REM LINKER
cl /nologo /Zi /EHs /GR- /MDd /Fe:%name%.exe *.obj /link /SUBSYSTEM:CONSOLE ..\deps\libs\Win_SDL2\x86\SDL2.lib ..\deps\libs\Win_SDL2\x86\SDL2main.lib ..\deps\libs\Win_SDL2\x86\SDL2_TTF.lib opengl32.lib shell32.lib user32.lib gdi32.lib

@echo -----------------------------------------------------------------------
@echo  Proceso por lotes finalizado.
@echo -----------------------------------------------------------------------

pause
