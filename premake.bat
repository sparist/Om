@echo off

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
for %%y in ("%Icu%") do set IcuShort=%%~sy
for /f "delims=" %%a in ('cygpath --unix "%IcuShort%"') do set IcuShortUnix=%%a
mkdir build
mkdir make
cd make
mkdir debug
cd debug
bash ../../source/runConfigureICU --enable-debug --disable-release Cygwin/MSVC --enable-static --prefix="%IcuShortUnix%/build"
make
make install
cd ..
mkdir release
cd release
bash ../../source/runConfigureICU Cygwin/MSVC --enable-static --prefix="%IcuShortUnix%/build"
make
make install
cd "%Directory%"

cd %2
set Boost=%CD%
call .\bootstrap --with-icu="%Icu%\build" --prefix="%Boost%\build"
call .\b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off boost.locale.winapi=off boost.locale.posix=off define=U_STATIC_IMPLEMENTATION=1 -sICU_PATH="%Icu%\build" --hash --with-chrono --with-locale --with-system --with-thread --with-test link=static install --prefix="%Boost%\build"
cd "%Directory%"

exit /b 0

:Usage
echo Usage: %0 "ICU path" "Boost path"
exit /b 1

:IcuMissing
echo The ICU directory was not found at "%1".
exit /b 1

:BoostMissing
echo The Boost directory was not found at "%2".
exit /b 1
