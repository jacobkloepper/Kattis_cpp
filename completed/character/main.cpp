/* Kattis problem: character
    Link: https://open.kattis.com/problems/character
    24 August 2021
*/

#include <iostream>

/* Explanation:
    To find the number of subsets of s:[0,N] with size 2 or more, find all subsets of S and remove the invalid ones.
    All subsets: binary representations with N bits. 1's are in the subset and 0's are not.

    eg. N=4:

        0000    <-- invalid
        0001    <-- invalid
        0010    <-- invalid
        0011
        0100    <-- invalid
        0101
        0110
        0111
        1000    <-- invalid
        1001
        1010
        1011
        1100
        1101
        1110
        1111

    We note that the only invalid subsets are powers of two (also zero). Therefore, given N bits, the total number of
    subsets with size greater or equal to 2 is 2^N-N-1.
*/

int main() {
    uint16_t _num {0};
    uint32_t subs {1};

    // _num on [0,30]
    std::cin >> _num;

    std::cout << ((subs<<_num)-_num-1) << std::endl;

    return 0;
}