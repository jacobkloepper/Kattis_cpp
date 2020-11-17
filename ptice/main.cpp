/* Jacob Kloepper
 * November 17, 2020
 * Kattis problem: ptice
 *  Link: https://open.kattis.com/problems/ptice
 */

#include <iostream>
#include <vector>
#include <set>

// Given the solutions and the marked answers, return a pair of the score and the name of student.
std::pair<int, std::string> check_answers(std::string solutions, std::string marked) {
    std::pair<int, std::string> checked;
    int score {0};

    for (int i {0}; i < solutions.size(); i++) {
        if (solutions.at(i) == marked.at(i%marked.size())) {
            score++;
        }
    }

    // Fill out pair
    checked.first = score;

    // In a real application, I would think you'd use a class of students or a database.
    if (marked == "ABC") {
        checked.second = "Adrian";
    } else if (marked == "BABC") {
        checked.second = "Bruno";
    } else if (marked == "CCAABB") {
        checked.second = "Goran";
    } else {
        std::cout << "Invalid marking input." << std::endl;
    }

    return checked;
}

int main() {
    std::string solutions {};
    int num_questions {};
    std::set<std::pair<int, std::string>> results_set {};

    // Each of these repeat to fill out a written test of size num_solutions;
    std::vector<std::string> to_mark {"ABC", "BABC", "CCAABB"};

    // Get inputs
    std::cin >> num_questions;
    std::cin >> solutions;

    if (num_questions != solutions.size()) {
        std::cout << "Invalid input. [" << num_questions << ", " << solutions.size() << "] must match." << std::endl;
        return 1;
    }


    // Fill solution set
    for (const auto& key : to_mark) {
        results_set.insert(check_answers(solutions, key));
    }

    // Get high score
    int high_score {0};
    for (const auto& pair : results_set) {
        if (pair.first > high_score) {
            high_score = pair.first;
        }
    }

    // Output best scores
    std::cout << high_score << std::endl;
    for (const auto& pair : results_set) {
        if (pair.first == high_score) {
            std::cout << pair.second << std::endl;
        }
    }
    return 0;
}
