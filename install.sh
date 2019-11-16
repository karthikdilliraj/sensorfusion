#!/bin/bash

PARENT_DIR="$(pwd)"
mkdir -p lib

cd ./lib/

if ! [ -x "$(command -v gcc)" ]; then
	echo "Error: GCC is not installed." >&2
	echo "Please install GCC before continue!"
	exit 1
fi

if ! [ -x "$(command -v make)" ]; then
	echo "Error: GNU Make is not installed." >&2
	echo "Please install GNU make before continue!"
	exit 1
fi

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

case "$(uname -s)" in
	CYGWIN*|MINGW32*|MINGW64*|MSYS*)
		echo "Configuring PATH for CYGWIN"
		echo 'export PATH='"$CUR_DIR/gsl/bin"':$PATH'  >> ~/.bashrc
		source ~/.bashrc
		;;
	Darwin)
		echo 'Mac OS X'
		echo "Configuring LD_LIBRARY_PATH for MACOS"
		echo 'export LD_LIBRARY_PATH='"$CUR_DIR/gsl/lib"  >> ~/.bashrc
		source ~/.bashrc
		;;
	Linux)
		echo 'Linux'
		echo "Configuring LD_LIBRARY_PATH for Ubuntu"
		echo 'export LD_LIBRARY_PATH='"$CUR_DIR/gsl/lib"  >> ~/.bashrc
		source ~/.bashrc
		;;
	*)
		echo "Other OS. Skip"
		;;
esac

cd $PARENT_DIR
