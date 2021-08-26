/* Jacob Kloepper
 * November 21, 2020
 * Kattis problem: genetics2
 *  Link: https://open.kattis.com/problems/genetics2
 */

#include <iostream>
#include <vector>

/* algorithm explanataion:
 * scan three DNA codes to find an incorrect sequence.
 * if the sample includes the correct, then 2 will be K chars off, and we can find the answer.
 * After we have an incorrect sequence, we scan the remaining DNA codes until we find the right one.
 */

// Given a code and an incorrect code, return their number of differences.
int get_diffs(const std::string &check, const std::string &incorrect) {
    int diffs {0};

    for (int ch {0}; ch < check.size(); ch++) {
        if (check.at(ch) != incorrect.at(ch)) {
            diffs++;
        }
    }

    return diffs;
}

// Given three codes, if all are incorrect return an incorrect code XOR if one is correct return it and its index.
std::pair<std::string, int> get_incorrect(const std::vector<std::string> &cases, int diffs) {
    std::pair<std::string, int> tmp_incorrect {};
    std::vector<bool> outcomes(3);
    int tmp_diff;

    // Checks
    // Check 0:
    tmp_diff = get_diffs(cases.at(0), cases.at(1));
    if (tmp_diff == diffs) {
        outcomes.at(0) = true;
    } else {
        outcomes.at(0) = false;
    }

    // Check 1:
    tmp_diff = get_diffs(cases.at(0), cases.at(2));
    if (tmp_diff == diffs) {
        outcomes.at(1) = true;
    } else {
        outcomes.at(1) = false;
    }

    // Check 2:
    tmp_diff = get_diffs(cases.at(1), cases.at(2));
    if (tmp_diff == diffs) {
        outcomes.at(2) = true;
    } else {
        outcomes.at(2) = false;
    }

    // Results
    // Case 0:
    if (outcomes.at(0) && outcomes.at(1)) {
        return {cases.at(0), 1};
    }
    // Case 1:
    if (outcomes.at(0) && outcomes.at(2)) {
        return {cases.at(1), 2};
    }
    // Case 2:
    if (outcomes.at(1) && outcomes.at(2)) {
        return {cases.at(2), 3};
    }
    return {cases.at(0), 0};
}

int main() {
    int cases {};
    int dna_length {};
    int diffs {};
    std::string code {};

    // Get inputs
    std::cin >> cases;
    std::cin >> dna_length;
    std::cin >> diffs;

    // Get an incorrect sequence
    std::vector<std::string> check {};
    std::pair<std::string, int> tmp_incorrect {};
    std::string incorrect {};

    for (int test {0}; test < 3; test++) {
        std::cin >> code;

        check.push_back(code);
    }
    tmp_incorrect = get_incorrect(check, diffs);

    // Check if a correct code was encountered.
    if (tmp_incorrect.second != 0) {
        std::cout << tmp_incorrect.second << std::endl;
        return 0;
    }
    incorrect = tmp_incorrect.first;

    // Scan DNA sequences against incorrect sequence
    int tmp_diffs;
    for (int test {3}; test < cases; test++) {
        std::cin >> code;
        tmp_diffs = get_diffs(code, incorrect);

        // If the correct code is found, output its index
        if (tmp_diffs == diffs) {
            std::cout << test+1 << std::endl;
            return 0;
        }
    }

    return 0;
}