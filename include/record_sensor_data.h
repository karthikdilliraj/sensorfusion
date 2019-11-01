struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int record_sensor_data(struct sensorList sensor);