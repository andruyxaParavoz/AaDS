#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <random>
#include <iostream>

struct stats {
	size_t comparision_count = 0;
	size_t copy_count = 0;

	stats& operatror+=(const stats & other) {
		comparision_count += other.comparision_count;
		copy_count += other.copy_count;
		return *this;
	}
};

namespace array_utils {
	void swap(int& a, int& b, stats& s) {
		int temp = a;
		a = b;
		b = temp;
		s.copy_count += 3;
	}

	std::vector<int> generate_random_array(size_t size, unsigned int seed = 0) {
		std::vector<int> arr(size);
		std::mt19937 gen(seed == 0 ? std::random_device{}() : seed);
		std::uniform_int_distribution<int> dist(-1000, 1000);
		for (size_t i = 0; i < size; ++i) { arr[i] = dist(gen); }
		return arr;
	}

	std::vector<int> generate_sorted_array(size_t size) {
		std::vector<int> arr(size);
		for (size_t i = 0; i < size; ++i) { arr[i] = static_cast<int>(i); }
		return arr;
	}

	std::vector<int> generate_reverse_sorted_array(size_t size) {
		std::vector<int> arr(size);
		for (size_t i = 0; i < size; ++i) { arr[i] = static_cast<int>(size - i - 1);}
		return arr;
	}

	bool is_sorted(const std::vector<int>& arr) {
		for (size_t i = 0; i < arr.size(); ++i) {
			if (arr[i] < arr[i - 1]) return false;
		}
		return true;
	}
}

class SortableList {
private:
	struct Node {
		int data;
		Node* next;
		Node* prev;
		Node(int val) : data(val), next(nullptr), prev(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size;

public:
	//def
	SortableList() : head(nullptr), tail(nullptr), size(0) {}
	//dstr
	~SortableList() { clear(); }

	void clear() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		size = 0;
	}

	void push_back(int value) {
		Node* newNode = new Node(value);
		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		++size;
	}

	std::vector<int> to_vector() const {
		std::vector<int> result;
		Node* current = head;
		while (current) {
			result.push_back(current->data);
			current = current->next;
		}
		return result;
	}

	stats bubble_sort() {
		stats s;
		if (!head || !head->next) return s;

		bool swapped;
		do {
			swapped = false;
			Node* current = head;

			while (current->next) {
				s.comparision_count++;
				if (current->data > current->next->data) {
					int temp = current->data;
					current->data = current->next->data;
					current->next->data = temp;
					s.copy_count += 3;
					swapped = true;
				}
				current = current->next;
			}
		} while (swapped);
		return s;
	}

	stats bubble_sort_list(std::vector<int>& arr) {
		SortableList list;
		for (int val : arr) {
			list.push_back(val);
		}

		stats result = list.bubble_sort();
		std::vector<int> sorted = list.to_vector();
		arr = sorted;
		return result;
	}

	stats cocktail_sort(std::vector<int>& arr) {
		stats s;
		if (arr.empty()) return s;
		
		bool swapped = true;
		size_t start = 0;
		size_t end = arr->size() - 1;

		while (swapped) {
			swapped = false;
			for (size_t i = 0; i < end; ++i) {
				s.comparision_count++;
				if (arr[i] > arr[i + 1]) {
					array_utils::swap(arr[i], arr[i + 1], s);
					swapped = true;
				}
			}

			if (!swapped) break;
			swapped = false;
			--end;

			for (size_t i = 0; i > start; --i) {
				s.comparision_count++;
				if (arr[i] < arr[i - 1]) {
					array_utils::swap(arr[i], arr[i - 1], s);
					swapped = true;
				}
			}
			++start;
		}
		return s;
	}

	size_t partition(std::vector<int>& arr, size_t low, size_t high, stats* s) {
		int pivot = arr[high];
		size_t i = low;

		for (size_t j = 0; j < high; ++j) {
			s->comparision_count++;
			if (arr[j] <= pivot) {
				if (i != j) {
					array_utils::swap(arr[i], arr[j], s);
				}
				++i;
			}
		}
		if (i != high) { array_utils::swap(arr[i], arr[high], s); }
		return i;
	}

	void quick_sort_recursive(std::vector<int>& arr, size_t low, size_t high, stats* s) {
		if (low < high) {
			size_t pi = partition(arr, low, high, s);
			if (pi > 0) {
				quick_sort_recursive(arr, low, pi - 1, s);
			}
			quick_sort_recursive(arr, pi + 1, high, s);
		}
	}

	stats quick_sort(std::vector<int>& arr) {
		stats s;
		if (arr.empty()) return s;
		quick_sort_recursive(arr, 0, arr.size() - 1, s);
		return s;
	}
};
#endif