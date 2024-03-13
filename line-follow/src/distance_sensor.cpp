#include "distance_sensor.h"

#define CONVERSION_FACTOR 4.025

u08 get_dist_sensor_raw()
{
    return analogRead(A0);
}

int get_dist_sensor_cm()
{
    return (6762 / (get_dist_sensor_raw() - 9)) - 4;
}
