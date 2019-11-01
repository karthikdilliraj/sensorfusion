struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int update_out_range_sensor_list(struct sensorList sensor);