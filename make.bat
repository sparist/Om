@echo off
setlocal

set argC=0
for %%x in (%*) do Set /A argC+=1
if %argC% lss 2 goto Usage
if %argc% gtr 2 goto Usage

if not exist %1 goto IcuMissing
if not exist %2 goto BoostMissing

set Directory=%CD%
call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cd %1
set Icu=%CD%
cd "%Directory%"

cd %2
set Boost=%CD%
cd "%Directory%"

mkdir products
cd products
mkdir projects
cd projects
mkdir vs
cd vs
cmake -G "Visual Studio 10" -D Icu:PATH="%Icu%\build" -D Boost:PATH="%Boost%\build" ..\..\..
cd "%Directory%"
exit /b 0

:Usage
echo Usage: %0 "ICU path" "Boost path"
exit /b 1

:IcuMissing
echo The ICU directory was not found at %1.
exit /b 1

:BoostMissing
echo The Boost directory was not found at %2.
exit /b 1
