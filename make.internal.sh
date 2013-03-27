#!/bin/sh
set -e

Directory=`pwd -P`

mkdir -p output/projects/xcode
cd output/projects/xcode
cmake -G "Xcode" "$@" "$Directory"
cd "$Directory"
