#!/bin/sh
set -e

if [ -d output/artifacts ]
then
	exit 0
fi

Directory=`pwd -P`

cmake "$@" -P CMakeLists.txt "$Directory"

mkdir -p output/intermediate
cd output/intermediate

mkdir -p Release
cd Release
../../../input/source/runConfigureICU MacOSX --enable-static --disable-shared --prefix="$Directory/output/artifacts" CPPFLAGS=-DU_CHARSET_IS_UTF8=1
make -s
make -s install
cd ..

cd "$Directory"
