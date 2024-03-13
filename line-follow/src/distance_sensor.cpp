#include "distance_sensor.h"

#define CONVERSION_FACTOR 4.025

u08 get_dist_sensor_raw()
{
    return analog(DIST_SENS_AN_PIN);
}

// float get_dist_sensor_cm()
// // {
// //     return get_dist_sensor_raw()/CONVERSION_FACTOR;
// // }
