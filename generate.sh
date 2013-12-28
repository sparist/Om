#!/bin/sh
set -e

if [ $# -lt 1 ]
then
	echo Usage: $0 \"Project name\" [CMake arguments...]
	exit 1
fi

BuildsDirectory=`pwd -P`
BuildDirectory="$BuildsDirectory/Om"

cd `dirname "$0"`
SourceDirectory=`pwd -P`

ProjectDirectory="$BuildDirectory/projects/$1"
mkdir -p "$ProjectDirectory"
cd "$ProjectDirectory"
cmake --no-warn-unused-cli -D BuildsDirectory="$BuildsDirectory" -D BuildDirectory="$BuildDirectory" -D ProjectDirectory="$@" "$SourceDirectory"

cd "$BuildsDirectory"
