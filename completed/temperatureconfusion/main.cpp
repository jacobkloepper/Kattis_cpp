/* Jacob Kloepper
 * November 21, 2020
 * Kattis problem: temperatureconfusion
 *  Link: https://open.kattis.com/problems/temperatureconfusion
 */

#include <iostream>

// I wrote this class from an earlier school assignment.
// Edited slightly to fit my needs here
class Rational {
public:
    // Default constructor: Rational = 0
    Rational() {
        numerator = 0;
        denominator = 1;
    }
    // Custom constructor
    Rational(int tmp_numerator, int tmp_denominator) {
        if (tmp_denominator == 0) {
            throw std::runtime_error("Invalid rational, denominator cannot be zero.");
        }
        numerator = tmp_numerator;
        denominator = tmp_denominator;

        reduce();
    };

    // Add rational to rational
    Rational operator+(const Rational &x) const {
        Rational sum{};

        sum.numerator = ((this->numerator) * (x.denominator) + (x.numerator) * (this->denominator));
        sum.denominator = (this->denominator) * (x.denominator);

        sum.reduce();
        return sum;
    }

    // Subtract rational from rational
    Rational operator-(const Rational &x) const {
        Rational difference{};

        difference.numerator = ((this->numerator) * (x.denominator) - (x.numerator) * (this->denominator));
        difference.denominator = (this->denominator) * (x.denominator);

        difference.reduce();
        return difference;
    }

    // Multiply rationals
    Rational operator*(const Rational &x) const {
        Rational product{};

        product.numerator = (this->numerator * x.numerator);
        product.denominator = (this->denominator * x.denominator);

        product.reduce();
        return product;
    }

    // Divide rationals
    Rational operator/(const Rational &x) const {
        if (x.numerator == 0) {
            throw std::runtime_error("Cannot divide by zero");
        }
        Rational quotient{};

        quotient.numerator = (this->numerator * x.denominator);
        quotient.denominator = (this->denominator * x.numerator);

        quotient.reduce();
        return quotient;
    }

    // Reduces the object to lowest form
    void reduce() {
        int GCD {};

        // Euclid's algorithm for GCD's:
        int a {numerator};
        int b {denominator};
        int remainder{a % b};

        while (remainder != 0) {
            a = b;
            b = remainder;
            remainder = a % b;
        }

        GCD = b;

        // Reduce the rational
        numerator /= GCD;
        denominator /= GCD;
    }

    void edit_form() {
        if (numerator > 0 && denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }


    // Print value of rational
    void print() {
        edit_form();
        std::cout << numerator << "/" << denominator << std::endl;
    }

private:
    int numerator{};
    int denominator{};
};

Rational convert_F_to_C(Rational temp_F) {
    Rational coefficient(5, 9);
    Rational term(32, 1);
    return coefficient * (temp_F - term);
}

int main() {
    // Get input, parse into numerator and denominator
    std::string str {};
    std::cin >> str;

    auto pos = str.find('/');
    int numerator {std::stoi(str.substr(0, pos))};
    int denominator {std::stoi(str.substr(pos + 1))};

    // Output converted temperature
    Rational input(numerator,denominator);
    convert_F_to_C(input).print();

    return 0;
}
