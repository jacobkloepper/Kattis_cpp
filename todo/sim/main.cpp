/* Jacob Kloepper
 * November 15, 2020
 * Kattis problem: sim
 *  Link: https://open.kattis.com/problems/sim
 */
#include <iostream>

/* algorithm explanation:
 * Use iterators and flags to build the output string from the input string.
 *
 */


// Given a string with control chars, parse and output it.
std::string parse_input(std::string str) {
    std::string parsed {};
    std::string str_alnum {};

    // Fill parsed with at least as many chars needed
    for (auto c : str) {
        if (isalnum(c) || isspace(c)) {
            str_alnum.push_back(c);
        }
    }

    // Pad parsed a bit more
    parsed.resize(str_alnum.size()+5);

    // Iterators used to access around the string
    auto icursor {str.begin()};
    auto ocursor {parsed.begin()};
    auto top_cursor {parsed.begin()};

    // Is "[" mode on?
    bool home_flag {false};

    // Iterate through the string, copying input string to output string
    while (icursor != str.end()) {
        if (isalnum(*icursor) || isspace(*icursor)) {
            if (!home_flag) {
                parsed.erase(ocursor);
                parsed.insert(top_cursor, *icursor);
            } else {
                parsed.insert(ocursor, *icursor);
                parsed.pop_back();
            }

            ocursor++;
            top_cursor++;
        }

        // Control chars:
        switch (*icursor) {

            case '<':
                 parsed.erase(ocursor - 1);

                 if (ocursor != parsed.begin()) {
                    ocursor -= 1;
                    top_cursor -= 1;
                 }
                 break;

            case '[':
                home_flag = true;
                ocursor = parsed.begin();

                break;

            case ']':
                home_flag = false;
                ocursor = top_cursor;

                break;

            default:
                break;
        }

        icursor++;
    }

    // Remove padding
    while (*(parsed.end()-1) == '\0') {
        parsed.pop_back();
    }

    return parsed;
}

int main() {
    int num_tests {};
    std::string input {};

    // Get inputs
    std::getline(std::cin, input);
    num_tests = std::stoi(input);

    for (int i {0}; i < num_tests; i++) {
        std::getline(std::cin, input);
        std::cout << parse_input(input) << std::endl;
    }

    return 0;
}