@echo off
setlocal enableextensions

set Directory=%CD%

if not exist output\projects\vs mkdir output\projects\vs
cd output\projects\vs
cmake -G "Visual Studio 10" %* "%Directory%"
cd "%Directory%"
