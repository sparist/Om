#!/bin/sh
set -e

if [ $# -lt 1 ]
then
	echo Usage: $0 \"Project name\" [CMake arguments...]
	exit 1
fi

Build=`pwd -P`

cd `dirname "$0"`
Source=`pwd -P`

Project="$Build/projects/$1"
mkdir -p "$Project"
cd "$Project"
cmake --no-warn-unused-cli -D Project="$@" "$Source"

cd "$Builds"
