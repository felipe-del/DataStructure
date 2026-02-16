#pragma once

#include "../include/linear/DoublyLinkedList.hpp"
#include "utils/Person.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

inline void testDoublyLinkedList() {

    std::cout << "==============================\n";
    std::cout << " TEST DoublyLinkedList<int>\n";
    std::cout << "==============================\n\n";

    DoublyLinkedList<int> list;

    // --- Estado inicial ---
    std::cout << "¿Vacía? " << (list.empty() ? "Sí" : "No") << "\n";
    std::cout << "Tamaño inicial: " << list.size() << "\n\n";

    // --- push_back ---
    for (int i = 1; i <= 5; ++i)
        list.push_back(i);

    std::cout << "Después de push_back (1-5): " << list << "\n";

    // --- push_front ---
    list.push_front(100);
    list.push_front(200);

    std::cout << "Después de push_front (100, 200): " << list << "\n";

    // --- front y back ---
    std::cout << "Front: " << list.front()
              << " | Back: " << list.back() << "\n\n";

    // --- Iteración manual ---
    std::cout << "Iteración manual: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // --- Range-based for ---
    std::cout << "Range-based for: ";
    for (auto &value : list)
        std::cout << value << " ";
    std::cout << "\n\n";

    // =====================================================
    // PRUEBA ITERADOR BIDIRECCIONAL
    // =====================================================

    std::cout << "Recorrido inverso (rbegin / --): ";
    for (auto it = list.rbegin(); it != list.rend(); --it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Post-incremento (it++): ";
    for (auto it = list.begin(); it != list.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Post-decremento (it-- desde tail): ";
    for (auto it = list.rbegin(); it != list.rend(); it--)
        std::cout << *it << " ";
    std::cout << "\n";

    // --- Modificar valores usando iterador ---
    std::cout << "\nModificando valores (+10): ";
    for (auto it = list.begin(); it != list.end(); ++it)
        *it += 10;

    std::cout << list << "\n";

    // --- Comparación explícita ---
    auto it1 = list.begin();
    auto it2 = list.begin();

    std::cout << "\nComparación de iteradores:\n";
    std::cout << "it1 == it2 ? "
              << (it1 == it2 ? "Sí" : "No") << "\n";

    ++it2;

    std::cout << "Después de ++it2, it1 == it2 ? "
              << (it1 == it2 ? "Sí" : "No") << "\n\n";

    // --- pop_front y pop_back ---
    list.pop_front();
    list.pop_back();

    std::cout << "Después de pop_front y pop_back: "
              << list << "\n";

    std::cout << "Tamaño actual: " << list.size() << "\n\n";

    // --- Vaciar lista completamente ---
    while (!list.empty())
        list.pop_front();

    std::cout << "Después de vaciar completamente:\n";
    std::cout << "Tamaño: " << list.size()
              << " | ¿Vacía? "
              << (list.empty() ? "Sí" : "No") << "\n\n";

    // --- Probar excepción ---
    try {
        list.front();
    } catch (const std::out_of_range &e) {
        std::cout << "Excepción capturada correctamente (front): "
                  << e.what() << "\n";
    }

    try {
        list.pop_back();
    } catch (const std::out_of_range &e) {
        std::cout << "Excepción capturada correctamente (pop_back): "
                  << e.what() << "\n";
    }

    // =====================================================
    // TEST std::string
    // =====================================================

    std::cout << "\n==============================\n";
    std::cout << " TEST DoublyLinkedList<std::string>\n";
    std::cout << "==============================\n\n";

    DoublyLinkedList<std::string> strList;

    strList.push_back("Isaac");
    strList.push_back("Felipe");
    strList.push_front("Juan");

    std::cout << "Lista de strings: " << strList << "\n";

    strList.pop_back();
    std::cout << "Después de pop_back: " << strList << "\n\n";

    std::cout << "Iterando strings:\n";
    for (const auto &name : strList)
        std::cout << "- " << name << "\n";

    // =====================================================
    // TEST Person
    // =====================================================

    std::cout << "\n==============================\n";
    std::cout << " TEST DoublyLinkedList<Person>\n";
    std::cout << "==============================\n\n";

    DoublyLinkedList<Person> people;

    people.push_back(Person("Isaac", 25));
    people.push_back(Person("Felipe", 30));
    people.push_front(Person("Juan", 22));

    std::cout << "Lista de personas:\n";
    for (auto &p : people)
        p.print();

    // --- Movimiento ---
    DoublyLinkedList<Person> movedPeople = std::move(people);

    std::cout << "\nDespués de mover:\n";
    std::cout << "Tamaño original: " << people.size() << "\n";
    std::cout << "Tamaño nueva: " << movedPeople.size() << "\n";

    std::cout << "\nContenido lista movida:\n";
    for (auto &p : movedPeople)
        p.print();

    movedPeople.clear();

    std::cout << "\nDespués de clear(): tamaño = "
              << movedPeople.size()
              << " | ¿Vacía? "
              << (movedPeople.empty() ? "Sí" : "No") << "\n";

    std::cout << "\n==============================\n";
    std::cout << " FIN TEST DoublyLinkedList\n";
    std::cout << "==============================\n";
}