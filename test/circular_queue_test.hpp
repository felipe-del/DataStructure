#pragma once

#include "../include/linear/CircularQueue.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testCircularQueue() {

    std::cout << "=== Probando CircularQueue<int> ===\n";

    CircularQueue<int> intQueue(5); // capacidad fija 5

    // Insertar elementos hasta llenar
    for (int i = 1; i <= 5; ++i)
        intQueue.enqueue(i);

    std::cout << "Tamaño después de enqueue: "
              << intQueue.size()
              << ", ¿Llena? "
              << (intQueue.full() ? "Sí" : "No") << "\n";

    std::cout << "Front: " << intQueue.front()
              << ", Back: " << intQueue.back() << "\n";

    // Probar excepción por estar llena
    try {
        intQueue.enqueue(6);
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada - llena): "
                  << e.what() << "\n";
    }

    // Eliminar dos elementos
    intQueue.dequeue();
    intQueue.dequeue();

    std::cout << "Después de 2 dequeue:\n";
    std::cout << "Front: " << intQueue.front()
              << ", Back: " << intQueue.back()
              << ", Tamaño: " << intQueue.size() << "\n";

    // Insertar nuevamente para probar reutilización circular
    intQueue.enqueue(6);
    intQueue.enqueue(7);

    std::cout << "Después de reutilizar espacios:\n";
    std::cout << "Front: " << intQueue.front()
              << ", Back: " << intQueue.back()
              << ", Tamaño: " << intQueue.size()
              << ", ¿Llena? "
              << (intQueue.full() ? "Sí" : "No") << "\n";

    // Vaciar completamente
    while (!intQueue.empty())
        intQueue.dequeue();

    std::cout << "Después de vaciar, Tamaño: "
              << intQueue.size()
              << ", ¿Vacía? "
              << (intQueue.empty() ? "Sí" : "No") << "\n";

    // Probar excepción por estar vacía
    try {
        intQueue.dequeue();
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada - vacía): "
                  << e.what() << "\n";
    }


    std::cout << "\n=== Probando CircularQueue<std::string> ===\n";

    CircularQueue<std::string> strQueue(3);

    strQueue.enqueue("Isaac");
    strQueue.enqueue("Felipe");
    strQueue.enqueue("Juan");

    std::cout << "Front: " << strQueue.front()
              << ", Back: " << strQueue.back() << "\n";

    strQueue.dequeue();
    strQueue.enqueue("Lucas"); // prueba circular

    std::cout << "Después de operación circular:\n";
    std::cout << "Front: " << strQueue.front()
              << ", Back: " << strQueue.back()
              << ", Tamaño: " << strQueue.size() << "\n";


    std::cout << "\n=== Probando CircularQueue<Person> ===\n";

    CircularQueue<Person> peopleQueue(3);

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
    peopleQueue.enqueue(Person("Lucas", 28)); // reutilización circular

    std::cout << "Después de operación circular, nueva persona al frente:\n";
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
        std::cout << "Excepción capturada (esperada - front vacío): "
                  << e.what() << "\n";
    }
}