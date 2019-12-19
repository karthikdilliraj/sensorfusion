# SensorFusion

SensorFusion is a software that measures sensor data from different sensors in order to assure precise estimates of value.

SensorFusion implements the algorithm described in:

G. Hongyan, “A simple multi-sensor data fusion algorithm based on principal component analysis,” in 2009 ISECS International Colloquium on Computing, Communication, Control, and Management, Sanya, China, 2009, pp. 423–426.

# Authors

- Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca - Carleton University
- Nhat Hieu Le - nhathieule@cmail.carleton.ca - Carleton University
- Jason Miller - jasonmiller@cmail.carleton.ca - Carleton University

# Installation

Installation steps are mentioned in [INSTALL.md](https://github.com/karthikdilliraj/sensorfusion/blob/dev/INSTALL.md)

# Usage

To run, you must first install it. Then you can follow instructions mentioned in
[User_Manual.md](https://github.com/karthikdilliraj/sensorfusion/blob/dev/doc/User_Manual.md).

# File Structure

The correct file structure (after installing GSL library should be follow and run the binary)

```
├── DOCS.md 	-> Usage file
├── INSTALL.md 	-> Installation Guide
├── LICENSE 	-> License file
├── Makefile 	-> Makefile
├── README.md 	-> Readme file
├── bin 	-> Binary directory
├── doc
│   └── html 	-> Doxygen document
├── include 	-> Header files
│   ├── calculate_fusion.h
│   ├── linked_list.h
│   ├── parsing_csv_file.h
│   └── sensor.h
├── install.sh 	-> Installation script
├── lib
│   ├── gsl 	-> GSL binary
│   └── gsl-2.6 	-> GSL source
├── obj 	-> Object files
├── sensor_fusion_config 	-> Doxygen Configuration files
├── sensor_fusion_report.txt 	-> Report data
├── src 	-> Source files for sensorfusion
│   ├── calculate_fusion.c
│   ├── input.csv 	-> Input raw data
│   ├── linked_list.c
│   ├── main.c
│   ├── parsing_csv_file.c
│   └── sensor.c
└── test
    ├── include		-> Header file for unittest
    │   └── test.h
    ├── input_test.csv 	-> Test data
    └── test.c
```

# For Developers

The developer manual is available [here](https://github.com/karthikdilliraj/sensorfusion/blob/dev/doc/Developer_Manual.md).

# License

This project is licensed under the GPL 2.0 License - see the LICENSE.md file for details

# Acknowledgements

Thank to Dr. Cristina Ruiz Martin for providing guidance on how to develop the software.
