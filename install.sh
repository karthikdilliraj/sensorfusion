#!/bin/bash
mkdir -p ./lib

cd ./lib/

if [ -n "$(ls -A gsl-2.6.tar.gz 2>/dev/null)" ]
then
  echo "Already download GSL library!"
else
	echo "===== Download GSL library ======"

	if ! [ -x "$(command -v curl)" ]; then
  		echo "Error: curl is not installed." >&2
  		if ! [ -x "$(command -v wget)" ]; then
  			echo "Error: wget is not installed." >&2
  			echo "Please install wget or curl to continue!"
  			echo "NOTE:"
  			echo -e "\tYou can also download GSL package from ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz into lib directory."
  			exit 1
  		else
  			echo "===== Downloading using wget ======"
  			wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz 
  		fi
  	else
  		echo "===== Downloading using curl ======"
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
