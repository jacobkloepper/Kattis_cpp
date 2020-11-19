/* Jacob Kloepper
 * November 19, 2020
 * Kattis problem: uxuhulvoting
 *  Link: https://open.kattis.com/problems/uxuhulvoting
 */

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <bitset>

// TODO: write this better / show more clearly in an image
/* algorithm explanation:
 * Represent states as binary.
 * A turn results in a single bit flip.
 * see tree.PNG.
 * Don't use a tree because upper bound of 100 priests (ie., a tree of depth 100)
 * Instead, build an algorithm that decides what each priest will point to from each node based of prefs.
 * Start from the bottom up, because the last priest's vote matters most.
 *
 * The possible outcome set depends on the depth.
 * d = 0: {0}
 * d = 1: {1,2,4}
 * d > 1 && d % 2 == 0: {0,3,5,6}
 * d > 1 && d % 2 == 1: {1,2,4,7}
 *
 * Pseudocode:
 *      let p[n-1] be the last priest.
 *      let S be the solution set based on d.
 *      let O(4) be p[n-1]'s best possible outcomes for each of the previous nodes
 *          eg. if d is odd, O[0] will be the preference from node 0, O[1] will be from node 3, etc.
 *          note: for d=0 or d=1, set invalid indices to -1
 *      choose node based on p[n-2]'s chosen node.
 *      RETURN
 *
 *      let p[n-2] be the second last priest.
 *      let Q be the remaining solution set (a subset of S, all elements in p[n-1]'s O)
 *      let O be p[n-2]'s best possible outcomes from Q
 *      choose node based on p[n-3]'s chosen node.
 *
 *      ...
 *
 *      let p[0] be the first priest.
 *      let S be the solution set based on d.
 *      let O(4) be p[0]'s best possible outcomes from the second last depth nodes.
 *
 */

class Node;

class Node {
    unsigned int value{};
    std::set<int> potential_next{};
    std::set<int> possible_outcomes;
    std::vector<int> prefs{};

    unsigned int current_depth {};
    unsigned int tree_depth{};
    std::shared_ptr<Node> prev{}; // maybe not needed?
    std::shared_ptr<Node> next{};

public:
    Node(unsigned int n, unsigned int curr_d, unsigned int d, const std::vector<int> &input_prefs) {
        value = n;
        set_potential_next();
        current_depth = curr_d;
        tree_depth = d;
        set_possible_outcomes();
        prefs = input_prefs;
    }

    unsigned int get_value() {
        return value;
    } // Maybe not needed.

    std::shared_ptr<Node> get_next() {
        return next;
    }

    // TODO: the big issue.
    // Based on value, potential_next, possible_outcomes, and prefs, set the next.
    // But you also need the prefs of other nodes.
    unsigned int vote() {
        // each node has its own preferences.

        // last node
        if (current_depth == tree_depth-1) {
            for (auto p : prefs) {
                if (potential_next.find(p) != potential_next.end()) {
                    return p;
                }
            }
        }

        return 0;
    }

    void set_next(Node next_node) {
        next = std::make_shared<Node>(next_node.vote(), next_node.current_depth + 1, next_node.tree_depth, next_node.prefs);
    }

private:
    void set_potential_next() {
        switch (value) {
            case 0:
                potential_next.insert(1);
                potential_next.insert(2);
                potential_next.insert(4);
                break;
            case 1:
                potential_next.insert(0);
                potential_next.insert(3);
                potential_next.insert(5);
                break;
            case 2:
                potential_next.insert(0);
                potential_next.insert(3);
                potential_next.insert(6);
                break;
            case 3:
                potential_next.insert(1);
                potential_next.insert(2);
                potential_next.insert(7);
                break;
            case 4:
                potential_next.insert(0);
                potential_next.insert(5);
                potential_next.insert(6);
                break;
            case 5:
                potential_next.insert(1);
                potential_next.insert(4);
                potential_next.insert(7);
                break;
            case 6:
                potential_next.insert(2);
                potential_next.insert(4);
                potential_next.insert(7);
                break;
            case 7:
                potential_next.insert(3);
                potential_next.insert(5);
                potential_next.insert(6);
                break;
            default:
                std::cout << "Invalid node." << std::endl;
                delete this; // Is this right?
        }
    }
    void set_possible_outcomes() {
        if (tree_depth == 0) {
            possible_outcomes.insert(0);
            possible_outcomes.insert(-1);
            possible_outcomes.insert(-1);
            possible_outcomes.insert(-1);
        } else if (tree_depth == 1) {
            possible_outcomes.insert(1);
            possible_outcomes.insert(2);
            possible_outcomes.insert(4);
            possible_outcomes.insert(-1);
        } else if (tree_depth % 2 == 0) {
            possible_outcomes.insert(0);
            possible_outcomes.insert(3);
            possible_outcomes.insert(5);
            possible_outcomes.insert(6);
        } else if (tree_depth % 2 == 1) {
            possible_outcomes.insert(1);
            possible_outcomes.insert(2);
            possible_outcomes.insert(4);
            possible_outcomes.insert(7);
        }
    }
};

std::string interpret_outcome(unsigned int outcome) {
    if (outcome > 7) {
        std::cout << "Outcome must be on range [0, 7]. Given outcome: " << outcome << std::endl;
        return {};
    }
    std::string bits {std::bitset<3>(outcome).to_string()};
    std::string votes {};

    for (auto b : bits) {
        if (b == '0') {
            votes.push_back('N');
        } else if (b == '1') {
            votes.push_back('Y');
        }
    }
    return votes;
}

int main() {
    unsigned int rounds {0};
    unsigned int priests {0}; // also equals depth of tree
    unsigned int outcome {};
    unsigned int current_vote {0};

    std::vector<std::vector<int>> prefs_list {};
    int tmp_pref {};

    std::vector<Node> nodes {};

    std::cin >> rounds;
    std::cin >> priests;

    for (int i {0}; i < rounds; i++) {
        // Get preference list
        for (int voter {0}; voter < priests; voter++) {
            prefs_list.emplace_back();
            for (int pref {0}; pref < 8; pref++) {
                std::cin >> tmp_pref;
                prefs_list.at(voter).emplace_back(tmp_pref-1);
            }
        }

        // Fill a vector of skeleton nodes
        for (int count {0}; count < priests; count++) {
            Node tmp_node = Node(current_vote, count, priests, prefs_list.at(count)); // First voter
            nodes.emplace_back(tmp_node);
        }

        // TODO: connect node 0 to node 1 by prefs.
        // TODO: get the algorithm to do so.
        // TODO: on exactly what does node i's choice depend? The rest of the tree?

        // Send output
        std::cout << interpret_outcome(outcome) << std::endl;
    }

    return 0;
}
