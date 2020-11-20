/* Jacob Kloepper
 * November 19, 2020
 * Kattis problem: loowater
 *  Link: https://open.kattis.com/problems/loowater
 */

#include <iostream>
#include <vector>
#include <set>

// Given the vector of dragons and multiset of knights, return either the minimum cost for the kingdom's safety
// or a confirmation of the kingdom's impending doom.
std::string check_kingdom(std::vector<std::pair<int, bool>> dragons, std::multiset<int> knights) {
    // Running sum of spent knights
    int spent_knights {0};
    int count {0};

    // Get biggest knight
    int max_knight {0};
    for (auto knight : knights) {
        if (knight > max_knight) {
            max_knight = knight;
        }
    }

    // Run through dragons and knights
    for (auto pair : dragons) {
        for (auto knight : knights) {
            if (pair.first <= knight) {

                // Kill dragon
                dragons.erase(dragons.begin() + count);

                // Spend knight
                knights.erase(knight);
                spent_knights += knight;
                break;
            }
        }
        count++;
    }

    // Return based on data
    for (auto pair : dragons) {
        if (pair.second) {
            return "Loowater is doomed!";
        }
    }
    return std::to_string(spent_knights);
}

int main() {
    std::vector<std::pair<int, bool>> dragons{};
    std::multiset<int> knights{};

    int num_dragons{};
    int num_knights{};

    int tmp_dragon;
    int tmp_knight;

    // Get inputs
    std::cin >> num_dragons;
    std::cin >> num_knights;

    while (num_dragons != 0 && num_knights != 0) {

        // Compile dragon and knight collections
        for (int i{0}; i < num_dragons; i++) {
            std::cin >> tmp_dragon;
            dragons.emplace_back(tmp_dragon, true);
        }
        for (int i{0}; i < num_knights; i++) {
            std::cin >> tmp_knight;
            knights.insert(tmp_knight);
        }

        // Output
        std::cout << check_kingdom(dragons, knights) << std::endl;

        std::cin >> num_dragons;
        std::cin >> num_knights;
    }

    return 0;
}