#ifndef _UTILITIES_TERMINAL_H
#define _UTILITIES_TERMINAL_H

// #include <cstdio>
#include <iostream>
#include <string>

namespace utilities {

    namespace terminal {
        using std::cout;
        using std::string;

        string red(const string& str) {
            return "\x1b[35;5;31m" + str + "\033[0m";
        }

        string green(const string& str) {
            return "\x1b[35;5;32m" + str + "\033[0m";
        }

        string yellow(const string& str) {
            return "\x1b[35;5;33m" + str + "\033[0m";
        }

        string blue(const string& str) {
            return "\x1b[35;5;34m" + str + "\033[0m";
        }

        string magenta(const string& str) {
            return "\x1b[35;5;35m" + str + "\033[0m";
        }

        string cyan(const string& str) {
            return "\x1b[35;5;36m" + str + "\033[0m";
        }

        void clear_screen() {
            cout << "\033[2j\033[1;1H";
        }
    }
}

#endif // _UTILITIES_TERMINAL_H