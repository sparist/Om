#!/bin/sh

Directory=`pwd -P`

if [ $# -lt 2 ] || [ $# -gt 3 ]
then
  echo "Usage: $0 \"ICU path\" \"Boost path\" [\"UnitTest++ path\"]"
  exit
fi

cd $1
Icu=`pwd -P`
if [ ! -d "build" ]
then
	mkdir -p build
	mkdir -p make
	cd make
	../source/runConfigureICU MacOSX --enable-static --disable-shared --prefix="$Icu/build"
	make check
	make install
fi
cd "$Directory"

cd $2
Boost=`pwd -P`
if [ ! -d "build" ]
then
	./bootstrap.sh --with-icu="$Icu/build" --prefix="$Boost/build"
	./b2 boost.locale.iconv=off -sICU_PATH="$Icu/build" --with-chrono --with-locale --with-system --with-thread link=static install
fi
cd "$Directory"

if [ $# -eq 3 ]
then
	cd $3
	UnitTest=`pwd -P`
	if [ ! -f libUnitTest++.a ]
	then
		make all
	fi
	cd "$Directory"
fi

mkdir -p products/xcode
cd products/xcode
cmake -G "Xcode" -D Icu:PATH="$Icu/build" -D Boost:PATH="$Boost/build" -D UnitTest:PATH="$UnitTest" ../..
cd "$Directory"
