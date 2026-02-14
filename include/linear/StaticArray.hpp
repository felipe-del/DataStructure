#pragma once  // Evita múltiples inclusiones del mismo archivo

#include <cstddef>   // std::size_t
#include <stdexcept> // std::out_of_range
#include <ostream>   // std::ostream

// Clase plantilla para un arreglo estático de tamaño fijo
template<typename T, std::size_t SIZE>
class StaticArray {
private:
    T data_[SIZE]{};       // Arreglo interno de tamaño fijo
    std::size_t length_{0}; // Cantidad de elementos actualmente almacenados

public:
    // Constructor por defecto (constexpr + noexcept = seguro y evaluable en tiempo de compilación)
    constexpr StaticArray() noexcept = default;

    // Destructor y operaciones especiales por defecto
    ~StaticArray() = default;                         // Destructor trivial
    constexpr StaticArray(const StaticArray&) = default; // Constructor copia
    constexpr StaticArray& operator=(const StaticArray&) = default; // Operador de asignación copia

    // Capacidad máxima del arreglo (static + constexpr: conocida en tiempo de compilación, no depende de instancia)
    [[nodiscard]] static constexpr std::size_t capacity() noexcept {
        return SIZE;
    }

    // Tamaño actual del arreglo (cantidad de elementos añadidos)
    [[nodiscard]] constexpr std::size_t size() const noexcept {
        return length_;
    }

    // Verifica si el arreglo está vacío
    [[nodiscard]] constexpr bool empty() const noexcept {
        return length_ == 0;
    }

    // Inserta un elemento al final del arreglo
    constexpr void push_back(const T& value) {
        if (length_ >= SIZE)
            throw std::out_of_range("StaticArray: capacity exceeded"); // Lanza excepción si supera capacidad
        data_[length_++] = value; // Inserta y aumenta contador de elementos
    }

    // Elimina el último elemento
    constexpr void pop_back() {
        if (empty())
            throw std::out_of_range("StaticArray: empty container"); // Excepción si no hay elementos
        --length_;
    }

    // Acceso sin verificación (similar al operador [] de std::vector)
    constexpr T& operator[](std::size_t index) noexcept {
        return data_[index];
    }

    constexpr const T& operator[](std::size_t index) const noexcept {
        return data_[index];
    }

    // Acceso con verificación de límites
    constexpr T& at(std::size_t index) {
        if (index >= length_)
            throw std::out_of_range("StaticArray: index out of bounds"); // Excepción si índice fuera de rango
        return data_[index];
    }

    constexpr const T& at(std::size_t index) const {
        if (index >= length_)
            throw std::out_of_range("StaticArray: index out of bounds");
        return data_[index];
    }

    // Limpia el arreglo (solo lógico, no destruye los objetos)
    constexpr void clear() noexcept {
        length_ = 0;
    }

    // Operador de salida para imprimir el arreglo
    friend std::ostream& operator<<(std::ostream& os, const StaticArray& arr) {
        os << "[";
        for (std::size_t i = 0; i < arr.length_; ++i) {
            os << arr.data_[i];
            if (i + 1 < arr.length_)
                os << ", ";
        }
        os << "]";
        return os;
    }
};