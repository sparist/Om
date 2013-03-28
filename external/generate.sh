#!/bin/sh
set -e

Directory=`pwd -P`

cmake "$@" -P CMakeLists.txt "$Directory"

mkdir -p output/intermediate/Icu4c
cd output/intermediate/Icu4c

mkdir -p Release
cd Release
../../../../input/Icu4c/source/runConfigureICU MacOSX --enable-static --disable-shared --prefix="$Directory/output/artifacts/Icu4c" CPPFLAGS="-DU_CHARSET_IS_UTF8=1"
make -s
make -s install
cd ..

cd "$Directory"

cd input/Boost
./bootstrap.sh
./b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off define=U_CHARSET_IS_UTF8=1 -sICU_PATH="$Directory/output/artifacts/Icu4c" --build-dir="$Directory/output/intermediate/Boost" --prefix="$Directory/output/artifacts/Boost" --with-chrono --with-locale --with-system --with-thread --with-test link=static install
cd "$Directory"
