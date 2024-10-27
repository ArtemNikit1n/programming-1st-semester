#include <stdio.h>
#include <stdbool.h>

#include "postfixCalculator.h"

bool testCalculate() {
    int test1 = calculate("9 6 - 1 2 + *");
    int test2 = calculate("17 10 + 3 * 9 /");
    return test1 == 9 && test2 == 9;
}