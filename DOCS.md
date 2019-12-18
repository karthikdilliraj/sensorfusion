# Introduction

SensorFusion is a software that measures sensor data from different sensors in order to assure precise estimates of value. It applies the sensor fusion algorithm to calculate the fused output.

# Installation

Please refer to [INSTALL.md](https://github.com/karthikdilliraj/sensorfusion/blob/dev/INSTALL.md) file for installation instructions.

# Usage

The user needs to input the software with a csv file containing the sensor values taken at different time from differnt sensors.

The following parameters are to be given along with the execution file sensorfusion:

- Lower Limit Value (-l) : Specifies the lower limit below which the sensor will be marked out of range.

- Upper Limit Value (-u) : Specifies the upper limit above which the sensor will be marked out of range.

- Stuck Time Interval (-s) : Specifies how long (in minutes) beyond which, the sensor is considered to be stuck, and no longer valid.

- Input file path location (-f) : Specifies a input filepath.

- Parameter (-p) : Specifies the ratio (in %) used to determine how many principle components are to be used.

- Support (-q) : Specifies the percentage of (in %) sensors that must agree before a sensor value is considered valid.

Example:

The below command will conduct sensor fusion algorithm with Stuck Time Interval as 10 minutes with sensor values range from 1 to 10. The data input is from sensor_fusion_input.csv file, Parameter p is set to 50% and Support q is 70%.

Please note that the binary is located within `bin` folder

```
./bin/sensorfusion -s 10 -l 1 -u 10 -p 50 -q 70 -f ./sensor_fusion_input.csv
```

# Testing

Unit testing is done for each functions defined in the software. The test cases can be run using the command below:

```
./bin/sensorfusion -t
```

# Help

User can run the below command to know the details about input parameters.

```
./bin/sensorfusion -h
```

# Report Generation

Report will be generated after running the sensorfusion execution file. The report provides the fused output values for each time interval and also the statistics about the status of the sensor, whether it is valid or stuck.

Report is saved as `sensor_fusion_report.txt` file. The report will keep track of all the past run. That means it will append the report of each run into the above file. To generate a clean report, you need to:

```
make clean && make
```

Then run the `sensorfusion` binary again
