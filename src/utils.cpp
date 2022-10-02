#include "utils.h"

/**
 * @brief this function checks if a given value x is in the range between the min and max. the function also returns
 *        true if x is equal to min or max
 * 
 * @param x the value that has to be checked
 * @param min the lower bound of the range
 * @param max the upper bound of the range
 * 
 * @returns a bool that indicates if x is in range of min and max
*/
bool utils::inRange(uint8_t x, uint8_t min, uint8_t max)
{
    if(x <= max && x >= min) { return true; };
    return false;
}