#pragma once

#include "../include/linear/PriorityQueue.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testPriorityQueue() {

    std::cout << "=== Probando PriorityQueue<int> (Max-Heap) ===\n";

    PriorityQueue<int> intQueue(5); // capacidad fija 5

    // Insertar elementos desordenados
    intQueue.push(10);
    intQueue.push(5);
    intQueue.push(30);
    intQueue.push(20);
    intQueue.push(15);

    std::cout << "Tamaño después de push: "
              << intQueue.size()
              << ", ¿Llena? "
              << (intQueue.full() ? "Sí" : "No") << "\n";

    std::cout << "Elemento con mayor prioridad (top): "
              << intQueue.top() << "\n";

    // Probar excepción por estar llena
    try {
        intQueue.push(50);
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada - llena): "
                  << e.what() << "\n";
    }

    // Eliminar elementos verificando orden
    std::cout << "\nExtrayendo elementos en orden de prioridad:\n";
    while (!intQueue.empty()) {
        std::cout << intQueue.top() << " ";
        intQueue.pop();
    }
    std::cout << "\n";

    std::cout << "Después de vaciar, Tamaño: "
              << intQueue.size()
              << ", ¿Vacía? "
              << (intQueue.empty() ? "Sí" : "No") << "\n";

    // Probar excepción por estar vacía
    try {
        intQueue.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada - vacía): "
                  << e.what() << "\n";
    }


    std::cout << "\n=== Probando PriorityQueue<std::string> ===\n";

    PriorityQueue<std::string> strQueue(4);

    strQueue.push("Isaac");
    strQueue.push("Felipe");
    strQueue.push("Juan");
    strQueue.push("Lucas");

    std::cout << "Elemento con mayor prioridad (lexicográficamente mayor): "
              << strQueue.top() << "\n";

    std::cout << "Extrayendo en orden:\n";
    while (!strQueue.empty()) {
        std::cout << strQueue.top() << " ";
        strQueue.pop();
    }
    std::cout << "\n";


    std::cout << "\n=== Probando PriorityQueue<Person> ===\n";

    PriorityQueue<Person> peopleQueue(4);

    // Asumimos que Person tiene operador >
    peopleQueue.push(Person("Isaac", 25));
    peopleQueue.push(Person("Felipe", 30));
    peopleQueue.push(Person("Juan", 22));
    peopleQueue.push(Person("Lucas", 28));

    std::cout << "Persona con mayor prioridad:\n";
    peopleQueue.top().print();
    std::cout << "\n";

    std::cout << "Extrayendo personas por prioridad:\n";
    while (!peopleQueue.empty()) {
        peopleQueue.top().print();
        std::cout << "\n";
        peopleQueue.pop();
    }

    // Probar clear
    peopleQueue.push(Person("Ana", 35));
    peopleQueue.push(Person("Carlos", 40));

    peopleQueue.clear();

    std::cout << "Después de clear, Tamaño: "
              << peopleQueue.size()
              << ", ¿Vacía? "
              << (peopleQueue.empty() ? "Sí" : "No") << "\n";

    // Probar excepción en top vacío
    try {
        peopleQueue.top();
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada - top vacío): "
                  << e.what() << "\n";
    }
}