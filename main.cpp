#include <iostream>
#include "set.h"
#include "io_utils.h"

int main() {
    try {
        setup_io();
        std::cout << "=== Set<int> ===\n";
        Set<int> a(6, 1, 10);
        Set<int> b(6, 5, 15);
        std::cout << "A: " << a << '\n';
        std::cout << "B: " << b << '\n';

        Set<int> union_set = a + b;
        std::cout << "A + B (union): " << union_set << '\n';

        Set<int> diff_set = a - b;
        std::cout << "A - B (difference): " << diff_set << '\n';

        Set<int> inter = a.intersection(b);
        std::cout << "A ∩ B(intersection) : " << inter << '\n';

        a += 100;
        std::cout << "A after adding 100: " << a << '\n';

        a -= 100;
        std::cout << "A after removing 100: " << a << '\n';

        std::cout << "Does A contain 5? " << (a.contains(5) ? "Yes" : "No") << '\n';
        std::cout << "Does B contain 5? " << (b.contains(5) ? "Yes" : "No") << '\n';

        std::cout << "A == B ? " << ((a == b) ? "Yes" : "No") << '\n';
        std::cout << "A != B ? " << ((a != b) ? "Yes" : "No") << '\n';

        std::cout << "A[0] = " << a[0] << '\n';
        std::cout << "B[3] = " << b[3] << '\n';

        try {
            std::cout << "\nTrying to access out-of-range index...\n";
            std::cout << a[50];
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << '\n';
        }

        std::cout << "\n=== Set<float> ===\n";
        Set<float> f1(3, 0.0f, 5.0f);
        std::cout << "F1: " << f1 << '\n';

        std::cout << "\n=== Set<string> ===\n";
        Set<std::string> s1({ "apple", "banana", "orange" });
        Set<std::string> s2({ "banana", "kiwi" });
        std::cout << "S1: " << s1 << '\n';
        std::cout << "S2: " << s2 << '\n';
        std::cout << "S1 - S2: " << (s1 - s2) << '\n';

        std::cout << "\n=== Set<pair<int,double>> ===\n";
        Set<std::pair<int, double>> p1({ {1,1.1}, {2,2.2}, {3,3.3} });
        Set<std::pair<int, double>> p2({ {2,2.2}, {4,4.4} });
        std::cout << "P1: " << p1 << '\n';
        std::cout << "P2: " << p2 << '\n';
        std::cout << "P1 ∩ P2: " << p1.intersection(p2) << '\n';

        std::cout << "\n=== Main task: Elements unique to one of two arrays ===\n";
        Set<int> unique = (a - b) + (b - a);
        std::cout << "Unique elements: " << unique << '\n';

    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << '\n';
    }

    return 0;
}