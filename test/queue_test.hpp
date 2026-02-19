#pragma once

#include "../include/linear/Queue.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testQueue() {

    std::cout << "=== Probando Queue<int> ===\n";

    Queue<int> intQueue;

    // Insertar elementos
    for (int i = 1; i <= 5; ++i)
        intQueue.enqueue(i);

    std::cout << "Tamaño después de enqueue: "
              << intQueue.size()
              << ", ¿Vacía? "
              << (intQueue.empty() ? "Sí" : "No") << "\n";

    // Consultar front y back
    std::cout << "Front: " << intQueue.front()
              << ", Back: " << intQueue.back() << "\n";

    // Eliminar dos elementos
    intQueue.dequeue();
    intQueue.dequeue();

    std::cout << "Después de 2 dequeue:\n";
    std::cout << "Front: " << intQueue.front()
              << ", Back: " << intQueue.back()
              << ", Tamaño: " << intQueue.size() << "\n";

    // Vaciar completamente
    while (!intQueue.empty())
        intQueue.dequeue();

    std::cout << "Después de vaciar, Tamaño: "
              << intQueue.size()
              << ", ¿Vacía? "
              << (intQueue.empty() ? "Sí" : "No") << "\n";

    // Probar excepción
    try {
        intQueue.dequeue();
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada): "
                  << e.what() << "\n";
    }


    std::cout << "\n=== Probando Queue<std::string> ===\n";

    Queue<std::string> strQueue;

    strQueue.enqueue("Isaac");
    strQueue.enqueue("Felipe");
    strQueue.enqueue("Juan");

    std::cout << "Front: " << strQueue.front()
              << ", Back: " << strQueue.back() << "\n";

    strQueue.dequeue();

    std::cout << "Después de dequeue:\n";
    std::cout << "Front: " << strQueue.front()
              << ", Back: " << strQueue.back()
              << ", Tamaño: " << strQueue.size() << "\n";


    std::cout << "\n=== Probando Queue<Person> ===\n";

    Queue<Person> peopleQueue;

    peopleQueue.enqueue(Person("Isaac", 25));
    peopleQueue.enqueue(Person("Felipe", 30));
    peopleQueue.enqueue(Person("Juan", 22));

    std::cout << "Persona al frente:\n";
    peopleQueue.front().print();
    std::cout << "\n";

    std::cout << "Persona al final:\n";
    peopleQueue.back().print();
    std::cout << "\n";

    peopleQueue.dequeue();

    std::cout << "Después de dequeue, nueva persona al frente:\n";
    peopleQueue.front().print();
    std::cout << "\n";

    // Vaciar
    peopleQueue.clear();

    std::cout << "Después de clear, Tamaño: "
              << peopleQueue.size()
              << ", ¿Vacía? "
              << (peopleQueue.empty() ? "Sí" : "No") << "\n";

    // Probar excepción en front vacío
    try {
        peopleQueue.front();
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada): "
                  << e.what() << "\n";
    }
}