#!/bin/sh

Directory=`pwd -P`

if [ $# -lt 2 ] || [ $# -gt 2 ]
then
  echo "Usage: $0 \"ICU path\" \"Boost path\""
  exit
fi

if [ ! -d "$1" ]
then
	echo "The ICU directory was not found at \"$1\"."
	exit
fi
if [ ! -d "$2" ]
then
	echo "The Boost directory was not found at \"$2\"."
	exit
fi

cd "$1"
Icu=`pwd -P`
cd "$Directory"

cd "$2"
Boost=`pwd -P`
cd "$Directory"

mkdir -p products/projects/xcode
cd products/projects/xcode
cmake -G "Xcode" -D Icu:PATH="$Icu/build" -D Boost:PATH="$Boost/build" ../../..
cd "$Directory"
