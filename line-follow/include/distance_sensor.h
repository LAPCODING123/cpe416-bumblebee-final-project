/*
    SharpIR

    Arduino library for retrieving distance (in cm) from the analog GP2Y0A21Y and GP2Y0A02YK

    From an original version of Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com)

    Version : 1.0 : Guillaume Rico

    Version : 1.2 : Archery2000

    https://github.com/guillaume-rico/SharpIR

*/

#pragma once

#define NB_SAMPLE 25
#define SHARP_IR_PIN A0

#include "Arduino.h"

class SharpIR
{
public:
    static SharpIR &getInstance()
    {
        static SharpIR instance; // Guaranteed to be destroyed.
                                 // Instantiated on first use.
        return instance;
    }
    int distance();

    SharpIR(SharpIR const &) = delete;
    void operator=(SharpIR const &) = delete;

private:
    SharpIR();
    void sort(int a[], int size);
};
