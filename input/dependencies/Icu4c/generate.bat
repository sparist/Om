@echo off
setlocal enableextensions

if exist output\artifacts goto :EOF

call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

set Directory=%CD%

cmake %* -P CMakeLists.txt "%Directory%"

for %%a in ("%Directory%") do set DirectoryShort=%%~sa
for /f "delims=" %%b in ('cygpath --unix "%DirectoryShort%"') do set DirectoryShortUnix=%%b

if not exist output\intermediate mkdir output\intermediate
cd output\intermediate

if not exist Debug mkdir Debug
cd Debug
bash ../../../input/source/runConfigureICU --enable-debug --disable-release Cygwin/MSVC --enable-static --prefix=%DirectoryShortUnix%/output/artifacts
make -s
make -s install
cd ..

if not exist Release mkdir Release
cd Release
bash ../../../input/source/runConfigureICU Cygwin/MSVC --enable-static --prefix=%DirectoryShortUnix%/output/artifacts
make -s
make -s install
cd ..

cd "%Directory%"
