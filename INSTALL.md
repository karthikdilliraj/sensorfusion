# Installation

## Supported Platforms:

Unix, Cygwin and MacOS.

## Prerequisite

GCC Compiler, GNU make, download ultilities such as wget or curl.

## Dependency Library

To run the project, you have to install the [GSL](https://www.gnu.org/software/gsl/doc/html/index.html#) library

Note that during the installation, GSL will be installed in `lib` directory. To start automatically install process, please the follwing command:

```
./install.sh
```

Execute below command to append GSL library into PATH environment:

```
source ~/.bashrc
```

## Build Project:

```
make
```

Excutable binary sensorfusion file will be placed at `bin` directory.
