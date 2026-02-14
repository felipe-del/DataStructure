#ifndef STATIC_ARRAY_HPP
#define STATIC_ARRAY_HPP

#include <iostream>
#include <stdexcept>

// Template class for a fixed-size array
template<typename T, size_t SIZE>
class StaticArray {
private:
    T data[SIZE]; // Fixed-size array
    size_t length; // Number of elements added

public:
    // Constructor
    StaticArray() : length(0) {}

    // Add element (fails if full)
    void push_back(const T& value) {
        if (length >= SIZE) throw std::out_of_range("StaticArray is full");
        data[length++] = value;
    }

    // Remove last element
    void pop_back() {
        if (length == 0) throw std::out_of_range("StaticArray is empty");
        length--;
    }

    // Access operator
    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Get current size
    size_t size() const {
        return length;
    }

    // Print elements
    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < length; i++) {
            std::cout << data[i];
            if (i < length - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

#endif // STATIC_ARRAY_HPP