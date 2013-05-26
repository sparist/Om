@echo off
setlocal enableextensions

set argC=0
for %%x in (%*) do Set /A argC+=1
if not %argC% == 1 (
	echo Usage: %0 {CMake Generator}
	exit /b 1
)
set Generator=%1

set Directory=%CD%

if not exist "output\intermediate\%Generator%" mkdir "output\intermediate\%Generator%"
cd "output\intermediate\%Generator%"
cmake -G "%Generator%" %* "%Directory%"
cd "%Directory%"
