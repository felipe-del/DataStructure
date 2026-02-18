#pragma once

#include <stdexcept>
#include "ArrayStack.hpp"

/*
    MinStack

    Extensión de una pila tradicional que permite
    obtener el elemento mínimo actual en O(1).

    Estrategia:
    - Una pila principal (data_) almacena los valores.
    - Una pila auxiliar (min_) almacena los mínimos históricos.
*/

template<typename T>
class MinStack {
private:
    /*
        Pila principal:
        Contiene todos los elementos insertados.
    */
    ArrayStack<T> data_;

    /*
        Pila auxiliar de mínimos:
        Guarda los valores mínimos actuales.
        El tope siempre representa el mínimo
        de la pila principal.
    */
    ArrayStack<T> min_;

public:
    /* =====================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================== */

    MinStack() = default;

    ~MinStack() = default;

    /* =====================================
       ESTADO
       ===================================== */

    // Indica si la pila está vacía
    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    // Retorna el número de elementos
    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    /* =====================================
       ACCESO AL TOPE
       ===================================== */

    // Acceso modificable al elemento superior
    T &top() {
        if (empty())
            throw std::out_of_range("MinStack: empty stack");

        return data_.top();
    }

    // Versión const
    const T &top() const {
        if (empty())
            throw std::out_of_range("MinStack: empty stack");

        return data_.top();
    }

    /* =====================================
       INSERCIÓN (push)
       ===================================== */

    /*
        Inserta por copia.

        Lógica importante:
        - Siempre insertamos en la pila principal.
        - Solo insertamos en min_ si:
            1) Está vacía
            2) El nuevo valor es menor o igual
               al mínimo actual
    */
    void push(const T &value) {
        data_.push(value);

        if (min_.empty() || value <= min_.top())
            min_.push(value);
    }

    /*
        Inserción por movimiento.
        Permite evitar copias innecesarias.
    */
    void push(T &&value) {
        if (min_.empty() || value <= min_.top())
            min_.push(value);

        data_.push(std::move(value));
    }

    /* =====================================
       ELIMINACIÓN (pop)
       ===================================== */

    /*
        Elimina el elemento superior.

        Lógica clave:
        - Si el elemento que sale es igual
          al mínimo actual, también debemos
          eliminarlo de la pila de mínimos.
    */
    void pop() {
        if (empty())
            throw std::out_of_range("MinStack: empty stack");

        if (data_.top() == min_.top())
            min_.pop();

        data_.pop();
    }

    /* =====================================
       OBTENER MÍNIMO
       ===================================== */

    /*
        Retorna el mínimo actual en O(1).

        Simplemente devolvemos el tope
        de la pila auxiliar.
    */
    const T &getMin() const {
        if (min_.empty())
            throw std::out_of_range("MinStack: empty stack");

        return min_.top();
    }

    /* =====================================
       LIMPIAR
       ===================================== */

    // Vacía ambas pilas
    void clear() noexcept {
        data_.clear();
        min_.clear();
    }
};
