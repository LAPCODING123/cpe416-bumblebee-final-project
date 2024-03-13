// Name:  Lorenzo Pedroza and Chris Lawson
// Lab 2
// Description: The main file for running all parts of program 2.
#include "main.h"

Robot robot = Robot();

void setup()
{
  robot.setup();
}

void loop()
{
  robot.periodic();
}
