struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int record_stuck_sensor(struct sensorList sensor);