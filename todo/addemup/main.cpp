#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>

class Card {
private:
    unsigned long face_num;
    unsigned long flip_num;
    bool flippable;

    char rotate_digit(char digit);

    void check_flippable();
    unsigned long get_flip();

public:
    Card(unsigned long number);

    unsigned long get_face_num();
    unsigned long get_flip_num();
    bool get_flippable();

    void print();

};

char Card::rotate_digit(char digit) {
    switch (digit) {
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '9';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '6';
            break;
        case 0:
            return '0';
            break;
        default:
            return '3';
            break;
    }
}

void Card::check_flippable() {
    for (char digit : std::to_string(face_num)) {
        if (digit == '3' || digit == '4' || digit == '7') {
            flippable = false;
        }
    }
    flippable = true;
}

unsigned long Card::get_flip() {
    std::string flipped_num{};
    std::string _tmp {std::to_string(face_num)};
    // Rotate numbers
    for (char digit : _tmp) {
        flipped_num.push_back(rotate_digit(digit - '0'));
    }

    // Reverse order of numbers
    reverse(flipped_num.begin(), flipped_num.end());

    return std::stoi(flipped_num);
}

Card::Card(unsigned long number) {
    face_num = number;
    check_flippable();

    if (flippable) {
        flip_num = get_flip();
    }
    else {
        flip_num = 3; // Lowest impossible value for flip_num. Use as magic num.
    }
}

unsigned long Card::get_face_num() {
    return face_num;
}

unsigned long Card::get_flip_num() {
    return flip_num;
}

bool Card::get_flippable() {
    return flippable;
}

void Card::print() {
    if (flip_num != 3) {
        std::cout << "Card: " << face_num << " | " << flip_num << std::endl;
    }
    else {
        std::cout << "Card: " << face_num << std::endl;
    }
}

// Check all permutations of additions for the two cards
bool check_sum(Card card1, Card card2, const unsigned long sum) {
    // Four cases: either card can be flippable or not.
    // Case 1: both flippable (00)
    if (card1.get_flippable() && card2.get_flippable()) {
        if (card1.get_face_num() + card2.get_face_num() == sum) return true;
        else if (card1.get_face_num() + card2.get_flip_num() == sum) return true;
        else if (card1.get_flip_num() + card2.get_face_num() == sum) return true;
        else if (card1.get_flip_num() + card2.get_flip_num() == sum) return true;
    }
    // Case 2: 01
    else if (card1.get_flippable() && !card2.get_flippable()) {
        if (card1.get_face_num() + card2.get_face_num() == sum) return true;
        else if (card1.get_flip_num() + card2.get_face_num() == sum) return true;
    }
    // Case 3: 10
    else if (!card1.get_flippable() && card2.get_flippable()) {
        if (card1.get_face_num() + card2.get_face_num() == sum) return true;
        else if (card1.get_face_num() + card2.get_flip_num() == sum) return true;
    }
    // Case 4: 11
    else if (!card1.get_flippable() && !card2.get_flippable()) {
        if (card1.get_face_num() + card2.get_face_num() == sum) return true;
    }
    return false;
}

void run_test(const std::vector<Card>& cards, const unsigned long& sum) {
    std::string msg{ "NO" };

    for (size_t i{ 0 }; i < cards.size() - 1; i++) {
        if (check_sum(cards[i], cards[i + 1], sum)) {
            msg = "YES";
            break;
        }
    }
    std::cout << msg << std::endl;
}

int main() {
    unsigned long n;
    unsigned long sum;

    std::cin >> n;
    std::cin >> sum;

    std::vector<Card> cards{};
    unsigned long _tmpval;
    for (unsigned long i{ 0 }; i < n; i++) {
        std::cin >> _tmpval;
        cards.push_back(Card(_tmpval));
    }

    run_test(cards, sum);

    return 0;
}