@echo off
setLocal enableExtensions

set argC=0
for %%x in (%*) do set /A argC+=1
if %argC% lss 1 (
	echo Usage: %0 "Project name" [CMake arguments...]
	exit /b 1
)

set Builds=%CD%
set Build=%Builds%\Om

set Source=%~dp0
if %Source:~-1%==\ set Source=%Source:~0,-1%

set Project=%Build%\projects\%~1
if not exist "%Project%" mkdir "%Project%"
cd "%Project%"
cmake --no-warn-unused-cli -D Builds="%Builds%" -D Build="%Build%" -D Project=%* "%Source%"

cd "%Builds%"
