#pragma once
#include <Arduino.h>

namespace utils
{
    bool inRange(uint8_t x, uint8_t min, uint8_t max);
    double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
}