#!/bin/sh

if [ ! -d "products/projects/xcode" ]; then
	echo The products/projects/xcode folder does not exist.  Please run make.sh.
	exit
fi

Directory=`pwd -P`
cd products/projects/xcode
cmake ../../..
cd "$Directory"
