#!/bin/sh
set -e

if [ ! -d "../../output/projects/xcode" ]; then
	echo The output/projects/xcode folder does not exist.  Please run make.sh.
	exit
fi

Directory=`pwd -P`
cd ../../output/projects/xcode
cmake ../../../input/internal
cd "$Directory"
