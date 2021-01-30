#ifndef _UTILITIES_STRING_H
#define _UTILITIES_STRING_H

#include <string>
// #include <string_view>


namespace utilities {
namespace string {
    // using std::string_view;
    using std::size_t;
    using std::vector;

/*
    tokenize a string based on given delimiter, and return tokens in a std::vector<string>
    PARAMETERS :
        std::string const& str - string to tokenize
        const char delim - delimiter character. NOTE can only be one character long
        std::vector<std::string>& container - dynamic container, to return tokens in
    EXCEPTION SAFETY :
        this function throws an expection of type std::invalid_argument() if str.size() == 0
*/
void tokenize_string(const std::string& str, const char delim, std::vector<std::string>& container) {
    std::size_t size = str.size();
    if (size == 0) {
        throw std::invalid_argument("invalid argument, string is empty");
    }

    std::size_t start = 0;
    // use two index variables 'start', 'stop' to go through the string
    while(start <= size) {
        // find the starting position, by finding the position of the first character, that
        // is not equal to the delimiter
        start = str.find_first_not_of(delim, start);

        // if there are no more characters left in the string, str.find()
        // will return string::npos, which ends the loop
        if (start == std::string::npos) {
            break;
        }

        std::size_t stop = start;

        stop = str.find_first_of(delim, stop);
        // create a copy using string::substr(), and insert into the end of the vector
        container.push_back(str.substr(start, stop - start));
        // update the start iterator, to seach for next word
        start = stop;
    }

    std::vector<std::string> split_lines(const std::string& str) noexcept {
        std::vector<std::string> lines{};
        tokenize_string(str, '\n', lines);
        return lines;
    }
}

// string_view (FASTER!)
// concatenate
// append
// prepend
// join(string, "delim")
// join (initializer-list, splitter)


} // namespace string
} // namespace utilities



#endif // _UTILITIES_STRING_H
