#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>

/*
	Given an input float dec on [0,1], return the ternary representation.
	Needs to detect repeats (track r somewhere)
*/
std::string dec_to_tern(const float& dec) {
	float _frac{ dec };
	std::stringstream result{};
	int q{};
	float r{};

	// First iteration: always 0.x...
	q = int(_frac);
	r = _frac - q;
	_frac = 3 * r;
	result << "0.";

	int i{ 10 }; //db
	while (i > 0) {
		q = int(_frac); // maybe need an std::floor?
		r = _frac - q;
		_frac = 3 * r;

		result << q;

		i--; // the i is for debugging
	}

	return result.str();
}

int main() {
	float val { 0.875 };
	std::string str{};

	str = dec_to_tern(val);

	std::cout << str << std::endl;
	return 0;
}
