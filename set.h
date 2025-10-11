#ifndef SET_H
#define SET_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Set {
private:
	T* data_;
	std::size_t size_;
	static constexpr double EPSILON = 1e-6;

	bool is_equal(const T& a, const T& b) const {
		if constexpr (std::is_floating_point_v<T>) {
			return std::abs(a - b) < EPSILON;
		}
		else {
			return a == b;
		}
	}

	bool contains_internal(const T& value) const {
		for (std::size_t i = 0; i < size_; ++i) {
			if (is_equal(data_[i]), value) { return true; }
		}
		return false;
	}

public:
	Set() : data_(nullptr), size_(0) {}

	Set(const T* arr, std::size_t n) : data_(nullptr), size_(0) {
		for (std::size_t i = 0; i < n; ++i) { add(arr[i]); }
	}

	Set(const Set& other) : data_(nullptr), size_(0) {
		if (other.size_ > 0) {
			data_ = new T[other.size_];
			for (std::size_t i = 0; i < other.size_; ++i) { data_[i] = other.data_[i]; }
		}
		size_ = other.size_;
	}

	~Set() { delete[] data_; }

	Set& operator=(const Set& other) {
		if (this != &other) {
			delete[] data_;
			size_ = other.size_;
			data_ = new T[size_];
			for (std::size_t i = 0; i < size_; ++i) { data_[i] = other.data_[i]; }
		}
		return *this;
	}
};

#endif // !SET_H
