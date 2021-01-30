#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H

#include <cstdio>
#include <iostream>
#include <string>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <sstream>
#include <vector>

#include "utilities/fs.h"
#include "utilities/graph.h"
#include "utilities/math.h"
#include "utilities/string.h"
#include "utilities/terminal.h"



namespace utilities {

    namespace string {
        using std::size_t;
        using std::string;

        #define ALPHABET 256
        #define Q 101

        bool rabin_karp(const std::string& pattern, const std::string& text) {
            size_t n = text.length();
            size_t m = pattern.length();
            int p = 0;
            int t = 0;
            int h = 1;

            // Calculate the hash value of pattern
            for (int i = 0; i < m; i++) {
                h = (h * ALPHABET) % Q;  // precompute
                p = (ALPHABET * p + pattern[i]) % Q;
                t = (ALPHABET * t + text[i]) % Q;
            }

            // Slide the 'pattern' over 'text' by one
            for (int i = 0; i < n - m; i++) {
                // check the hash values
                if (p == t) {
                    // check the characters one by one (check for false positives)
                    int j = 0;
                    for (; j < m; j++) {
                        if (text[i + j] != pattern[j]) {
                            break;
                        }
                    }

                    if (j == m) {
                        return true;
                    }
                }

                // Calculate has value of next window of 'text'
                // Remove leading digit, add trailing digit.
                if (i < n - m) {
                    t = (ALPHABET * t - text[i] * h + text[i + m]) % Q;  // clever update
                    // we might get negative values of t, converting it to positive.
                    if (t < 0) {
                        t = t + Q;
                    }
                }
            }

            return false;
        }

        void prepare_match(const std::string& pattern, std::vector<int>& b) {
            int i = 0;
            int j = -1;
            size_t m = pattern.length();

            b.resize(m);
            b[0] = -1;   // starting values

            while (i < m) {  // pre-process the pattern string
                while (j >= 0 && pattern[i] != pattern[j]) {
                    j = b[j];  // if different, reset j using b
                }

                i += 1;
                j += 1;          // if same advance both pointers
                b[i] = j;
            }
        }

        std::vector<int> prefix_table(const std::string& pattern) {
            size_t len = pattern.length();
            std::vector<int> table(len, 0);

            int k = 0;
            for (int i = 1; i < len; i++) {

                while (k > 0 && pattern[k+1] != pattern[i]) {
                    k = table[k];
                }

                if (pattern[k+1] == pattern[i]) {
                    k += 1; // the longest prefix str_k is also a proper suffix of str_i
                }
                table[i] = k;
            }

            return table;
        }

        // bool knuth_morris_prat(const std::string& pattern, const std::string& text) {
        //     int i = 0, j = 0; // starting values
        //     size_t n = text.length();
        //     size_t m = pattern.length();

        //     while (i <= n) {  // search through text string
        //         while(j >= 0 && text[i] != pattern[j]) {
        //             j = b[j];  // if different, reset j using b
        //         }
        //         i += 1;
        //         j += 1;  // if same advance both pointers
        //         if (j == m) {  // a match found when a == m
        //             j = b[j];  // prepare j for the next possible match
        //             return true;
        //         }
        //     }
        //     return false;
        // }


        // void trim(const std::string& pattern, std::string& text) {
        //     for (auto iter = text.begin(); iter != text.end(); iter++) {

        //     }
        //     text.erase()
        // }

    }
}













std::vector<std::string> read_lines(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("the file:\t" + path + "\t does not exist.\n");
    }

    std::string line{};
    std::vector<std::string> lines{};

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::string read_to_string(const std::string& path) {

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("the file:\t" + path + "\t does not exist.\n");
    }
    std::string line{};
    std::vector<std::string> lines{};

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::string retval{};

    for (const std::string& str : lines) {
        retval += str + "\n";
    }

    return retval;
}

#endif // COLOR_PRINT_H
