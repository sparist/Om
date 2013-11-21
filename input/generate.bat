@echo off
setLocal enableExtensions

set argC=0
for %%x in (%*) do set /A argC+=1
if %argC% lss 1 (
	echo Usage: %0 "Project" [CMake arguments...]
	exit /b 1
)

set Directory=%CD%

if not exist "..\output\projects\%~1" mkdir "..\output\projects\%~1"
cd "..\output\projects\%~1"
cmake --no-warn-unused-cli -D Project=%* "%Directory%"
cd "%Directory%"
