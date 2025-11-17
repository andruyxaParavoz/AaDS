#include "linked_list.h"
#include <cmath>

void display_menu() {
    std::cout << "\n=== Polynomial Calculator ===\n";
    std::cout << "1. Create first polynomial manually\n";
    std::cout << "2. Create second polynomial manually\n";
    std::cout << "3. Create first polynomial with random values\n";
    std::cout << "4. Create second polynomial with random values\n";
    std::cout << "5. Display polynomials\n";
    std::cout << "6. Add polynomials\n";
    std::cout << "7. Add node to head\n";
    std::cout << "8. Add node to tail\n";
    std::cout << "9. Access node by index\n";
    std::cout << "10. Evaluate polynomial at x\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

void create_manual_polynomial(Polynomial& poly, const std::string& name) {
    poly = Polynomial();
    int node_count;
    std::cout << "Enter number of nodes for " << name << ": ";
    std::cin >> node_count;

    for (int i = 0; i < node_count; ++i) {
        int coeff, exp;
        std::cout << "Node " << i + 1 << " - coefficient: ";
        std::cin >> coeff;
        std::cout << "Node " << i + 1 << " - exponent: ";
        std::cin >> exp;

        add_node(poly, coeff, exp);
    }

    poly.sort_by_exponent();
    std::cout << name << " created: ";
    poly.display();
}

void create_random_polynomial(Polynomial& poly, const std::string& name) {
    size_t count;
    int max_exp;
    unsigned int seed;

    std::cout << "Enter number of random nodes for " << name << ": ";
    std::cin >> count;
    std::cout << "Enter maximum exponent: ";
    std::cin >> max_exp;
    std::cout << "Enter random seed: ";
    std::cin >> seed;
    poly = Polynomial(count, max_exp, seed);
    std::cout << name << " created: ";
    poly.display();
}

void add_node_to_head(Polynomial& poly, const std::string& name) {
    int coeff, exp;
    std::cout << "Enter coefficient for " << name << ": ";
    std::cin >> coeff;
    std::cout << "Enter exponent for " << name << ": ";
    std::cin >> exp;
    add_node(poly, coeff, exp);
    poly.sort_by_exponent();
    std::cout << "Updated " << name << ": ";
    poly.display();
}

void add_node_to_tail(Polynomial& poly, const std::string& name) {
    int coeff, exp;
    std::cout << "Enter coefficient for " << name << ": ";
    std::cin >> coeff;
    std::cout << "Enter exponent for " << name << ": ";
    std::cin >> exp;
    add_node(poly, coeff, exp);
    poly.sort_by_exponent();
    std::cout << "Updated " << name << ": ";
    poly.display();
}

void access_node_by_index(const Polynomial& poly, const std::string& name) {
    if (poly.is_empty()) {
        std::cout << name << " is empty!\n";
        return;
    }

    size_t index;
    std::cout << "Enter index for " << name << " (0 to " << poly.get_size() - 1 << "): ";
    std::cin >> index;

    try {
        const Node& node = poly[index];
        std::cout << "Node at index " << index << " in " << name << ": "
            << node.coefficient << "x^" << node.exponent << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void add_node(Polynomial& poly, int coefficient, int exponent) {
    if (coefficient == 0) return;

    Node* current = poly.get_head();
    if (current) {
        do {
            if (current->exponent == exponent) {
                current->coefficient += coefficient;
                if (current->coefficient == 0) {
                    poly.delete_node(exponent);
                }
                return;
            }
            current = current->next;
        } while (current != poly.get_head());
    }
    poly.push_tail(coefficient, exponent);
}

double evaluate_polynomial(const Polynomial& poly, double x) {
    double result = 0.0;
    for (size_t i = 0; i < poly.get_size(); ++i) {
        const Node& node = poly[i];
        result += node.coefficient * std::pow(x, node.exponent);
    }
    return result;
}

int main() {
    Polynomial poly1, poly2, result;
    int choice;

    do {
        display_menu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            create_manual_polynomial(poly1, "first polynomial");
            break;
        case 2:
            create_manual_polynomial(poly2, "second polynomial");
            break;
        case 3:
            create_random_polynomial(poly1, "first polynomial");
            break;
        case 4:
            create_random_polynomial(poly2, "second polynomial");
            break;
        case 5:
            std::cout << "First polynomial: ";
            poly1.display();
            std::cout << "Second polynomial: ";
            poly2.display();
            break;
        case 6:
            result = poly1 + poly2;
            std::cout << "First polynomial: ";
            poly1.display();
            std::cout << "Second polynomial: ";
            poly2.display();
            std::cout << "Sum: ";
            result.display();
            break;
        case 7: {
            int poly_choice;
            std::cout << "Add node to head of which polynomial? (1/2): ";
            std::cin >> poly_choice;
            if (poly_choice == 1) add_node_to_head(poly1, "first polynomial");
            else if (poly_choice == 2) add_node_to_head(poly2, "second polynomial");
            else std::cout << "Invalid choice!\n";
            break;
        }
        case 8: {
            int poly_choice;
            std::cout << "Add node to tail of which polynomial? (1/2): ";
            std::cin >> poly_choice;
            if (poly_choice == 1) add_node_to_tail(poly1, "first polynomial");
            else if (poly_choice == 2) add_node_to_tail(poly2, "second polynomial");
            else std::cout << "Invalid choice!\n";
            break;
        }
        case 9: {
            int poly_choice;
            std::cout << "Access node from which polynomial? (1/2): ";
            std::cin >> poly_choice;
            if (poly_choice == 1) access_node_by_index(poly1, "first polynomial");
            else if (poly_choice == 2) access_node_by_index(poly2, "second polynomial");
            else std::cout << "Invalid choice!\n";
            break;
        }
        case 10: {
            int poly_choice;
            std::cout << "Evaluate which polynomial? (1/2): ";
            std::cin >> poly_choice;
            double x;
            std::cout << "Enter value of x: ";
            std::cin >> x;
            if (poly_choice == 1) std::cout << "Value: " << evaluate_polynomial(poly1, x) << "\n";
            else if (poly_choice == 2) std::cout << "Value: " << evaluate_polynomial(poly2, x) << "\n";
            else std::cout << "Invalid choice!\n";
            break;
        }
        case 0:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid option!\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
