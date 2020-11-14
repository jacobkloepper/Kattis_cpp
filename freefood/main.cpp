/* Jacob Kloepper
 * November 14, 2020
 * Kattis problem: freefood
 *  Link: https://open.kattis.com/problems/freefood
*/

#include <iostream>
#include <set>

/* algorithm explanation:
 * We are looking for the size of the union of N sets
 * std::set is a natural choice for container as it features unique members.
 */

int main() {
    unsigned int num_events {};
    unsigned int event_start {};
    unsigned int event_end {};
    std::set<unsigned int> serving_days {};

    std::cin >> num_events;

    for (int i {0}; i < num_events; i++) {
        std::cin >> event_start >> event_end;

        // Check event bounds
        if (event_start < 0 || event_end < 0 || event_start > 365 || event_end > 365) {
            std::cout << "Invalid event bounds" << std::endl;
            return 1;
        }

        // Insert days on which food are served
        for (unsigned int num {event_start}; num <= event_end; num++) {
            serving_days.insert(num);
        }
    }

    std::cout << serving_days.size() << std::endl;

    return 0;
}