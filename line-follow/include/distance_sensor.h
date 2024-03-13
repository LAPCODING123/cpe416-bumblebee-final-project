#pragma once

#include <Bumblebee.h>
#include "util.h"
#include "calibration_data.h"

#define DIST_SENS_AN_PIN ANALOG0_PIN

u08 get_dist_sensor_raw();
int get_dist_sensor_cm();
