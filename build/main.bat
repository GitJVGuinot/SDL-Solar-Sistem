@echo off

title Compiler
set "name=%~n0"

REM Compiler & Linker with graphic libs
@cls
@echo -----------------------------------------------------------------------
@echo  ESAT Curso 2022-2023 Asignatura PRG Primero
@echo -----------------------------------------------------------------------
@echo  Debug compiler Start
@echo -----------------------------------------------------------------------
@echo  Deleting some objects....
del .\*.obj *.pdb *.ilk
@echo  Objects deleted
@echo -----------------------------------------------------------------------

REM COMPILER
  cl /nologo /Zi /EHs /GR- /MDd /W4 -I ..\deps\includes\SDL2 /c ..\deps\includes\IMGUI\*.cpp

  cl /nologo /Zi /EHs /GR- /MDd /W4 /c ..\deps\includes\Obj_Loader\*.cpp

  cl /nologo /Zi /EHs /GR- /MDd ^
  -I ..\includes ^
  -I ..\deps\includes ^
  -I ..\deps\includes\IMGUI ^
  -I ..\deps\includes\SDL2 ^
  /c ..\src\*.cc

 REM LINKER
  set "SDL2_Lib=..\deps\libs\Win_SDL2\x86\SDL2.lib"
  set "SDL2main_Lib=..\deps\libs\Win_SDL2\x86\SDL2main.lib"
  set "SDL2ttf_Lib=..\deps\libs\Win_SDL2\x86\SDL2_ttf.lib"
  set "SDL2image_Lib=..\deps\libs\Win_SDL2\x86\SDL2_image.lib"
  set "SDL2mixer_Lib=..\deps\libs\Win_SDL2\x86\SDL2_mixer.lib"
  set "My_Window_Lib=..\deps\libs\Win_own\my_window.lib"
  set "Libs=%SDL2_Lib% %SDL2main_Lib% %SDL2ttf_Lib% %SDL2image_lib% %SDL2mixer_lib% %My_Window_Lib%"

  cl /nologo /Zi /EHs /GR- /MDd /Fe:../bin/%name%_debug.exe *.obj /link /SUBSYSTEM:CONSOLE %Libs% opengl32.lib shell32.lib user32.lib gdi32.lib

@echo -----------------------------------------------------------------------
@echo  Debug Compiler Finish
@echo -----------------------------------------------------------------------
@echo  Release compiler Start
@echo -----------------------------------------------------------------------
@echo  Deleting some objects....
del .\*.obj *.pdb *.ilk
@echo  Objects deleted
@echo -----------------------------------------------------------------------

REM COMPILER
  cl /nologo /O2 /EHs /GR- /MT /W4 -I ..\deps\includes\SDL2 /c ..\deps\includes\IMGUI\*.cpp

  cl /nologo /O2 /EHs /GR- /MT /W4 /c ..\deps\includes\Obj_Loader\*.cpp

  cl /nologo /O2 /EHs /GR- /MT ^
  -I ..\includes ^
  -I ..\deps\includes ^
  -I ..\deps\includes\IMGUI ^
  -I ..\deps\includes\SDL2 ^
  /c ..\src\*.cc

 REM LINKER
  set "SDL2_Lib=..\deps\libs\Win_SDL2\x86\SDL2.lib"
  set "SDL2main_Lib=..\deps\libs\Win_SDL2\x86\SDL2main.lib"
  set "SDL2ttf_Lib=..\deps\libs\Win_SDL2\x86\SDL2_ttf.lib"
  set "SDL2image_Lib=..\deps\libs\Win_SDL2\x86\SDL2_image.lib"
  set "SDL2mixer_Lib=..\deps\libs\Win_SDL2\x86\SDL2_mixer.lib"
  set "My_Window_Lib=..\deps\libs\Win_own\my_window_release.lib"
  set "Libs=%SDL2_Lib% %SDL2main_Lib% %SDL2ttf_Lib% %SDL2image_lib% %SDL2mixer_lib% %My_Window_Lib%"

  cl /nologo /O2 /EHs /GR- /MT /Fe:../bin/%name%.exe *.obj /link /SUBSYSTEM:CONSOLE %Libs% opengl32.lib shell32.lib user32.lib gdi32.lib

  @echo -----------------------------------------------------------------------
  @echo  Release compiler Finish
  @echo -----------------------------------------------------------------------
