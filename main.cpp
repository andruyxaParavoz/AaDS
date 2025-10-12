#include <iostream>
#include "set.h"

template <typename T>
Set<T> exclusive_elements(const Set<T>& a, const Set<T>& b) {
	Set<T> union_set = a + b;
	Set<T> inter = a.intersection(b);
	return union_set - inter;
}

int main() {
	try {
		//for int
		Set<int> s1(5, 1, 10);
		Set<int> s2(5, 5, 15);

		std::cout << "Set 1: " << s1 << '\n';
		std::cout << "Set 2: " << s2 << "\n\n";

		Set<int> unique = exclusive_elements(s1, s2);
		std::cout << "Unique elements: " << unique << "\n\n";

		s1 += 100;
		std::cout << "After add 100: " << s1 << '\n';

		s1 -= 100;
		std::cout << "After rm 100: " << s1 << "\n\n";

		std::cout << "Intercection: " << s1.intersection(s2) << "\n\n";

		//for float
		Set<float> fset(5, 0.0f, 5.0f);
		std::cout << "Set: " << fset << "\n\n";

		//for string
		const std::string arr[] = { "apple", "banana", "apple", "cucumber" };
		Set<std::string> strset(arr, 4);
		std::cout << "Str set: " << strset << "\n\n";

		//for pair
		std::pair<int, double> parr[] = { {1, 2.0}, {1, 2.0}, {2, 3.0} };
		Set <std::pair<int, double>> pairset(parr, 3);
		std::cout << "Pair set: " << pairset << "\n\n";
	}
	catch (const std::exception& e) { std::cerr << "Error: " << e.what() << '\n'; }
}