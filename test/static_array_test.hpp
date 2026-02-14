#ifndef STATIC_ARRAY_TEST_HPP
#define STATIC_ARRAY_TEST_HPP

#include "../include/linear/StaticArray.hpp"
#include "../include/utils/SampleData.hpp"
#include <iostream>

// Test function for StaticArray with ints, strings, and Person objects
inline void testStaticArray() {
    std::cout << "=== Testing StaticArray<int> ===\n";
    StaticArray<int, 5> intArr;

    // push_back
    for (int i = 1; i <= 5; ++i) intArr.push_back(i);
    intArr.print(); // [1, 2, 3, 4, 5]

    // operator[]
    std::cout << "First element: " << intArr[0] << "\n";

    // pop_back
    intArr.pop_back();
    intArr.print(); // [1, 2, 3, 4]

    std::cout << "\n=== Testing StaticArray<std::string> ===\n";
    StaticArray<std::string, 3> strArr;
    auto names = SampleData::getStringVector(3);
    for (auto& name : names) strArr.push_back(name);
    strArr.print();

    strArr.pop_back();
    strArr.print();

    std::cout << "\n=== Testing StaticArray<Person> ===\n";
    StaticArray<Person, 5> personArr;
    auto people = SampleData::getPersonVector(5);

    // push_back
    for (auto& p : people) personArr.push_back(p);

    // print
    std::cout << "All persons:\n";
    for (size_t i = 0; i < personArr.size(); ++i) {
        personArr[i].print();
        std::cout << "\n";
    }

    // pop_back
    personArr.pop_back();
    std::cout << "After pop_back:\n";
    for (size_t i = 0; i < personArr.size(); ++i) {
        personArr[i].print();
        std::cout << "\n";
    }

    // Access out of bounds example
    try {
        personArr[10].print();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception as expected: " << e.what() << "\n";
    }
}

#endif // STATIC_ARRAY_TEST_HPP