#pragma once

#include <cstddef>   // std::size_t
#include <stdexcept> // std::out_of_range
#include <ostream>   // std::ostream
#include <algorithm> // std::copy

// Clase plantilla para un arreglo dinámico
template<typename T>
class DynamicArray {
private:
    T *data_{nullptr}; // Puntero al arreglo dinámico
    std::size_t length_{0}; // Cantidad de elementos actualmente almacenados
    std::size_t capacity_{0}; // Capacidad del arreglo

public:
    // Constructores y destructor
    DynamicArray() noexcept : data_(nullptr), length_(0), capacity_(0) {
    }

    explicit DynamicArray(std::size_t initialCapacity)
        : data_(new T[initialCapacity]{}), length_(0), capacity_(initialCapacity) {
    }

    ~DynamicArray() { delete[] data_; }

    // Constructor copia
    DynamicArray(const DynamicArray &other)
        : data_(new T[other.capacity_]), length_(other.length_), capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + other.length_, data_);
    }

    // Operador de asignación copia
    DynamicArray &operator=(const DynamicArray &other) {
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        length_ = other.length_;
        capacity_ = other.capacity_;
        std::copy(other.data_, other.data_ + other.length_, data_);
        return *this;
    }

    // Constructor movimiento
    DynamicArray(DynamicArray &&other) noexcept
        : data_(other.data_), length_(other.length_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.length_ = 0;
        other.capacity_ = 0;
    }

    // Operador de asignación movimiento
    DynamicArray &operator=(DynamicArray &&other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        length_ = other.length_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.length_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    // Capacidad y tamaño
    [[nodiscard]] std::size_t size() const noexcept { return length_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool empty() const noexcept { return length_ == 0; }

    // Redimensiona el arreglo al nuevo tamaño (reserva memoria)
    void resize(std::size_t newCapacity) {
        // Asegurarse de no reducir la capacidad por debajo del número de elementos existentes.
        // Si newCapacity es menor que length_, ajustamos newCapacity al tamaño actual.
        if (newCapacity < length_) newCapacity = length_;

        // Crear un nuevo arreglo dinámico con la nueva capacidad.
        // Los {} inicializan los elementos de tipo T a su valor por defecto.
        T *newData = new T[newCapacity]{};

        // Copiar los elementos existentes al nuevo arreglo.
        // std::copy recibe: inicio, fin (no incluido), destino
        // Copia exactamente 'length_' elementos desde 'data_' hacia 'newData'
        std::copy(data_, data_ + length_, newData);

        // Liberar la memoria del arreglo anterior para evitar fugas de memoria
        delete[] data_;

        // Actualizar el puntero interno para que apunte al nuevo arreglo
        data_ = newData;

        // Actualizar la capacidad del arreglo a la nueva capacidad
        capacity_ = newCapacity;
    }

    // Inserción al final
    void push_back(const T &value) {
        if (length_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2); // doblar la capacidad si es necesario
        }
        data_[length_++] = value;
    }

    // Eliminación del último elemento
    void pop_back() {
        if (empty()) throw std::out_of_range("DynamicArray: empty container");
        --length_;
    }

    // Acceso sin verificación
    T &operator[](std::size_t index) noexcept { return data_[index]; }
    const T &operator[](std::size_t index) const noexcept { return data_[index]; }

    // Acceso con verificación
    T &at(std::size_t index) {
        if (index >= length_) throw std::out_of_range("DynamicArray: index out of bounds");
        return data_[index];
    }

    const T &at(std::size_t index) const {
        if (index >= length_) throw std::out_of_range("DynamicArray: index out of bounds");
        return data_[index];
    }

    // Limpia el arreglo (solo lógico)
    void clear() noexcept { length_ = 0; }

    // Redimensionamiento manual
    void reserve(std::size_t newCapacity) {
        if (newCapacity > capacity_) resize(newCapacity);
    }

    void shrink_to_fit() {
        if (capacity_ > length_) resize(length_);
    }

    // Operador de salida
    friend std::ostream &operator<<(std::ostream &os, const DynamicArray &arr) {
        os << "[";
        for (std::size_t i = 0; i < arr.length_; ++i) {
            os << arr.data_[i];
            if (i + 1 < arr.length_) os << ", ";
        }
        os << "]";
        return os;
    }
};
