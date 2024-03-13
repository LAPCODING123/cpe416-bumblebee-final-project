#include "state_handler_pid.h"
#include "distance_sensor.h"

#define FORWARD_TIME 500

PIDMode::PIDMode(Drivetrain *drivetrain, PID *pidController) : m_drivetrain(drivetrain), m_pidController(pidController)
{
    m_stateName = PID_MODE;
}

PIDMode::~PIDMode()
{
}

void PIDMode::init()
{
    clear_screen();
    print_string("PID");
}

//handles remaneuving to get around an obstacle places on the tack 
void PIDMode::handleObstaclePeriodic()
{
    unsigned long time_diff = millis() - m_correctiveManeuverInitTime;
    if(time_diff < m_correctiveManeuverWaitTime)
    {
        m_drivetrain->set_speed_turn(0.0, 15.0);
    }
    else if(time_diff >= m_correctiveManeuverWaitTime && time_diff <  m_correctiveManeuverWaitTime + 950)
    {
        //turn 90 ccw
        m_drivetrain->set_speed_turn(20.0, -2.5);

    }
    else if(time_diff >= m_correctiveManeuverWaitTime + 950 && time_diff <  m_correctiveManeuverWaitTime + 1300)
    {
        //turn 90 ccw
        m_drivetrain->set_speed_turn(0.0, 15.0);

    }
    else
    {
        m_detourMode = false;
    }
    // else if(time_diff > m_correctiveManeuverWaitTime+500 && time_diff <  m_correctiveManeuverWaitTime + 750)
    // {
    //     m_drivetrain->set_speed_turn(0.0, -30.0);

    // }
    // else if(time_diff > m_correctiveManeuverWaitTime+750 && time_diff <  m_correctiveManeuverWaitTime + 1000)
    // {
    //     //turn 90 cw
    //     m_drivetrain->set_speed(15.0);

    // }
    // else if(time_diff > m_correctiveManeuverWaitTime+1000 && time_diff <  m_correctiveManeuverWaitTime + 1250)
    // {
    //     m_drivetrain->set_speed_turn(0.0, -15.0);
    // }
    // else if(time_diff > m_correctiveManeuverWaitTime+1250 && time_diff <  m_correctiveManeuverWaitTime + 1500)
    // {
    //     m_drivetrain->set_speed(15.0);
    // }
    // else if(time_diff > m_correctiveManeuverWaitTime+1500 && time_diff <  m_correctiveManeuverWaitTime + 1750)
    // {
    //     m_drivetrain->set_speed_turn(0.0, 15.0);
    // }
 
    // else if(time_diff > m_correctiveManeuverWaitTime)
    // {
    //     //move forward

    // }
    // else if(time_diff> m_correctiveManeuverWaitTime)
    // {
    //     //turn 70 cw

    // }
    // else if(time_diff > m_correctiveManeuverWaitTime)
    // {
    //     //move forward until on track

    // }
    // else if(time_diff > m_correctiveManeuverWaitTime)
    // {

    // }
   
}

void PIDMode::periodic()
{
    // clear_screen();
    // print_num(get_dist_sensor_raw());
    int dir = m_lastWorkingDir;
    // If off track, sweep left and right
    int dist_reading = SharpIR::getInstance().distance();
    
    if(!m_detourMode) m_detourMode = dist_reading <= 16;

    if (off_track())
    {
        // If we just entered off track mode, set the initial time
        if (!m_offTrackMode)
        {
            m_offTrackInitTime = millis();
            m_offTrackMode = true;
        }

        if (m_detourMode)
        {
           handleObstaclePeriodic();
        }

        else
        {
            m_correctiveManeuverInitTime = millis();
              // Turn in place
            m_drivetrain->set_speed_turn(0, dir * 50);

            // If we've been off track for too long, reverse direction
            if (millis() - m_offTrackInitTime > m_offTrackWaitTime)
            {
                dir *= -1;
                m_offTrackInitTime = millis();
                m_offTrackWaitTime *= 2;
            }
        }

    }
    // If we're on track, follow the line
    else
    {
        // If we just got back on track, reset the wait time and turn off off track mode
        if (m_offTrackMode)
        {
            m_offTrackWaitTime = 100;
            m_offTrackMode = false;

            // Save the last working direction that got us back on track
            // This is an educated guess for the next time we go off track
            m_lastWorkingDir = dir;
        }

        if (m_detourMode)
        {
            handleObstaclePeriodic();
        }
        else //run the PID controller
        {
            m_correctiveManeuverInitTime = millis();
             // Set the speed and turn based on the PID controller
            struct MotorCommand speeds;
            speeds = m_drivetrain->compute_proportional(m_pidController, 15);
            m_drivetrain->set_speed(speeds);
        }

       
    }
}

void PIDMode::postPeriodic()
{
}

bool PIDMode::btnPressed()
{
    return true;
}

void PIDMode::btnHeld()
{
}
