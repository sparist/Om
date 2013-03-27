@echo off
setlocal enableextensions

call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

set Directory=%CD%

cd input\external
set ExternalDirectory=%CD%
for %%a in ("%ExternalDirectory%") do set ExternalDirectoryShort=%%~sa
for /f "delims=" %%b in ('cygpath --unix "%ExternalDirectoryShort%"') do set ExternalDirectoryShortUnix=%%b

if not exist output\intermediate\icu4c mkdir output\intermediate\icu4c
cd output\intermediate\icu4c

if not exist debug mkdir debug
cd debug
bash ../../../../input/icu4c/source/runConfigureICU --enable-debug --disable-release Cygwin/MSVC --enable-static --prefix=%ExternalDirectoryShortUnix%/output/artifacts/icu4c
make -s
make -s install
cd ..

if not exist release mkdir release
cd release
bash ../../../../input/icu4c/source/runConfigureICU Cygwin/MSVC --enable-static --prefix=%ExternalDirectoryShortUnix%/output/artifacts/icu4c
make -s
make -s install
cd ..

cd "%ExternalDirectory%"

cd input\boost
call .\bootstrap
call .\b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off define=U_STATIC_IMPLEMENTATION=1 -sICU_PATH="%ExternalDirectory%\output\artifacts\icu4c" --build-dir="%ExternalDirectory%\output\intermediate\boost" --prefix="%ExternalDirectory%\output\artifacts\boost" --hash --with-chrono --with-locale --with-system --with-thread --with-test link=static install
cd "%ExternalDirectory%"

cd "%Directory%"
