#!/bin/sh
set -e

if [ $# -lt 1 ]
then
	echo Usage: $0 \"Project name\" [CMake arguments...]
	exit 1
fi

Builds=`pwd -P`
Build="$Builds/Om"

cd `dirname "$0"`
Source=`pwd -P`

Project="$Build/projects/$1"
mkdir -p "$Project"
cd "$Project"
cmake --no-warn-unused-cli -D Builds="$Builds" -D Build="$Build" -D Project="$@" "$Source"

cd "$Builds"
