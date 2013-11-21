#!/bin/sh
set -e

if [ $# -lt 1 ]
then
	echo Usage: $0 \"Generator\" [CMake arguments...]
	exit 1
fi

Directory=`pwd -P`

mkdir -p "../output/projects/$1"
cd "../output/projects/$1"
cmake --no-warn-unused-cli -D Project="$@" "$Directory"
cd "$Directory"
