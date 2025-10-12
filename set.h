#ifndef SET_H
#define SET_H

#include <iostream>
#include <stdexcept>
#include <random>
#include <utility>
#include <string>

template <typename T>
class Set {
private:
	T* data_;
	std::size_t size_;
	static constexpr double EPSILON = 1e-6;

	//1
	static bool is_equal(const T& a, const T& b) {
		if constexpr (std::is_floating_point_v<T>) {
			return std::fabs(a - b) < EPSILON;
		}
		else if constexpr (std::is_same_v<T, std::pair<int, double>>) {
			return a.first == b.first &&
				std::fabs(a.second - b.second) < EPSILON;
		}
		else {
			return a == b;
		}
	}

	//2
	bool contains_internal(const T& value) const {
		for (std::size_t i = 0; i < size_; ++i) {
			if (is_equal(data_[i], value)) { return true; }
		}
		return false;
	}

public:
	//1 def
	Set() : data_(nullptr), size_(0) {}

	//2 arr
	Set(const T* arr, std::size_t n) : data_(nullptr), size_(0) {
		for (std::size_t i = 0; i < n; ++i) { insert(arr[i]); }
	}

	//3 cpy
	Set(const Set& other) : data_(nullptr), size_(0) {
		if (other.size_ > 0) {
			data_ = new T[other.size_];
			for (std::size_t i = 0; i < other.size_; ++i) { data_[i] = other.data_[i]; }
		}
		size_ = other.size_;
	}

	//4 rndm
	Set(std::size_t count, T min_val, T max_val) : data_(nullptr), size_(0) {
		if constexpr (!std::is_arithmetic_v<T>) { throw std::invalid_argument("Random generation only works for numeric types."); }

		std::random_device rd;
		std::mt19937 gen(rd());
		if constexpr (std::is_integral_v<T>) {
			std::uniform_int_distribution<T> dist(min_val, max_val);
			for (std::size_t i = 0; i < count; ++i) { insert(dist(gen)); }
		}
		else {
			std::uniform_real_distribution<T> dist(min_val, max_val);
			for (std::size_t i = 0; i < count; ++i) { insert(dist(gen)); }
		}
	}

	
	//5 dstr
	~Set() { delete[] data_; }



	//1
	Set& operator=(const Set& other) {
		if (this != &other) {
			delete[] data_;
			size_ = other.size_;
			data_ = new T[size_];
			for (std::size_t i = 0; i < size_; ++i) { data_[i] = other.data_[i]; }
		}
		return *this;
	}

	//2
	const T& operator[](std::size_t idx) const {
		if (idx >= size_) {
			throw std::out_of_range("Index out of range..");
		}
		return data_[idx];
	}

	//3
	void insert(const T& value) {
		if (contains_internal(value)) return;
		T* new_data = new T[size_ + 1];
		for (std::size_t i = 0; i < size_; ++i) { new_data[i] = data_[i]; }
		new_data[size_] = value;
		delete[] data_;
		data_ = new_data;
		++size_;
	}

	//4
	void remove(const T& value) {
		if (!contains_internal(value)) return;
		T* new_data = new T[size_ - 1];
		std::size_t idx = 0;
		for (std::size_t i = 0; i < size_; ++i) {
			if (!is_equal(data_[i], value)) { new_data[idx++] = data_[i]; }
		}
		delete[] data_;
		data_ = new_data;
		--size_;
	}

	//5
	bool contains(const T& value) const {
		return contains_internal(value);
	}

	//6
	std::size_t size() const { return size_; }

	//7
	Set operator+(const Set& other) const {
		Set result = *this;
		for (std::size_t i = 0; i < size_; ++i) { result.insert(other.data_[i]); }
		return result;
	}

	//8
	Set operator-(const Set& other) const {
		Set result = *this;
		for (std::size_t i = 0; i < size_; ++i) { result.remove(other.data_[i]); }
		return result;
	}

	//9
	Set& operator+=(const T& value) {
		insert(value);
		return *this;
	}

	//10
	Set& operator-=(const T& value) {
		remove(value);
		return *this;
	}

	//11
	bool operator==(const Set& other) const {
		if (size_ != other.size_) return false;
		for (std::size_t i = 0; i < size_; ++i) { if (!other.contains(data_[i])) return false; }
		return true;
	}

	//12
	bool operator!=(const Set& other) const {
		return !(*this == other);
	}

	//13
	Set intersection(const Set& other) const {
		Set result;
		for (std::size_t i = 0; i < size_; ++i) {
			if (other.contains(data_[i])) { result.insert(data_[i]); }
		}
		return result;
	}

	//14
	friend std::ostream& operator<<(std::ostream& os, const Set<T>& s) {
		os << "{ ";
		for (std::size_t i = 0; i < s.size_; ++i) {
			if constexpr (std::is_same_v<T, std::pair<int, double>>) {
				os << "(" << s.data_[i].first << ", " << s.data_[i].second << ")";
			}
			else {
				os << s.data_[i];
			}

			if (i + 1 < s.size_) {
				os << ", ";
			}
		}
		os << " }";
		return os;
	}

	
};

#endif // !SET_H
