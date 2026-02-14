#pragma once

#include "../include/linear/DynamicArray.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testDynamicArray() {
    std::cout << "=== Probando DynamicArray<int> ===\n";
    DynamicArray<int> intArr; // Arreglo dinámico de enteros

    // Agregar elementos con push_back (probar auto-resize)
    for (int i = 1; i <= 10; ++i) intArr.push_back(i);
    std::cout << "Después de push_back 10 elementos: " << intArr << "\n";

    // Consultar tamaño, capacidad y si está vacío
    std::cout << "Tamaño: " << intArr.size()
              << ", Capacidad: " << intArr.capacity()
              << ", ¿Vacío? " << (intArr.empty() ? "Sí" : "No") << "\n";

    // Acceso mediante operator[]
    std::cout << "Primer elemento: " << intArr[0] << "\n";

    // Acceso con verificación (at), lanza excepción si índice fuera de rango
    try {
        std::cout << "Elemento en índice 9: " << intArr.at(9) << "\n";
        std::cout << "Elemento en índice 10: " << intArr.at(10) << "\n"; // debe lanzar excepción
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada): " << e.what() << "\n";
    }

    // Eliminar último elemento
    intArr.pop_back();
    std::cout << "Después de pop_back: " << intArr << "\n";

    // Limpiar todo el arreglo
    intArr.clear();
    std::cout << "Después de clear, Tamaño: " << intArr.size()
              << ", ¿Vacío? " << (intArr.empty() ? "Sí" : "No") << "\n";

    std::cout << "\n=== Probando DynamicArray<std::string> ===\n";
    DynamicArray<std::string> strArr; // Arreglo dinámico de strings
    strArr.push_back("Isaac");
    strArr.push_back("Felipe");
    strArr.push_back("Juan");
    std::cout << "Strings: " << strArr << "\n";

    strArr.pop_back();
    std::cout << "Después de pop_back: " << strArr << "\n";

    std::cout << "\n=== Probando DynamicArray<Person> ===\n";
    DynamicArray<Person> people; // Arreglo dinámico de objetos Person

    people.push_back(Person("Isaac", 25));
    people.push_back(Person("Felipe", 30));
    people.push_back(Person("Juan", 22));

    // Imprimir todas las personas
    std::cout << "Todas las personas:\n";
    for (size_t i = 0; i < people.size(); ++i) {
        people[i].print();
        std::cout << "\n";
    }

    // Eliminar último elemento
    people.pop_back();
    std::cout << "Después de pop_back:\n";
    for (size_t i = 0; i < people.size(); ++i) {
        people[i].print();
        std::cout << "\n";
    }

    // Limpiar el arreglo
    people.clear();
    std::cout << "Después de clear, Tamaño: " << people.size()
              << ", ¿Vacío? " << (people.empty() ? "Sí" : "No") << "\n";

    // Probar excepción al acceder fuera de rango
    people.push_back(Person("Lucas", 28));
    try {
        people.at(2).print(); // índice 2 no existe, debe lanzar excepción
    } catch (const std::out_of_range& e) {
        std::cout << "Excepción capturada (esperada): " << e.what() << "\n";
    }

    std::cout << "\n=== Probando resize manual ===\n";
    DynamicArray<int> resizeArr;
    for (int i = 0; i < 5; ++i) resizeArr.push_back(i);
    std::cout << "Antes de resize: " << resizeArr << ", Capacidad: " << resizeArr.capacity() << "\n";
    resizeArr.resize(10); // aumentar capacidad manual
    std::cout << "Después de resize a 10: " << resizeArr << ", Capacidad: " << resizeArr.capacity() << "\n";

    resizeArr.resize(3); // intentar reducir, pero no perder datos
    std::cout << "Después de resize a 3 (mínimo length_): " << resizeArr << ", Capacidad: " << resizeArr.capacity() << "\n";
}