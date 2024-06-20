set SRC=*.cpp
 set CC=g++
 set CFLAGS=-Wall -Wextra
 set IDIR=C:/msys64/ucrt64/include
 set LDIR=C:/msys64/ucrt64/lib
 set SRC=*.cpp
 set LIBS=-lm
 %CC% %CFLAGS% %SRC% -o main -I%IDIR% -L%LDIR% %LIBS%
