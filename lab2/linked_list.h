#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <random>

struct Term {
    double coefficient;
    int exponent;
    Term* next;

    Term(double coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

class Polynomial {
private:
    Term* head;
    size_t size;

    void clear() {
        while (!is_empty()) {
            pop_head();
        }
    }

public:
    Polynomial() : head(nullptr), size(0) {}

    Polynomial(const Polynomial& other) : head(nullptr), size(0) {
        Term* current = other.head;
        if (current) {
            do {
                push_tail(current->coefficient, current->exponent);
                current = current->next;
            } while (current != other.head);
        }
    }

    Polynomial(size_t count, int max_exponent, unsigned int seed = 0) : head(nullptr), size(0) {
        std::mt19937 gen(seed == 0 ? std::random_device{}() : seed);
        std::uniform_real_distribution<double> coeff_dist(-10.0, 10.0);
        std::uniform_int_distribution<int> exp_dist(0, max_exponent);

        for (size_t i = 0; i < count; ++i) {
            double coeff = coeff_dist(gen);
            int exp = exp_dist(gen);
            if (coeff != 0) {
                push_tail(coeff, exp);
            }
        }
        sort_by_exponent();
    }

    ~Polynomial() {
        clear();
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            clear();
            Term* current = other.head;
            if (current) {
                do {
                    push_tail(current->coefficient, current->exponent);
                    current = current->next;
                } while (current != other.head);
            }
        }
        return *this;
    }

    void push_tail(double coefficient, int exponent) {
        if (coefficient == 0) return;

        Term* new_term = new Term(coefficient, exponent);

        if (!head) {
            head = new_term;
            head->next = head;
        }
        else {
            Term* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = new_term;
            new_term->next = head;
        }
        ++size;
    }

    void push_tail(const Polynomial& other) {
        if (!other.head) return;

        Term* current = other.head;
        do {
            push_tail(current->coefficient, current->exponent);
            current = current->next;
        } while (current != other.head);
        sort_by_exponent();
    }

    void push_head(double coefficient, int exponent) {
        if (coefficient == 0) return;

        Term* new_term = new Term(coefficient, exponent);

        if (!head) {
            head = new_term;
            head->next = head;
        }
        else {
            Term* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            new_term->next = head;
            head = new_term;
            tail->next = head;
        }
        ++size;
    }

    void push_head(const Polynomial& other) {
        if (!other.head) return;

        Polynomial temp = other;
        Term* current = temp.head;
        do {
            push_head(current->coefficient, current->exponent);
            current = current->next;
        } while (current != temp.head);
        sort_by_exponent();
    }

    void pop_head() {
        if (!head) {
            throw std::runtime_error("Cannot pop from empty polynomial");
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Term* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            Term* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        --size;
    }

    void pop_tail() {
        if (!head) {
            throw std::runtime_error("Cannot pop from empty polynomial");
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
        }
        else {
            Term* current = head;
            while (current->next->next != head) {
                current = current->next;
            }
            Term* temp = current->next;
            current->next = head;
            delete temp;
        }
        --size;
    }

    Term& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Term* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return *current;
    }

    const Term& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Term* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return *current;
    }

    void delete_term(int exponent) {
        if (!head) return;

        Term* current = head;
        Term* prev = nullptr;

        do {
            if (current->exponent == exponent) {
                if (current == head) {
                    pop_head();
                    current = head;
                    if (!head) break;
                }
                else {
                    Term* temp = current;
                    prev->next = current->next;
                    current = current->next;
                    delete temp;
                    --size;
                }
            }
            else {
                prev = current;
                current = current->next;
            }
        } while (current != head && head);
    }

    bool is_empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    void display() const {
        if (is_empty()) {
            std::cout << "0";
            return;
        }

        Term* current = head;
        bool first_term = true;

        do {
            if (current->coefficient > 0 && !first_term) {
                std::cout << " + ";
            }
            else if (current->coefficient < 0) {
                std::cout << " - ";
            }

            double abs_coeff = std::abs(current->coefficient);

            if (current->exponent == 0) {
                std::cout << abs_coeff;
            }
            else if (current->exponent == 1) {
                if (abs_coeff == 1) {
                    std::cout << "x";
                }
                else {
                    std::cout << abs_coeff << "x";
                }
            }
            else {
                if (abs_coeff == 1) {
                    std::cout << "x^" << current->exponent;
                }
                else {
                    std::cout << abs_coeff << "x^" << current->exponent;
                }
            }

            first_term = false;
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this;

        Term* current = other.head;
        if (current) {
            do {
                result.add_term(current->coefficient, current->exponent);
                current = current->next;
            } while (current != other.head);
        }

        return result;
    }

    void add_term(double coefficient, int exponent) {
        if (coefficient == 0) return;

        if (!head) {
            push_tail(coefficient, exponent);
            return;
        }

        Term* current = head;
        bool found = false;

        do {
            if (current->exponent == exponent) {
                double new_coeff = current->coefficient + coefficient;
                if (new_coeff == 0) {
                    delete_term(exponent);
                }
                else {
                    current->coefficient = new_coeff;
                }
                found = true;
                break;
            }
            current = current->next;
        } while (current != head);

        if (!found) {
            push_tail(coefficient, exponent);
        }
    }

    void sort_by_exponent() {
        if (!head || head->next == head) return;

        bool swapped;
        do {
            swapped = false;
            Term* current = head;
            Term* prev = nullptr;

            do {
                Term* next = current->next;
                if (next != head && current->exponent < next->exponent) {
                    if (current == head) {
                        head = next;
                    }

                    if (prev) {
                        prev->next = next;
                    }
                    current->next = next->next;
                    next->next = current;

                    swapped = true;
                }
                prev = current;
                current = next;
            } while (current != head);
        } while (swapped);
    }
};

#endif