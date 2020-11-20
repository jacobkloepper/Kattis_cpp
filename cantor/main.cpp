/* Jacob Kloepper
 * November 14, 2020
 * Kattis problem: cantor
*/

#include <iostream>
#include <set>
#include <vector>

/* Info:
 * Three properties are useful in the ternary representation:
 * 1. contains a "1"
 *      NOT in set
 * 2. repeats
 *      IN SET
 * 3. terminates
 *      if the last digit is not 2, IN SET
 */

// Info on ternary obtained from https://math.stackexchange.com/questions/974851/

/* [0]: contains 1
 * [1]: repeats
 * [2]: terminates
 */
std::vector<bool> check_cantor_criteria(double num) {
    std::vector<bool> flags (3, false);
    std::vector<unsigned int> ternary_rep {};

    // Check first flag
    for (auto digit : ternary_rep) {
        if (digit == 1) {
            flags.at(0) = true;
        }
    }

    // Check second flag

    // Check third flag

    return flags;
}

int main() {
    std::string str {};
    double input_dec {};
    double input_tern {};
    std::vector<bool> flags {}; // Checks conditions outlined in the info section
    std::set<double> cantor {};

    while (std::cin >> str) {
        // Exit condition
        if (str == "END") {
            return 0;
        }

        input_dec = std::stod(str, nullptr);

        flags = check_cantor_criteria(input_dec);







    }

}
