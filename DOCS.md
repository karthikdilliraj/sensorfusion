# Introduction

SensorFusion is a software that measures sensor data from different sensors in order to assure precise estimates of value. It applies the sensor fusion algorithm to calculate the fused output.

# Installation

Please refer to INSTALL.md file for installation instructions.

# Usage

The user needs to input the software with a csv file containing the sensor values taken at different time from differnt sensors.

The following parameters are to be given along with the execution file sensorfusion:

- Lower Limit Value (-l) : Specifies the lower limit below which the sensor will be marked out of range.

- Upper Limit Value (-u) : Specifies the upper limit above which the sensor will be marked out of range.

- Stuck Time Interval (-s) : Specifies how long (in minutes) beyond which, the sensor is considered to be stuck, and no longer valid.

- Input file path location (-f) : Specifies a input filepath.

Example:

The below command will conduct sensor fusion algorithm with Stuck Time Interval is 10 minutes with sensor values range from 1 to 10. The data is get from sensor_fusion_input.csv

```
./sensorfusion -s 10 -l 1 -u 10 -f ./sensor_fusion_input.csv
```

# Testing

Unit testing is done for each functions defined in the software. The test cases can be run using the command below:

```
./sensorfusion -t
```

# Report Generation

Report will be generated after running the sensorfusion execution file. The report provides the fused output values for each time interval and also the statistics about the status of the sensor, whether it is valid or stuck.
