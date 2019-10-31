struct sensorList
{
    int number_of_sensors;
    int *values;
    int timestamp;
};
int calculate_support_degree_matrix(struct sensorList sensor);