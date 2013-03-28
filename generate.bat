@echo off
setlocal enableextensions

set Directory=%CD%

cd internal
call generate.bat --no-warn-unused-cli -D External:Path="%Directory%/external" -D Icu:Path="%Directory%/external/output/artifacts/Icu4c" -D Boost:Path="%Directory%/external/output/artifacts/Boost"
cd "%Directory%"
