@echo Launch building!
cd temp\
cmake cd %~dp0 -G"Borland Makefiles"
make
copy /N XMLpars.exe %~dp0XMLpars.exe
cd ..