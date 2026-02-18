#pragma once

#include "utils/Person.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "linear/LinkedStack.hpp"

inline void testLinkedStack() {

    std::cout << "==============================\n";
    std::cout << " TEST LinkedStack<int>\n";
    std::cout << "==============================\n\n";

    LinkedStack<int> stack;

    // --- Estado inicial ---
    std::cout << "¿Vacía? " << (stack.empty() ? "Sí" : "No") << "\n";
    std::cout << "Tamaño inicial: " << stack.size() << "\n\n";

    // --- push ---
    for (int i = 1; i <= 5; ++i)
        stack.push(i);

    std::cout << "Después de push (1-5): " << stack << "\n";

    // --- top ---
    std::cout << "Top actual: " << stack.top() << "\n\n";

    // --- pop ---
    stack.pop();
    std::cout << "Después de pop(): " << stack << "\n";
    std::cout << "Nuevo top: " << stack.top() << "\n\n";

    // --- Vaciar completamente ---
    while (!stack.empty())
        stack.pop();

    std::cout << "Después de vaciar completamente:\n";
    std::cout << "Tamaño: " << stack.size()
              << " | ¿Vacía? "
              << (stack.empty() ? "Sí" : "No") << "\n\n";

    // --- Probar excepción ---
    try {
        stack.top();
    }
    catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada correctamente (top): "
                  << e.what() << "\n";
    }

    try {
        stack.pop();
    }
    catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada correctamente (pop): "
                  << e.what() << "\n";
    }

    // =====================================================
    // TEST std::string
    // =====================================================

    std::cout << "\n==============================\n";
    std::cout << " TEST LinkedStack<std::string>\n";
    std::cout << "==============================\n\n";

    LinkedStack<std::string> strStack;

    strStack.push("Isaac");
    strStack.push("Felipe");
    strStack.push("Juan");

    std::cout << "Stack de strings: " << strStack << "\n";
    std::cout << "Top string: " << strStack.top() << "\n\n";

    strStack.pop();
    std::cout << "Después de pop(): " << strStack << "\n\n";

    // =====================================================
    // TEST Person
    // =====================================================

    std::cout << "\n==============================\n";
    std::cout << " TEST LinkedStack<Person>\n";
    std::cout << "==============================\n\n";

    LinkedStack<Person> people;

    people.push(Person("Isaac", 25));
    people.push(Person("Felipe", 30));
    people.push(Person("Juan", 22));

    std::cout << "Top persona:\n";
    people.top().print();

    // --- Movimiento ---
    LinkedStack<Person> movedPeople = std::move(people);

    std::cout << "\nDespués de mover:\n";
    std::cout << "Tamaño original: " << people.size() << "\n";
    std::cout << "Tamaño nueva: " << movedPeople.size() << "\n";

    std::cout << "\nContenido pila movida:\n";
    while (!movedPeople.empty()) {
        movedPeople.top().print();
        movedPeople.pop();
    }

    std::cout << "\nDespués de vaciar movida:\n";
    std::cout << "Tamaño: " << movedPeople.size()
              << " | ¿Vacía? "
              << (movedPeople.empty() ? "Sí" : "No") << "\n";

    std::cout << "\n==============================\n";
    std::cout << " FIN TEST LinkedStack\n";
    std::cout << "==============================\n";
}