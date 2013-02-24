@echo off

set argC=0
for %%x in (%*) do Set /A argC+=1
if %argC% lss 2 goto Usage
if %argc% gtr 2 goto Usage

set OldDirectory=%CD%
set OldPath=%PATH%
call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cd %1
set Icu=%CD%
set PATH=%Icu%\bin\;%PATH%
msbuild "source\allinone\allinone.sln" /p:Configuration=Debug
msbuild "source\allinone\allinone.sln" /p:Configuration=Release
call "source\allinone\icucheck.bat" %PROCESSOR_ARCHITECTURE% Release
set PATH=%OldPath%
cd "%OldDirectory%"

cd %2
set Boost=%CD%
call .\bootstrap --with-icu="%Icu%" --prefix="%Boost%\build"
call .\b2 boost.locale.icu=on boost.locale.std=off -sICU_PATH="%Icu%" --with-chrono --with-locale --with-system --with-thread --with-test link=static install --prefix="%Boost%\build"
cd "%OldDirectory%"

exit /b 0

:Usage
echo Usage: %0 "ICU path" "Boost path"
exit /b 1
