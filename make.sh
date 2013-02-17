#!/bin/sh

Directory=`pwd -P`

if [ $# -lt 2 ] || [ $# -gt 3 ]
then
  echo "Usage: $0 \"ICU path\" \"Boost path\" [\"UnitTest++ path\"]"
  exit
fi

cd $1
Icu=`pwd -P`
cd "$Directory"

cd $2
Boost=`pwd -P`
cd "$Directory"

if [ $# -eq 3 ]
then
	cd $3
	UnitTest=`pwd -P`
	cd "$Directory"
fi

mkdir -p products/projects/xcode
cd products/projects/xcode
cmake -G "Xcode" -D Icu:PATH="$Icu/build" -D Boost:PATH="$Boost/build" -D UnitTest:PATH="$UnitTest" ../../..
cd "$Directory"
