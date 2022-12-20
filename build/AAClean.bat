title Cleaner
cls
@echo -----------------------------------------------------------------------
@echo  Eliminando objetos....
del .\*.obj *.pdb *.ilk *.ini
del ..\bin\*.obj ..\bin\*.pdb ..\bin\*.ilk ..\bin\*.ini
del ..\bin\*.vs ..\build\*.vs *.vs
@echo  Objetos eliminados
@echo -----------------------------------------------------------------------
