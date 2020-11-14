/* Jacob Kloepper
 * November 14, 2020
 * Kattis problem: sibice
*/

#include <iostream>
#include <cmath>
#include <vector>

int main() {
    int num_matches, width, height {};
    std::vector<int> lengths {};
    int temp_len {};

    // Get inputs
    std::cin >> num_matches;
    std::cin >> width;
    std::cin >> height;

    for (int i {0}; i < num_matches; i++) {
        std::cin >> temp_len;
        lengths.push_back(temp_len);
    }

    // Get data
    for (auto len : lengths) {
        // Check if the match fits in box and output accordingly
        if (len <= floor(sqrt(double(width * width + height * height)))) {
            std::cout << "DA" << std::endl;
        } else {
            std::cout << "NE" << std::endl;
        }
    }

    return 0;
}
