@echo off

set argC=0
for %%x in (%*) do Set /A argC+=1
if %argC% lss 2 goto Usage
if %argc% gtr 2 goto Usage

set OldDirectory=%CD%
call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cd %1
set Icu=%CD%
cd "%OldDirectory%"

cd %2
set Boost=%CD%
cd "%OldDirectory%"

mkdir products
cd products
mkdir projects
cd projects
mkdir vs
cd vs
cmake -G "Visual Studio 10" -D Icu:PATH="%Icu%" -D Boost:PATH="%Boost%\build" ..\..\..
cd "%OldDirectory%"
exit /b 0

:Usage
echo Usage: %0 "ICU path" "Boost path"
exit /b 1
