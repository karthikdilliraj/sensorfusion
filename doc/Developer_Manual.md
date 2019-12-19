# Introduction

SensorFusion is a software that measures sensor data from different sensors in order to assure precise estimates of value. It applies the sensor fusion algorithm to calculate the fused output.

# Requirement

Software needs to calculate and store fused value provided by the algorithm for the input csv file which contains the sensor data from different sensors and timestamp.

# Assumption

- User can specify the range of valid sensor data to run the algorithm.
- User can specify the stuck time interval to calculate the fused output for a particular timeframe.
- User can specify the Parameter p and Support q value for the calculation.

# Program Flow

The program flow for the application is as follows:

![Diagram](https://github.com/karthikdilliraj/sensorfusion/blob/dev/assets/c.png)

- The main.c file calls the functions in sensor.c to run the alogorithm.
- The sensor.c file calls:
  - The functions in parsing_csv_file.c to parse the input from csv file
  - The functions in linked_list.c to store the sensor values.
  - The functions in calculate_fusion.c to compute the fused output from sensor values.
- The sensor.c file writes the fused output into the text file.

# Documentation

Complete documentation of the source code can be found [here](https://github.com/karthikdilliraj/sensorfusion/blob/dev/doc/html/index.html).
