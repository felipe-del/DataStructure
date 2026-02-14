#pragma once

#include "../include/linear/StaticArray.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testStaticArray() {
    std::cout << "=== Probando StaticArray<int> ===\n";
    StaticArray<int, 5> intArr; // Arreglo de enteros de tamaño fijo 5

    // Agregar elementos con push_back
    for (int i = 1; i <= 5; ++i) intArr.push_back(i);
    std::cout << "Después de push_back: " << intArr << "\n";

    // Consultar tamaño y si está vacío
    std::cout << "Tamaño: " << intArr.size()
              << ", ¿Vacío? " << (intArr.empty() ? "Sí" : "No") << "\n";

    // Acceso mediante operator[]
    std::cout << "Primer elemento: " << intArr[0] << "\n";

    // Acceso con verificación (at), lanza excepción si índice fuera de rango
    try {
        std::cout << "Elemento en índice 4: " << intArr.at(4) << "\n";
        std::cout << "Elemento en índice 5: " << intArr.at(5) << "\n"; // debe lanzar excepción
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

    std::cout << "\n=== Probando StaticArray<std::string> ===\n";
    StaticArray<std::string, 3> strArr; // Arreglo de strings
    strArr.push_back("Isaac");
    strArr.push_back("Felipe");
    strArr.push_back("Juan");
    std::cout << "Strings: " << strArr << "\n";

    strArr.pop_back();
    std::cout << "Después de pop_back: " << strArr << "\n";

    std::cout << "\n=== Probando StaticArray<Person> ===\n";
    StaticArray<Person, 5> people; // Arreglo de objetos Person

    // Inicialización moderna de objetos con lista de miembros (Member Initialization List)
    people.push_back(Person("Isaac", 25));
    people.push_back(Person("Felipe", 30));
    people.push_back(Person("Juan", 22));

    // Imprimir todas las personas
    std::cout << "Todas las personas:\n";
    for (size_t i = 0; i < people.size(); ++i) {
        people[i].print(); // operador[] devuelve referencia
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
}