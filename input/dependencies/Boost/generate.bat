@echo off
setlocal enableextensions

if exist output\artifacts goto :EOF

set argC=0
for %%x in (%*) do Set /A argC+=1
if not %argC% == 1 (
	echo Usage: %0 {ICU path}
	exit /b 1
)

if not exist %1 (
	echo The ICU directory was not found at %1.
	exit /b 1
)

set Directory=%CD%

cd %1
set Icu=%CD%
cd "%Directory%"

call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cmake %* -P CMakeLists.txt "%Directory%"

cd input
call .\bootstrap
call .\b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off define=U_STATIC_IMPLEMENTATION=1 -sICU_PATH="%Icu%" --build-dir="%Directory%\output\intermediate" --prefix="%Directory%\output\artifacts" --hash --with-locale --with-system --with-thread --with-test link=static install
cd "%Directory%"
