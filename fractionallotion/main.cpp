/* Jacob Kloepper
 * November 14, 2020
 * Kattis problem: fractionallotion
 *	Link: https://open.kattis.com/problems/fractionallotion
*/

#include <iostream>
#include <set>
#include <string>

// Check if double input is a valid integer
bool is_integer(double num) {
    if (num == int(num)) {
        return true;
    }
    return false;
}

// algorithm explanation: 1/x + 1/y = 1/n implies xn/(x-n)=y
// check if xn/(x-n) is an integer, then consider (x,y) a valid pair.
// also: x > n, y > n

int main() {
    double initial {};
    unsigned int count {0};
    std::set<unsigned int> used_nums {};
    std::string str {};

    while (std::cin >> str) {
        // Accept rational input, retain only denominator
        initial = std::stod(str.substr(2, str.size()-2), nullptr);

        // The last pair left unchecked is (initial*2, initial*2), giving the upper bound below.
        for (int i{int(initial)}; i < initial*2; i++) {
            double y {((i + 1) * initial) / ((i + 1) - initial)}; // y = xn/(x-n)
            if (is_integer(y)) {
                if (used_nums.find(i + 1) == used_nums.end()) { // Do not count already-counted pairs
                    count++;
                    used_nums.insert(y);
                }
                used_nums.insert(i + 1);
            }
        }

        // Output and reset
        std::cout << count << std::endl;
        used_nums.clear();
        count = 0;
    }

    return 0;
}