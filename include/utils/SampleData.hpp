#ifndef SAMPLE_DATA_HPP
#define SAMPLE_DATA_HPP

#include <vector>
#include <string>
#include <random>
#include <iostream>

// Example Person class for testing
class Person {
public:
    std::string name;
    int age;

    Person() : name("Unknown"), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}

    void print() const {
        std::cout << "{Name: " << name << ", Age: " << age << "}";
    }
};

// Utility class to generate sample data
class SampleData {
public:
    // Generate a vector of integers
    static std::vector<int> getIntVector(size_t n = 10, int min = 0, int max = 100) {
        std::vector<int> v;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        for (size_t i = 0; i < n; ++i) {
            v.push_back(dis(gen));
        }
        return v;
    }

    // Generate a vector of strings
    static std::vector<std::string> getStringVector(size_t n = 5) {
        std::vector<std::string> v = {"Isaac", "Felipe", "Juan", "Lucas", "Pedro"};
        std::vector<std::string> res;
        for (size_t i = 0; i < n; ++i) {
            res.push_back(v[i % v.size()]);
        }
        return res;
    }

    // Generate a vector of Person objects
    static std::vector<Person> getPersonVector(size_t n = 5) {
        std::vector<std::string> names = getStringVector(n);
        std::vector<Person> persons;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> ageDis(18, 60);

        for (size_t i = 0; i < n; ++i) {
            persons.push_back(Person(names[i], ageDis(gen)));
        }
        return persons;
    }
};

#endif // SAMPLE_DATA_HPP