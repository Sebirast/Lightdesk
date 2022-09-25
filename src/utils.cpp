#include "utils.h"


bool utils::inRange(uint8_t x, uint8_t min, uint8_t max)
{
    if(x < max && x > min) { return true; };
    return false;
}
