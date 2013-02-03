#!/bin/sh

Directory=`pwd -P`

if [ ! -d "products/projects/xcode" ]; then
	echo The products/projects/xcode folder does not exist.  Please run make.sh.
	exit
fi
cd products/projects/xcode
cmake ../../..
cd "$Directory"
