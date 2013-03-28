@echo off
setlocal enableextensions

call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

set Directory=%CD%

cmake %* -P CMakeLists.txt "%Directory%"

for %%a in ("%Directory%") do set DirectoryShort=%%~sa
for /f "delims=" %%b in ('cygpath --unix "%DirectoryShort%"') do set DirectoryShortUnix=%%b

if not exist output\intermediate\Icu4c mkdir output\intermediate\Icu4c
cd output\intermediate\Icu4c

if not exist Debug mkdir Debug
cd Debug
bash ../../../../input/Icu4c/source/runConfigureICU --enable-debug --disable-release Cygwin/MSVC --enable-static --prefix=%DirectoryShortUnix%/output/artifacts/Icu4c
make -s
make -s install
cd ..

if not exist Release mkdir Release
cd Release
bash ../../../../input/Icu4c/source/runConfigureICU Cygwin/MSVC --enable-static --prefix=%DirectoryShortUnix%/output/artifacts/Icu4c
make -s
make -s install
cd ..

cd "%Directory%"

cd input\Boost
call .\bootstrap
call .\b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off define=U_STATIC_IMPLEMENTATION=1 -sICU_PATH="%Directory%\output\artifacts\Icu4c" --build-dir="%Directory%\output\intermediate\Boost" --prefix="%Directory%\output\artifacts\Boost" --hash --with-chrono --with-locale --with-system --with-thread --with-test link=static install
cd "%Directory%"
