#!/bin/bash

mkdir -p lib
cd ./lib/

if [ -n "$(ls -A gsl-2.6.tar.gz 2>/dev/null)" ]
then
  echo "Already download GSL library!"
else
	echo "===== Download GSL library ======"
	if [ "$(uname)" == "Darwin" ]; then
	    # Do something under Mac OS X platform
	    echo "This is Mac system"
	    wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz
	elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
	    # Do something under GNU/Linux platform
	    echo "This is Linux system"
	    wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz 
	elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
	    # Do something under 32 bits Windows NT platform
	    echo "This is Windows32 system"
	    curl ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz -o gsl-2.6.tar.gz
	elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
	    # Do something under 64 bits Windows NT platform
	    echo "This is Windows64 system"
	    curl ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz -o gsl-2.6.tar.gz
	fi
fi

echo echo "===== Untar GSL library ======"
tar -zxvf gsl-2.6.tar.gz

echo "===== Build GSL ======"

mkdir -p ./gsl

CUR_DIR="$(pwd)"
echo "Will Install Library to $CUR_DIR/gsl"

cd ./gsl-2.6
./configure --prefix=$CUR_DIR/gsl
make
make install

echo "===== Build GSL. Done! ======"




