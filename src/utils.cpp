#include <algorithm>

#include "../include/utils.h"

int hcf(int num1, int num2)
{
    int result = std::min(num1, num2); // Find Minimum of num1 nd num2

    while (result > 0)
    {
        if (num1 % result == 0 && num2 % result == 0)
            break;

        result--;
    }

    return result; // return gcd of num1 and num2
}