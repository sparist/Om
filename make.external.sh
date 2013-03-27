#!/bin/sh
set -e

Directory=`pwd -P`

cd input/external
ExternalDirectory=`pwd -P`

mkdir -p output/intermediate/icu4c
cd output/intermediate/icu4c
../../../input/icu4c/source/runConfigureICU MacOSX --enable-static --disable-shared --prefix="$ExternalDirectory/output/artifacts/icu4c" CPPFLAGS="-DU_CHARSET_IS_UTF8=1"
make -s
make -s install
cd "$ExternalDirectory"

cd input/boost
./bootstrap.sh
./b2 boost.locale.icu=on boost.locale.std=off boost.locale.iconv=off define=U_CHARSET_IS_UTF8=1 -sICU_PATH="$ExternalDirectory/output/artifacts/icu4c" --build-dir="$ExternalDirectory/output/intermediate/boost" --prefix="$ExternalDirectory/output/artifacts/boost" --with-chrono --with-locale --with-system --with-thread --with-test link=static install
cd "$ExternalDirectory"

cd "$Directory"
