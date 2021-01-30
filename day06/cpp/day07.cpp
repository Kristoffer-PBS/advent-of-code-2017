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

struct Program final {
    std::string name{};
    unsigned int weight{};
    std::vector<std::string> above_programs{};

    Program(std::string name, unsigned int weight, std::vector<std::string> above_programs) :
        name(name), weight(weight), above_programs(above_programs) {}
};

Program parse(std::string str) {
    // 1. split at whitespace

    std::string name{};
    unsigned int weight{};
    std::vector<std::string> above_programs{};

    std::vector<std::string> tokens{};
    tokenize_string(str, ' ', tokens);

    if (tokens.size() < 2) {
        throw std::invalid_argument("error: the string - " + str + "cannot be parsed into a Program struct");
    }

    name = tokens[0];
    weight 

    // can throw exception
    return Program(name, weight, above_programs);
}


std::string part_1(std::vector<Program> programs) {

    return "foo";
}



int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << print_red("the input file was specified as an argument!") << "\n";
        std::cerr << "try:\t./day06 <filename.txt>" << std::endl;
        return 1;
    }



    std::vector<std::string> lines{};

    try {
        std::string path = argv[1];
        lines = read_lines(path);
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

    return 0;
}
