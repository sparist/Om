#!/bin/sh
set -e

Directory=`pwd -P`

Generator=Xcode

mkdir -p "output/intermediate/${Generator}"
cd "output/intermediate/${Generator}"
cmake -G "${Generator}" "$@" "$Directory"
cd "$Directory"
