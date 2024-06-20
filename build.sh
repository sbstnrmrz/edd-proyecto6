#!/bin/bash

CC="clang++"
CCFLAGS="-Wall -Wextra"
IDIR="/usr/local/include"
LDIR="/usr/local/lib"
LIBS="-lm"
SRC="*.cpp"
RPATH=""
BAT="set SRC=$SRC\n
set CC=g++\n
set CFLAGS=$CCFLAGS\n
set IDIR=C:/msys64/ucrt64/include\n
set LDIR=C:/msys64/ucrt64/lib\n
set SRC=$SRC\n
set LIBS=$LIBS\n
%CC% %CFLAGS% %SRC% -o main -I%IDIR% -L%LDIR% %LIBS%"

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

echo -e $BAT > build_win.bat 

$CC $CCFLAGS $SRC -o main -I$IDIR -L$LDIR $LIBS $RPATH 
