struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int update_sensor_list(struct sensorList sensor);