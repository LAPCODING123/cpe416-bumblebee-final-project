#include "distance_sensor.h"

SharpIR::SharpIR()
{

    // Define pin as Input
    pinMode(SHARP_IR_PIN, INPUT);
    analogReference(DEFAULT);
}

// Sort an array
void SharpIR::sort(int a[], int size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        bool flag = true;
        for (int o = 0; o < (size - (i + 1)); o++)
        {
            if (a[o] > a[o + 1])
            {
                int t = a[o];
                a[o] = a[o + 1];
                a[o + 1] = t;
                flag = false;
            }
        }
        if (flag)
            break;
    }
}

// Read distance and compute it
int SharpIR::distance()
{

    int ir_val[NB_SAMPLE] = {};
    int distanceCM;
    int median;

    for (int i = 0; i < NB_SAMPLE; i++)
    {
        // Read analog value
        ir_val[i] = analogRead(SHARP_IR_PIN);
    }

    sort(ir_val, NB_SAMPLE);
    median = ir_val[NB_SAMPLE / 2];
    // Different expressions required as the Photon has 12 bit ADCs vs 10 bit for Arduinos
    distanceCM = 29.988 * pow(map(median, 0, 1023, 0, 5000) / 1000.0, -1.173);

    return distanceCM;
}
