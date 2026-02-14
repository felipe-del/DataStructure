#pragma once

#include "../include/linear/SinglyLinkedList.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>

inline void testSinglyLinkedList() {
    std::cout << "=== Probando SinglyLinkedList<int> ===\n";
    SinglyLinkedList<int> intList;

    // Insertar elementos al final
    for (int i = 1; i <= 5; ++i) intList.push_back(i);
    std::cout << "Después de push_back 5 elementos: " << intList << "\n";

    // Insertar elementos al inicio
    for (int i = 10; i <= 12; ++i) intList.push_front(i);
    std::cout << "Después de push_front 3 elementos: " << intList << "\n";

    // Acceder al primer y último elemento
    std::cout << "Front: " << intList.front() << ", Back: " << intList.back() << "\n";

    // Eliminar primer y último elemento
    intList.pop_front();
    intList.pop_back();
    std::cout << "Después de pop_front y pop_back: " << intList << "\n";

    // Tamaño y si está vacío
    std::cout << "Tamaño: " << intList.size() << ", ¿Vacío? "
            << (intList.empty() ? "Sí" : "No") << "\n";

    // Iterar con range-based for
    std::cout << "Iterando con range-based for: ";
    for (auto &val: intList) std::cout << val << " ";
    std::cout << "\n";

    // Vaciar lista
    intList.clear();
    std::cout << "Después de clear, Tamaño: " << intList.size()
            << ", ¿Vacío? " << (intList.empty() ? "Sí" : "No") << "\n";

    std::cout << "\n=== Probando SinglyLinkedList<std::string> ===\n";
    SinglyLinkedList<std::string> strList;
    strList.push_back("Isaac");
    strList.push_back("Felipe");
    strList.push_front("Juan");
    std::cout << "Lista de strings: " << strList << "\n";

    strList.pop_back();
    std::cout << "Después de pop_back: " << strList << "\n";

    std::cout << "\n=== Probando SinglyLinkedList<Person> ===\n";
    SinglyLinkedList<Person> people;
    people.push_back(Person("Isaac", 25));
    people.push_back(Person("Felipe", 30));
    people.push_front(Person("Juan", 22));

    std::cout << "Lista de personas:\n";
    for (auto &p: people) p.print();

    people.pop_front();
    std::cout << "\nDespués de pop_front:\n";
    for (auto &p: people) p.print();

    // Vaciar lista
    people.clear();
    std::cout << "Después de clear, Tamaño: " << people.size()
            << ", ¿Vacío? " << (people.empty() ? "Sí" : "No") << "\n";

    // Probar mover lista
    SinglyLinkedList<Person> movedList = std::move(people);
    std::cout << "\nLista movida (debería estar vacía original): Tamaño original: " << people.size()
            << ", Tamaño nueva: " << movedList.size() << "\n";
}
