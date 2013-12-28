@echo off
setLocal enableExtensions

set argC=0
for %%x in (%*) do set /A argC+=1
if %argC% lss 1 (
	echo Usage: %0 "Project name" [CMake arguments...]
	exit /b 1
)

set BuildsDirectory=%CD%
set BuildDirectory=%BuildsDirectory%\Om

set SourceDirectory=%~dp0
if %SourceDirectory:~-1%==\ set SourceDirectory=%SourceDirectory:~0,-1%

set ProjectDirectory=%BuildDirectory%\projects\%~1
if not exist "%ProjectDirectory%" mkdir "%ProjectDirectory%"
cd "%ProjectDirectory%"
cmake --no-warn-unused-cli -D BuildsDirectory="%BuildsDirectory%" -D BuildDirectory="%BuildDirectory%" -D ProjectDirectory=%* "%SourceDirectory%"

cd "%BuildsDirectory%"
