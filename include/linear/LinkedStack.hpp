#pragma once

#include <stdexcept>
#include <utility>      // std::move
#include <ostream>
#include "SinglyLinkedList.hpp"

/*
    LinkedStack (Pila basada en lista enlazada simple)

    Principio:
    LIFO (Last In, First Out)

    Diseño:
    - El elemento superior (top) será el primero de la lista.
    - Internamente reutilizamos SinglyLinkedList.
    - push  -> push_front
    - pop   -> pop_front
    - top   -> front

    Ventaja:
    - No duplicamos lógica de nodos.
    - Reutilizamos código probado.
    - push y pop son O(1) garantizado.
*/

template<typename T>
class LinkedStack {
private:
    /* =====================================================
       CONTENEDOR INTERNO
       ===================================================== */

    /*
        Usamos SinglyLinkedList como base.

        La pila NO maneja nodos directamente.
        Solo delega comportamiento.
    */
    SinglyLinkedList<T> data_;

public:
    /* =====================================================
       CONSTRUCTORES
       ===================================================== */

    LinkedStack() = default;

    ~LinkedStack() = default;

    // Evitamos copia accidental (hereda restricción de la lista)
    LinkedStack(const LinkedStack &) = delete;

    LinkedStack &operator=(const LinkedStack &) = delete;

    // Permitimos movimiento
    LinkedStack(LinkedStack &&) noexcept = default;

    LinkedStack &operator=(LinkedStack &&) noexcept = default;

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

        En esta implementación,
        el top es el primer nodo.
    */
    T &top() {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        return data_.front();
    }

    const T &top() const {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        return data_.front();
    }

    /* =====================================================
       INSERTAR (push)
       ===================================================== */

    /*
        Inserta por copia.

        Agregamos al inicio de la lista
        para mantener O(1).
    */
    void push(const T &value) {
        data_.push_front(value);
    }

    /*
        Inserta por movimiento.
        Evita copia innecesaria.
    */
    void push(T &&value) {
        data_.push_front(std::move(value));
    }

    /* =====================================================
       ELIMINAR (pop)
       ===================================================== */

    /*
        Eliminamos el elemento superior.

        Delegamos a pop_front().
    */
    void pop() {
        if (empty())
            throw std::out_of_range("Stack: empty stack");

        data_.pop_front();
    }

    /* =====================================================
       LIMPIAR
       ===================================================== */

    /*
        Eliminamos todos los elementos.
    */
    void clear() noexcept {
        data_.clear();
    }

    /* =====================================================
       IMPRESIÓN
       ===================================================== */

    /*
        Mostramos desde top → base.

        Coincide con el orden natural
        de la lista (head hacia adelante).
    */
    friend std::ostream &operator<<(std::ostream &os,
                                    const LinkedStack &stack) {
        os << "[ ";

        for (const auto &value: stack.data_)
            os << value << " ";

        os << "]";
        return os;
    }
};
