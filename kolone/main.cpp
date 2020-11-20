/* Jacob Kloepper
 * November 17, 2020
 * Kattis problem: kolone
 *  Link: https://open.kattis.com/problems/kolone
 */

#include <iostream>
#include <vector>

/* algorithm explanation:
 * based on bubble sort.
 *
 * Instead of checking >, check direction key.
 * bool direction: 0 -> going right (left_ants)
 *                 1 -> going left (right_ants)
 * only iterate time times.
 * do not "bubble": after a successful swap, skip ahead one.
 */
std::string collide_ants(std::vector<std::pair<char, bool>> sequence, unsigned int time) {
    std::string out_sequence {};
    std::pair<char, bool> temp {};

    for (int t {0}; t < time; t++) {
        for (int pair {0}; pair < sequence.size()-1; pair++) {
            if (sequence.at(pair).second == 0 && sequence.at(pair).second ^ sequence.at(pair+1).second) {
                temp = sequence.at(pair);
                sequence.at(pair) = sequence.at(pair+1);
                sequence.at(pair+1) = temp;
                pair++;
            }
        }
    }

    for (auto pair : sequence) {
        out_sequence.push_back(pair.first);
    }

    return out_sequence;
}

int main() {
    unsigned int left_size {};
    unsigned int right_size {};
    std::string left_ants {};
    std::string right_ants {};
    unsigned time {};

    // Get inputs
    std::cin >> left_size >> right_size >> left_ants >> right_ants >> time;
    if (left_size != left_ants.size()) {
        std::cout << "Invalid input. [" << left_size << ", " << left_ants.size() << "] must match." << std::endl;
        return 1;
    }
    if (right_size != right_ants.size()) {
        std::cout << "Invalid input. [" << right_size << ", " << right_ants.size() << "] must match." << std::endl;
        return 1;
    }

    // Get proper initial ant sequence
    std::vector<std::pair<char, bool>> sequence {};

    // Left ants (going right -> false)
    for (auto ritr {left_ants.rbegin()}; ritr != left_ants.rend(); ritr++) {
        sequence.emplace_back(*ritr, false);
    }
    // Right ants (going left -> true)
    for (auto ch : right_ants) {
        sequence.emplace_back(ch, true);
    }

    // Output order after time
    std::cout << collide_ants(sequence, time);

    return 0;
}