/* Jacob Kloepper
 * November 21, 2020
 * Kattis problem: guessinggame
 *  Link: https://open.kattis.com/problems/guessinggame
 */

#include <iostream>
#include <set>

std::set<int> init_soln_set() {
    std::set<int> tmp {1,2,3,4,5,6,7,8,9,10};
    return tmp;
}

char get_relation(const char& input) {
    // Checking only the first char avoids \n issues.
    if (input == 'l') {
        return '<';
    } else if (input == 'h') {
        return '>';
    } else if (input == 'o') {
        return '=';
    } else {
        std::cout << "Unexpected input." << std::endl;
        return '\0';
    }
}

int main() {
    std::pair<int, char> guess {};
    std::string tmp_str {};
    char tmp_char {};
    std::set<int> soln_set = init_soln_set();
    bool caught {false};

    int max_guess {};

    // Get current guess
    std::cin >> guess.first;
    while (guess.first != 0) {
        // Get relation for current guess
        std::getline(std::cin, tmp_str); // Eat first line
        std::getline(std::cin, tmp_str);
        tmp_char = tmp_str.substr(tmp_str.find(' ') + 1).at(0);
        guess.second = get_relation(tmp_char);

        // Update solution set if Stan has not already been caught
        if (!caught) {
            if (guess.second == '<') {
                if (!soln_set.empty()) {
                    max_guess = *(soln_set.rbegin());
                } else {
                    max_guess = 0;
                    caught = true;
                }
                for (int i {*soln_set.begin()}; i < max_guess + 1; i++) {

                    if (i <= guess.first) {
                        if (soln_set.find(i) == soln_set.end()) {
                            std::cout << "Stan is dishonest" << std::endl;
                            caught = true;
                        } else {
                            soln_set.erase(i);
                        }
                    }
                }
            } else if (guess.second == '>') {
                if (!soln_set.empty()) {
                    max_guess = *(soln_set.rbegin());
                } else {
                    max_guess = 0;
                    caught = true;
                }
                for (int i {1}; i < max_guess + 1; i++) {

                    if (i >= guess.first) {
                        if (soln_set.find(i) == soln_set.end()) {
                            std::cout << "Stan is dishonest" << std::endl;
                            caught = true;
                        } else {
                            soln_set.erase(i);
                        }
                    }
                }
            }
        }

        // Check if we go to the next guessing set
        if (guess.second == '=') {
            if (soln_set.find(guess.first) != soln_set.end()) {
                std::cout << "Stan may be honest" << std::endl;
            } else {
                std::cout << "Stan is dishonest" << std::endl;
            }

            soln_set.clear();
            soln_set = init_soln_set();
            caught = false;
        }

        // Get next guess
        std::cin >> guess.first;
    }

    return 0;
}
