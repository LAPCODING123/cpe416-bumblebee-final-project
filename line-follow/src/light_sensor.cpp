// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2 Part 2 and 3
// Description: Light sensor helper library for Lab 2 parts 2 and 3
#include "light_sensor.h"

float analog_to_percent(u08 analog_value)
{
    return (float)analog_value / 255.0;
}

int get_left_IR_raw()
{
    return analogRead(A3);
}

int get_right_IR_raw()
{
    return analogRead(A2);
}

float get_left_IR_percent(float left_IR_amount)
{
    const int LEFT_DIFF = CalibrationData::LEFT_BLACK - CalibrationData::LEFT_WHITE;
    return Util::bound((left_IR_amount - CalibrationData::LEFT_WHITE) / LEFT_DIFF, 0, 1);
}

float get_right_IR_percent(float right_IR_amount)
{
    const int RIGHT_DIFF = CalibrationData::RIGHT_BLACK - CalibrationData::RIGHT_WHITE;
    return Util::bound((right_IR_amount - CalibrationData::RIGHT_WHITE) / RIGHT_DIFF, 0, 1);
}

float get_left_IR_percent()
{
    return get_left_IR_percent(get_left_IR_raw());
}

float get_right_IR_percent()
{
    return get_right_IR_percent(get_right_IR_raw());
}

float get_IR_diff()
{
    return get_left_IR_percent() - get_right_IR_percent();
}

bool off_track()
{
    return (get_left_IR_percent() < CalibrationData::PERCENT_THRESHOLD) && (get_right_IR_percent() < CalibrationData::PERCENT_THRESHOLD);
}
