/* Jacob Kloepper
 * November 14, 2020
 * Kattis problem: 4thought
 *  Link: https://open.kattis.com/problems/4thought
 */

#include <iostream>
#include <vector>
#include <set>

/* algorithm explanation:
 * There are a finite number of possible solutions based on the operators.
 * Fill a set with all solutions and check the set elements against the inputs.
 */

// Given a vector of 3 chars representing the operations in an equation
// of form 4 o 4 o 4 o 4, compute the result
int parse_equation(std::vector<char> operations) {
    std::vector <int> pos_val (4,4);
    int new_size {3};

    // First sweep: mult/div
    for (int i {0}; i < new_size; i++) {
        if (operations.at(i) == '*') {
            pos_val.at(i) = pos_val.at(i) * pos_val.at(i+1);

            // Edit logic
            operations.erase(operations.begin()+i);
            pos_val.erase(pos_val.begin()+i+1);
            new_size--;
            i = -1;
        }
        if (i != -1) {
            if (operations.at(i) == '/') {
                pos_val.at(i) = pos_val.at(i) / pos_val.at(i + 1);

                // Edit logic
                operations.erase(operations.begin() + i);
                pos_val.erase(pos_val.begin() + i + 1);
                new_size--;
                i = -1;
            }
        }
    }

    // Second sweep: add/sub
    for (int i {0}; i < new_size; i++) {
        if (operations.at(i) == '+') {
            pos_val.at(i) = pos_val.at(i) + pos_val.at(i+1);

            // Edit logic
            operations.erase(operations.begin()+i);
            pos_val.erase(pos_val.begin()+i+1);
            new_size--;
            i = -1;
        }
        if (i != -1) {
            if (operations.at(i) == '-') {
                pos_val.at(i) = pos_val.at(i) - pos_val.at(i + 1);

                // Edit logic
                operations.erase(operations.begin() + i);
                pos_val.erase(pos_val.begin() + i + 1);
                new_size--;
                i = -1;
            }
        }
    }

    return pos_val.at(0);
}

// Base four vector incrementer
void increment_key(std::vector<unsigned int>& key) {
    key.at(0)++;

    for (int i {0}; i < key.size(); i++) {
        if (key.at(i) == 4 && i != 2) {
            key.at(i) = 0;
            key.at(i+1)++;
        }
    }
}

int main() {
    std::vector<char> operations {'+', '-', '*', '/'};
    std::vector<char> curr_permutation {'a', 'a', 'a'};
    std::vector<unsigned int> key {0, 0, 0}; // key in base 4

    std::set<std::pair<std::vector<char>, int>> solution_set {};
    std::set<int> visited_solutions {};
    bool found {false};

    // Get inputs
    int num_tests {};
    int32_t test {};

    std::cin >> num_tests;

    // Get current permutation
    while (key.at(2) != 4) {
        for (int i{0}; i < key.size(); i++) {
            curr_permutation.at(i) = operations.at(key.at(i));
        }
        increment_key(key);

        solution_set.insert({curr_permutation, parse_equation(curr_permutation)});
    }

    // Populate solution set
    for (int i {0}; i < num_tests; i++) {
        std::cin >> test;

        // Check solution set and output
        for (const auto& pair : solution_set) {
            if (pair.second == test && visited_solutions.find(pair.second) == visited_solutions.end()) {
                visited_solutions.insert(pair.second);

                std::cout << "4 ";
                for (auto op : pair.first) {
                    std::cout << op;
                    std::cout << " 4 ";
                }
                std::cout << "= " << pair.second << std::endl;
                found = true;
            }
        }
        // Check flag and update
        if (!found) {
            std::cout << "no solution" << std::endl;
        } else {
            found = false;
        }
    }
    return 0;
}
