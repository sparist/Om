#!/bin/sh
set -e

if [ -d output/artifacts ]
then
	exit 0
fi

if [ $# -ne 1 ]
then
  echo Usage: $0 {ICU path}
  exit 1
fi

if [ ! -d "$1" ]
then
	echo The ICU directory was not found at "$1".
	exit 1
fi

Directory=`pwd -P`

cd "$1"
Icu=`pwd -P`
cd "$Directory"

cmake "$@" -P CMakeLists.txt "$Directory"

cd input
./bootstrap.sh
./b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off define=U_CHARSET_IS_UTF8=1 -sICU_PATH="$Icu" --build-dir="$Directory/output/intermediate" --prefix="$Directory/output/artifacts" --with-locale --with-system --with-thread --with-test link=static linkflags=-ldl install
cd "$Directory"
