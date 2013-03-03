@echo off
setlocal

if not exist products\projects\vs goto FolderDoesNotExist

set Directory=%CD%
cd products\projects\vs
cmake ..\..\..
if %ERRORLEVEL% neq	0 goto CMakeError
cd "%Directory%"
exit /b 0

:FolderDoesNotExist
echo The products\projects\vs folder does not exist.  Please run make.bat.
exit /b 1

:CMakeError
echo There was an error running CMake.  Please run make.bat.
cd "%Directory%"
exit /b 1
