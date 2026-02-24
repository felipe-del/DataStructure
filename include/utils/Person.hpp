#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>   // Incluye la clase std::string para manejar cadenas de texto
#include <iostream> // Incluye std::cout para imprimir en consola
#include <utility>

// Clase que representa una persona
class Person {
public: // Lo que está después de public puede ser accedido desde fuera de la clase
    std::string name_; // Nombre de la persona, usando std::string
    int age_;          // Edad de la persona, tipo entero

    // ----------------------------
    // Constructores
    // ----------------------------

    // Constructor por defecto
    // 'noexcept' indica que esta función no lanzará excepciones
    Person() noexcept : name_("Unknown"), age_(0) {}
    // Constructor que recibe nombre y edad
    // Sintaxis moderna de inicialización con lista de miembros (: name(n), age(a))
    Person(std::string  name_, const int age_) noexcept : name_(std::move(name_)), age_(age_) {}

    // ----------------------------
    // Métodos
    // ----------------------------

    // Comparación por edad (mayor edad = mayor prioridad)
    bool operator>(const Person& other) const {
        return age_ > other.age_;
    }

    // Método que imprime los datos de la persona
    // 'const' indica que el método no modificará el objeto
    // 'noexcept' indica que no lanzará excepciones
    void print() const noexcept {
        std::cout << "{Name: " << name_ << ", Age: " << age_ << "}";
    }
};

#endif // PERSON_HPP