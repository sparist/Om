@echo off

set argC=0
for %%x in (%*) do Set /A argC+=1
if %argC% lss 2 goto Usage
if %argc% gtr 3 goto Usage

set OldDirectory=%CD%
set OldPath=%PATH%
call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cd %1
set Icu=%CD%
set PATH=%Icu%\bin\;%PATH%
msbuild "source\allinone\allinone.sln" /p:Configuration=Debug
msbuild "source\allinone\allinone.sln" /p:Configuration=Release
REM call "source\allinone\icucheck.bat" %PROCESSOR_ARCHITECTURE% Release
cd "%OldDirectory%"

cd %2
set Boost=%CD%
call .\bootstrap --with-icu="%Icu%" --prefix="%Boost%\build"
call .\b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off -sICU_PATH="%Icu%" --with-chrono --with-locale --with-system --with-thread link=static install --prefix="%Boost%\build"
cd "%OldDirectory%"

if %argC% lss 3 goto :Finish
cd %3
set UnitTest=%CD%
msbuild "UnitTest++.vsnet2010.sln" /p:Configuration=Debug
msbuild "UnitTest++.vsnet2010.sln" /p:Configuration=Release
cd "%OldDirectory%"

:Finish
mkdir products
cd products
mkdir projects
cd projects
mkdir vs
cd vs
cmake -G "Visual Studio 10" -D Icu:PATH="%Icu%" -D Boost:PATH="%Boost%\build" -D UnitTest:PATH="%UnitTest%" ..\..\..
cd "%OldDirectory%"
set PATH=%OldPath%
exit /b 0

:Usage
echo Usage: %0 "ICU path" "Boost path" ["UnitTest++ path"]
exit /b 1
