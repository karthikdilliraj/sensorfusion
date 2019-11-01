struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int record_out_of_range_sensor(struct sensorList sensor);