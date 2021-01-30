// how many redistributions can be done before a blocks-in-banks configuration is
// produced that has been seen before?

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
// #include <filesystem>

#include "utilities.h"

std::size_t find_largest_bank(const std::vector<int>& banks) {
    int largest = 0;
    for (int bank : banks) {
        if (bank > largest) {
            largest = bank;
        }
    }

    size_t index = 0;
    for (std::size_t i = 0; i < banks.size(); i++) {
        if (banks[i] == largest) {
            index = i;
            break;
        }
    }

    return index;
}

void redistribute_bank(std::size_t index, std::vector<int>& banks) {
    if (index >= banks.size()) {
        throw std::invalid_argument("index: " + std::to_string(index) +
            " is larger than the size of banks: " + std::to_string(banks.size()));
    }

    int blocks = banks[index];
    banks[index] = 0;
    index += 1;

    while (blocks > 0) {
        // if it reaches the last memory bank, it wraps around to the first one.
        if (index >= banks.size()) {
            index = 0;
        }
        banks[index] += 1;
        blocks -= 1;
        index += 1;
    }
}

bool check_previous_configurations(const std::vector<std::vector<int>>& previous_configurations, const std::vector<int>& current_configuration) {
    for (const auto& configuration : previous_configurations) {
        if (current_configuration == configuration) {
            return true;
        }
    }

    return false;
}

int part_1(std::vector<int> current_configuration) {
    int count = 0;
    std::vector<std::vector<int>> previous_configurations{};

    while (true) {
        count += 1;
        // 1. find the largest bank. If 2 or more are the highest then, the first one
        // in the sequence is chosen.
        std::size_t largest = find_largest_bank(current_configuration);

        // 2. remove all of the blocks from the selected bank, then move to the next
        // (by index) memory bank and insert one of the blocks.
        // It continues doing this until it runs out of blocks;
        // if it reaches the last memory bank, it wraps around to the first one.
        try {
            redistribute_bank(largest, current_configuration);
        }
        catch (const std::exception& exp) {
            std::cerr << exp.what() << std::endl;
            return -1;
        }

        // 3. if a blocks-in-banks configuration is produced which have been seen before, break.
        if (check_previous_configurations(previous_configurations, current_configuration)) {
            break;
        }

        previous_configurations.push_back(current_configuration);
    }

    return count;
}

int part_2(std::vector<int> current_configuration) {
    std::vector<std::vector<int>> previous_configurations{};

    // 1. find the configuration which causes a cycle
    while (true) {
        std::size_t largest = find_largest_bank(current_configuration);
        try {
            redistribute_bank(largest, current_configuration);
        }
        catch (const std::exception& exp) {
            std::cerr << exp.what() << std::endl;
            return -1;
        }

        if (check_previous_configurations(previous_configurations, current_configuration)) {
            break;
        }

        previous_configurations.push_back(current_configuration);
    }

    int cycle_count = 0;

    // 2. count the number of cycles as the difference in indexes between the configurations
    //    constrituting a cycle.
    for (std::size_t i = 0; i < previous_configurations.size(); i++) {
        if (previous_configurations[i] == current_configuration) {
            cycle_count = previous_configurations.size() - i;
            break;
        }
    }

    return cycle_count;
}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << print_red("the input file was not specified as an argument!") << "\n";
        std::cerr << "try:\t./day06 <filename.txt>" << std::endl;
        return 1;
    }

    std::string line{};

    try {
        std::string path = argv[1];
        line = read_to_string(path);
    }
    catch (const std::exception& exp) {
        std::cerr << print_red(exp.what()) << std::endl;
        return 1;
    }

    std::vector<int> input{};
    std::vector<std::string> tokens{};

    try {
        tokenize_string(line, ' ', tokens);
    }
    catch (std::exception exp) {
        std::cerr << print_red(exp.what()) << std::endl;
        return 1;
    }

    // parse the input
    for (const std::string& token : tokens) {
        input.push_back(std::atoi(token.c_str()));
    }

    std::vector<int> part_1_example { 0, 2, 7, 0 };
    assert(part_1(part_1_example) == 5);

    int number_of_redistributions = part_1(input);

    std::cout << print_green("PART 1: " + std::to_string(number_of_redistributions)) << std::endl;

    // -----------------------------------------------------------------------------------------------------------------

    std::vector<int> part_2_example { 0, 2, 7, 0 };
    assert(part_2(part_2_example) == 4);

    int cycles = part_2(input);

    std::cout << print_green("PART 2: " + std::to_string(cycles)) << std::endl;

    return 0;
}
