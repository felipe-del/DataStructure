#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "linear/MinStack.hpp"

inline void testMinStack() {

    std::cout << "==============================\n";
    std::cout << " TEST MinStack<int>\n";
    std::cout << "==============================\n\n";

    MinStack<int> stack;

    // --- Estado inicial ---
    std::cout << "¿Vacía? " << (stack.empty() ? "Sí" : "No") << "\n";
    std::cout << "Tamaño inicial: " << stack.size() << "\n\n";

    // --- push ---
    stack.push(5);
    stack.push(3);
    stack.push(7);
    stack.push(2);
    stack.push(2);  // duplicado mínimo
    stack.push(8);

    std::cout << "Tamaño después de push: " << stack.size() << "\n";
    std::cout << "Top actual: " << stack.top() << "\n";
    std::cout << "Mínimo actual: " << stack.getMin() << "\n\n";

    // --- pop ---
    stack.pop();
    std::cout << "Después de pop():\n";
    std::cout << "Top: " << stack.top() << "\n";
    std::cout << "Mínimo: " << stack.getMin() << "\n\n";

    // Sacar el mínimo duplicado
    stack.pop();
    std::cout << "Después de eliminar un mínimo duplicado:\n";
    std::cout << "Nuevo mínimo: " << stack.getMin() << "\n\n";

    // Sacar el último mínimo real
    stack.pop();
    std::cout << "Después de eliminar el mínimo real:\n";
    std::cout << "Nuevo mínimo: " << stack.getMin() << "\n\n";

    // Vaciar completamente
    while (!stack.empty())
        stack.pop();

    std::cout << "Después de vaciar completamente:\n";
    std::cout << "Tamaño: " << stack.size()
              << " | ¿Vacía? "
              << (stack.empty() ? "Sí" : "No") << "\n\n";

    // --- Probar excepción ---
    try {
        stack.getMin();
    }
    catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada correctamente (getMin): "
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
    std::cout << " TEST MinStack<std::string>\n";
    std::cout << "==============================\n\n";

    MinStack<std::string> strStack;

    strStack.push("zorro");
    strStack.push("gato");
    strStack.push("perro");
    strStack.push("abeja");

    std::cout << "Top string: " << strStack.top() << "\n";
    std::cout << "Mínimo string (orden lexicográfico): "
              << strStack.getMin() << "\n\n";

    strStack.pop();
    std::cout << "Después de pop():\n";
    std::cout << "Nuevo mínimo: " << strStack.getMin() << "\n\n";

    // =====================================================
    // TEST movimiento
    // =====================================================

    std::cout << "\n==============================\n";
    std::cout << " TEST Movimiento MinStack<int>\n";
    std::cout << "==============================\n\n";

    MinStack<int> original;

    original.push(10);
    original.push(4);
    original.push(6);

    std::cout << "Mínimo original antes de mover: "
              << original.getMin() << "\n";

    MinStack<int> movedStack = std::move(original);

    std::cout << "\nDespués de mover:\n";
    std::cout << "Tamaño original: " << original.size() << "\n";
    std::cout << "Tamaño movida: " << movedStack.size() << "\n";
    std::cout << "Mínimo en movida: "
              << movedStack.getMin() << "\n";

    std::cout << "\n==============================\n";
    std::cout << " FIN TEST MinStack\n";
    std::cout << "==============================\n";
}