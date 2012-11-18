#!/bin/sh

Directory=`pwd -P`

if [ ! -d "products/xcode" ]; then
	echo The products/xcode folder does not exist.  Please run make.sh.
	exit
fi
cd products/xcode
cmake ../..
cd "$Directory"
