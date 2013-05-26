#!/bin/sh
set -e

if [ $# -ne 1 ]
then
  echo Usage: $0 {CMake Generator}
  exit 1
fi
Generator=$1

Directory=`pwd -P`

mkdir -p "output/intermediate/${Generator}"
cd "output/intermediate/${Generator}"
cmake -G "${Generator}" "$@" "$Directory"
cd "$Directory"
