#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "utilities.h"

int main() {
    std::string pattern { "abcdabd" };
    auto table = utilities::string::prefix_table(pattern);

    std::vector<int> correct { 0, 0, 0, 0, 1, 2, 0 };

    assert(correct == table);

    return 0;
}