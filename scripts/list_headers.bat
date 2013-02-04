@echo off
cd code
set HEADER=%CD%\om.inc
del HEADER
for /r %i in (*) do @echo "#include ""%~nxi""" >> %HEADER%
cd ..
exit /b 0
