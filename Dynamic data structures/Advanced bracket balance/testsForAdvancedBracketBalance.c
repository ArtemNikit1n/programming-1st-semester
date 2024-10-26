#include <stdio.h>
#include <stdbool.h>

#include "advancedBracketBalance.h"

bool testAdvancedBracketBalance() {
    bool test1 = advanceBracketBalance("102938");
    bool test2 = advanceBracketBalance("([{}])()[{}]");
    bool test3 = advanceBracketBalance("([)]{}");
    bool test4 = advanceBracketBalance("{{{123}}}(2[])");
    return !test1 && test2 && !test3 && !test4;
}