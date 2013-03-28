@echo off
setlocal enableextensions

set Directory=%CD%

set Generator=Visual Studio 10

if not exist "output\intermediate\%Generator%" mkdir "output\intermediate\%Generator%"
cd "output\intermediate\%Generator%"
cmake -G "%Generator%" %* "%Directory%"
cd "%Directory%"
