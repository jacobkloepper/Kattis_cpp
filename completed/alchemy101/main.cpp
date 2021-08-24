/*	Jacob Kloepper
	August 23, 2021
	Kattis problem: alchemy101
		Link: https://open.kattis.com/problems/alchemy101
*/


#include <iostream>

int main() {
    int num_tests{};
    int m{};

    std::cin >> num_tests;
	
	/*
		Idea: The sequential XORing of natural numbers has some key patterns. Let ^[1..m] denote this function (ie., ^[1..m] := 1^2^3^...^(m-1)^m).
			1. For m | m%4==0: ^[1..m] = m
			2. For m | m%4==1: ^[1..4*floor(m/4)-1,m] = m
			3. For m | m%4==2: ^[2..m] = m
			4. For m | m%4==3: ^[1..(m-1)] = m 
			
			To illustrate, consider:
			
			   Dec  |   Bin     |   Sequential XOR	|  m%4	|
			-------------------------------------------------
				1	|	0001	|	1		0001	|	1	|
				2	|	0010	|	2		0011	|	2	|
				3	|	0011	|	0		0000	|	3	|
				4	|	0100	|	4		0100	|	0	|
				5	|	0101	|	1		0001	|	1	|
				6	|	0110	|	7		0111	|	2	|
				7	|	0111	|	0		0000	|	3	|
				8	|	1000	|	8		1000	|	4	|
				
			If it is unclear, play with it. Try to see how each equation above relates. Hint: (4) directly gives you (1), and (3) is a little weird.
			
		We are confident that equations (1-4) provide the largest solution sets.
	*/

    // integer division of positives returns the floor.
    for (int test{}; test < num_tests; test++) {
        std::cin >> m;

        // Print the size of the solution set:
        // Case 1: m % 4 == 3
        if (m % 4 == 3) {
            std::cout << m-1 << std::endl;
        } 
        // Case 2: m % 4 == 2
        else if (m % 4 == 2) {
            std::cout << m-1 << std::endl;
        }
        // Case 3: m%4!=3 and m%4!=2 and m < 4
        else if ((m / 4) * 4 == 0) {
            std::cout << 1 << std::endl;
        }
        // Case 4: m%4!=3 and m%4!=2 and m >= 4
        else {
            std::cout << (m / 4) * 4 << std::endl;
        }

        // Print the solution set:
        // Case 1: m%4==3
        if (m % 4 == 3) {
            for (int i{ 1 }; i < m; i++) {
                if (i != m - 1) {
                    std::cout << i << " ";
                }
                else {
                    std::cout << i;
                }
            }
            std::cout << std::endl;
        } 
        // Case 2: m%4==2
        else if (m % 4 == 2) {
            for (int i{ 2 }; i < m+1; i++) {
                if (i != m) {
                    std::cout << i << " ";
                }
                else {
                    std::cout << i;
                }
            }
            std::cout << std::endl;
        }
        // Case 3: m%4!=3 and m%4!=2
        else {
            for (int i{ 1 }; i < (m / 4) * 4; i++) {
                std::cout << i << " ";
            }
            std::cout << m << std::endl;
        }
    }

    return 0;
}