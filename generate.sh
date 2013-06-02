#!/bin/sh
set -e

if [ $# -lt 1 ]
then
	echo Usage: $0 \"CMake generator\" [Additional CMake arguments...]
	exit 1
fi
Generator=$1

Directory=`pwd -P`

mkdir -p "output/intermediate/${Generator}"
cd "output/intermediate/${Generator}"
cmake -G "$@" "$Directory"
cd "$Directory"
