#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <random>

struct Node;
class Polynomial;
void add_node(Polynomial& poly, int coefficient, int exponent);

struct Node {
    int coefficient;
    int exponent;
    Node* next;

    Node(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

class Polynomial {
private:
    Node* head;
    Node* tail;
    size_t size;

    void clear() {
        while (!is_empty()) {
            pop_head();
        }
    }

public:
    //def
    Polynomial() : head(nullptr), tail(nullptr), size(0) {}

    //cpy
    Polynomial(const Polynomial& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        if (current) {
            do {
                push_tail(current->coefficient, current->exponent);
                current = current->next;
            } while (current != other.head);
        }
    }

    //rndm
    Polynomial(size_t count, int max_exponent, unsigned int seed = 0) : head(nullptr), tail(nullptr), size(0) {
        std::mt19937 gen(seed == 0 ? std::random_device{}() : seed);
        std::uniform_int_distribution<int> coeff_dist(-10, 10);
        std::uniform_int_distribution<int> exp_dist(0, max_exponent);

        for (size_t i = 0; i < count; ++i) {
            int coeff = coeff_dist(gen);
            int exp = exp_dist(gen);
            if (coeff != 0) {
                push_tail(coeff, exp);
            }
        }
        sort_by_exponent();
    }

    //dstr
    ~Polynomial() {
        clear();
    }

    //1
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            if (current) {
                do {
                    push_tail(current->coefficient, current->exponent);
                    current = current->next;
                } while (current != other.head);
            }
        }
        return *this;
    }

    //2
    Node& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return *current;
    }

    //3
    const Node& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return *current;
    }

    //4
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;

        Node* current = head;
        if (current) {
            do {
                add_node(result, current->coefficient, current->exponent);
                current = current->next;
            } while (current != head);
        }

        current = other.head;
        if (current) {
            do {
                add_node(result, current->coefficient, current->exponent);
                current = current->next;
            } while (current != other.head);
        }

        result.sort_by_exponent();
        return result;
    }

    //1
    void push_tail(int coefficient, int exponent) {
        if (coefficient == 0) return;
        Node* current = head;
        if (current) {
            do {
                if (current->exponent == exponent) {
                    current->coefficient += coefficient;
                    if (current->coefficient == 0) delete_node(exponent);
                    return;
                }
                current = current->next;
            } while (current != head);
        }

        Node* node = new Node(coefficient, exponent);
        if (!head) {
            head = tail = node;
            node->next = node;
        }
        else {
            tail->next = node;
            node->next = head;
            tail = node;
        }
        ++size;
    }

    //2
    void push_tail(const Polynomial& other) {
        if (!other.head) return;

        Node* current = other.head;
        do {
            push_tail(current->coefficient, current->exponent);
            current = current->next;
        } while (current != other.head);
        sort_by_exponent();
    }

    //3
    void push_head(int coefficient, int exponent) {
        if (coefficient == 0) return;
        Node* current = head;
        if (current) {
            do {
                if (current->exponent == exponent) {
                    current->coefficient += coefficient;
                    if (current->coefficient == 0) delete_node(exponent);
                    return;
                }
                current = current->next;
            } while (current != head);
        }

        Node* node = new Node(coefficient, exponent);
        if (!head) {
            head = tail = node;
            node->next = node;
        }
        else {
            node->next = head;
            head = node;
            tail->next = head;
        }
        ++size;
    }

    //4
    void push_head(const Polynomial& other) {
        if (!other.head) return;

        Polynomial temp = other;
        Node* current = temp.head;
        do {
            push_head(current->coefficient, current->exponent);
            current = current->next;
        } while (current != temp.head);
        sort_by_exponent(); 
    }

    //5
    void pop_head() {
        if (!head) throw std::runtime_error("Cannot pop from empty polynomial");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* tmp = head;
            head = head->next;
            tail->next = head;
            delete tmp;
        }
        --size;
    }


    //6
    void pop_tail() {
        if (!head) throw std::runtime_error("Cannot pop from empty polynomial");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;
            while (current->next != tail) current = current->next;
            current->next = head;
            delete tail;
            tail = current;
        }
        --size;
    }

    //7
    void delete_node(int exponent) {
        if (!head) return;

        Node* current = head;
        Node* prev = nullptr;

        do {
            if (current->exponent == exponent) {
                if (current == head) {
                    pop_head();
                    current = head;
                    if (!head) break;
                }
                else {
                    Node* temp = current;
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

    //8
    bool is_empty() const {
        return size == 0;
    }

    //9
    size_t get_size() const {
        return size;
    }

    //10
    Node* get_head() { return head; }
    
    //11
    Node* get_tail() { return tail; }

    //12
    void display() const {
        if (is_empty()) {
            std::cout << "0";
            return;
        }

        Node* current = head;
        bool first_node = true;

        do {
            if (current->coefficient > 0 && !first_node) {
                std::cout << " + ";
            }
            else if (current->coefficient < 0) {
                std::cout << " - ";
            }

            int abs_coeff = std::abs(current->coefficient);

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

            first_node = false;
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }

    //13
    void sort_by_exponent() {
        if (!head || head == tail) return;

        bool swapped;
        do {
            swapped = false;
            Node* prev = tail;
            Node* current = head;

            do {
                Node* next = current->next;

                if (next != head && current->exponent < next->exponent) {
                    if (current == head) head = next;
                    if (next == tail) tail = current;

                    prev->next = next;
                    current->next = next->next;
                    next->next = current;

                    swapped = true;
                    prev = next;
                }
                else {
                    prev = current;
                    current = current->next;
                }
            } while (current != head);
        } while (swapped);
    }

};

#endif