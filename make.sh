#!/bin/sh

Directory=`pwd -P`

if [ $# -lt 2 ] || [ $# -gt 2 ]
then
  echo "Usage: $0 \"ICU path\" \"Boost path\""
  exit
fi

cd $1
Icu=`pwd -P`
cd "$Directory"

cd $2
Boost=`pwd -P`
cd "$Directory"

mkdir -p products/projects/xcode
cd products/projects/xcode
cmake -G "Xcode" -D Icu:PATH="$Icu/build" -D Boost:PATH="$Boost/build" ../../..
cd "$Directory"
