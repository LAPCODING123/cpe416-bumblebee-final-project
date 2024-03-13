// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 3
// Description: Robot class to run the robot.

#pragma once

#include <Bumblebee.h>
#include <vector>
#include "timer.h"
#include "drivetrain.h"
#include "debouncer.h"
#include "pid_controller.h"
#include "light_sensor.h"
#include "state_manager.h"
#include "state_handler_tuning.h"
#include "state_handler_pid.h"
#include "calibration_data.h"

#define BTN_HOLD_TIME 250

class Robot
{
public:
    Robot();
    ~Robot();

    void setup();
    void periodic();

private:
    Drivetrain *m_drivetrain;
    ButtonDebouncer *m_button;
    PID *m_pidController;

    TuningMode *m_tuningMode;
    PIDMode *m_pidMode;
    StateManager *m_stateManager;

    bool m_buttonPressed;
    bool m_longPressTriggered;
    unsigned long m_buttonPressTime;

    void when_btn_pressed();
    void when_btn_held();
};
