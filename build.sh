#!/bin/bash

CC="clang++"
CCFLAGS="-Wall -Wextra"
IDIR="/usr/local/include"
LDIR="/usr/local/lib"
LIBS="-lm -lSDL3 -lSDL3_image -lSDL3_ttf"
SRC="*.cpp"
RPATH=""
BAT="set SRC=$SRC
set CC=g++
set CFLAGS=$CCFLAGS
set IDIR=C:/msys64/ucrt64/include
set LDIR=C:/msys64/ucrt64/lib
set SRC=$SRC
set LIBS=$LIBS"

echo $BAT >> build_win.bat 

if [ `uname` = "Darwin" ]; then
    RPATH+="-rpath $LDIR"
fi

if [ `uname` = "Linux" ]; then
    LIBS+=" -lpthread -ldl"
fi

if ! test -f build_win.bat; then
    echo "build_win.bat created!"
    touch build_win.bat 
fi

$CC $CCFLAGS $SRC -o main -I$IDIR -L$LDIR $LIBS $RPATH 
