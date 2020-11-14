/* Jacob Kloepper
 * November 13, 2020
 * Kattis problem: faktor
 */

#include <iostream>
#include <cmath>

int main() {
    // Get inputs
    double num_articles {0};
    double impact {0};
    std::cin >> num_articles;
    std::cin >> impact;

    // Get required citation number
    double citations {impact*num_articles}; // upper bound
    while (std::ceil((citations)/num_articles) >= impact) {
        citations--; // Check each value for citations, incrementing down
    }
    citations++; // Fix the final decrement

    std::cout << citations;

    return 0;
}
