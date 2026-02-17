#pragma once

#include <stdexcept>
#include <utility>     // std::move
#include <ostream>
#include "DynamicArray.hpp"

/*
    ArrayStack (Pila de Array) basada en arreglo dinámico.

    Principio:
    LIFO (Last In, First Out)

    El elemento superior (top) será
    siempre el último elemento del arreglo.
*/

template<typename T>
class ArrayStack {
private:
    /* =====================================================
       ESTRUCTURA INTERNA
       ===================================================== */

    /*
        Usamos DynamicArray como contenedor interno.

        Ventaja:
        - Maneja crecimiento automático.
        - Controla capacidad.
        - Ya implementa push_back y pop_back.
    */
    DynamicArray<T> data_;

public:
    /* =====================================================
       CONSTRUCTORES
       ===================================================== */

    ArrayStack() = default;

    explicit ArrayStack(std::size_t initialCapacity)
        : data_(initialCapacity) {
    }

    ~ArrayStack() = default;

    /* =====================================================
       MÉTODOS BÁSICOS
       ===================================================== */

    /*
        Indica si la pila está vacía.
    */
    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    /*
        Retorna el número de elementos.
    */
    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    /*
        Accede al elemento superior (sin eliminarlo).

        El top está al final del arreglo.
    */
    T &top() {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        return data_[data_.size() - 1];
    }

    const T &top() const {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        return data_[data_.size() - 1];
    }

    /* =====================================================
       INSERTAR (push)
       ===================================================== */

    /*
        Inserta por copia.
        Se agrega al final del arreglo.
    */
    void push(const T &value) {
        data_.push_back(value);
    }

    /*
        Inserta por movimiento.
        Evita copia innecesaria.
    */
    void push(T &&value) {
        data_.push_back(std::move(value));
    }

    /* =====================================================
       ELIMINAR (pop)
       ===================================================== */

    /*
        Elimina el elemento superior.

        Solo reducimos el tamaño lógico
        del DynamicArray.
    */
    void pop() {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        data_.pop_back();
    }

    /* =====================================================
       LIMPIAR
       ===================================================== */

    /*
        Elimina todos los elementos.
        No libera necesariamente la capacidad.
    */
    void clear() noexcept {
        data_.clear();
    }

    /* =====================================================
       IMPRESIÓN
       ===================================================== */

    /*
        Mostramos desde base → top
        (orden natural del arreglo).
    */
    friend std::ostream &operator<<(std::ostream &os,
                                    const ArrayStack &stack) {
        os << "[ ";

        for (std::size_t i = 0; i < stack.data_.size(); ++i)
            os << stack.data_[i] << " ";

        os << "]";
        return os;
    }
};
