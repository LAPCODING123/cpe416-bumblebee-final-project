#include <Bumblebee.h>
#include <math.h>
#include "util.h"
#include "timer.h"

#pragma once

class PID
{
public:
    PID(float Kp = 0.0, float Ki = 0.0, float Kd = 0.0);

    void setGains(float Kp = 0.0, float Ki = 0.0, float Kd = 0.0);
    void setTarget(float target);
    float getTarget();
    void reset(float currPosition = NAN);
    void setBounds(float min, float max);

    // These calculate output based on the target and actual
    float calcOutput(float actual);
    float calcOutput(float actual, u16 timeMs);

    // These calculate output based on error
    float calcOutputWithError(float error);
    float calcOutputWithError(float error, u16 timeMs);

private:
    float m_Kp;
    float m_Ki;
    float m_Kd;

    float m_target;
    float m_min;
    float m_max;

    float m_timeLastUpdateSec;
    float m_prevPos;
    float m_prevErr;
    float m_integral;

    float m_lastOutput;
};