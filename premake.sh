#!/bin/sh

Directory=`pwd -P`

if [ $# -lt 2 ] || [ $# -gt 2 ]
then
  echo "Usage: $0 \"ICU path\" \"Boost path\""
  exit
fi

if [ ! -d "$1" ]
then
	echo "The ICU directory was not found at \"$1\"."
	exit
fi
if [ ! -d "$2" ]
then
	echo "The Boost directory was not found at \"$2\"."
	exit
fi

cd "$1"
Icu=`pwd -P`
mkdir -p build
mkdir -p make
cd make
../source/runConfigureICU MacOSX --enable-static --disable-shared --prefix="$Icu/build"
make
make install
cd "$Directory"

cd "$2"
Boost=`pwd -P`
./bootstrap.sh --with-icu="$Icu/build" --prefix="$Boost/build"
./b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off -sICU_PATH="$Icu/build" --with-chrono --with-locale --with-system --with-thread --with-test link=static install --prefix="$Boost/build"
cd "$Directory"
