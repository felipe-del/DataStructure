#pragma once

#include <iostream>
#include <stdexcept>
#include <utility> // std::move

template <typename T>
class CircularLinkedList {
private:

    /* =====================================================
       ESTRUCTURA INTERNA DEL NODO
       ===================================================== */
    struct Node {
        T value_;        // Valor almacenado
        Node* next_;     // Apunta al siguiente nodo

        // Constructor copia
        Node(const T& value) : value_(value), next_(nullptr) {}

        // Constructor movimiento (evita copia innecesaria)
        Node(T&& value) : value_(std::move(value)), next_(nullptr) {}
    };

    Node* tail_;        // Apunta SIEMPRE al último nodo
    size_t length_;     // Número de elementos

    /*
        Diseño importante:

        En una lista circular simple:

        - tail_->next_ apunta al primer nodo
        - El primer nodo NO se guarda directamente
        - Si está vacía → tail_ == nullptr
    */

public:

    /* =====================================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================================== */

    CircularLinkedList()
        : tail_(nullptr), length_(0) {}

    ~CircularLinkedList() {
        clear(); // Liberamos toda la memoria
    }

    /* =====================================================
       MÉTODOS BÁSICOS
       ===================================================== */

    bool empty() const {
        return length_ == 0;
    }

    size_t size() const {
        return length_;
    }

    /*
        El primer nodo es tail_->next_
        porque tail_ apunta al último
    */
    T& front() {
        if (empty())
            throw std::out_of_range("Lista vacía");

        return tail_->next_->value_;
    }

    /*
        El último nodo es tail_
    */
    T& back() {
        if (empty())
            throw std::out_of_range("Lista vacía");

        return tail_->value_;
    }

    /* =====================================================
       INSERTAR AL INICIO
       ===================================================== */

    void push_front(const T& value) {

        Node* node = new Node(value);

        if (empty()) {
            // Si está vacía:
            // el nodo se apunta a sí mismo
            tail_ = node;
            tail_->next_ = tail_;
        }
        else {
            // Insertamos entre tail_ y el primer nodo
            node->next_ = tail_->next_;
            tail_->next_ = node;
        }

        ++length_;
    }

    void push_front(T&& value) {

        Node* node = new Node(std::move(value));

        if (empty()) {
            tail_ = node;
            tail_->next_ = tail_;
        }
        else {
            node->next_ = tail_->next_;
            tail_->next_ = node;
        }

        ++length_;
    }

    /* =====================================================
       INSERTAR AL FINAL
       ===================================================== */

    /*
        Truco elegante:
        Insertamos al inicio
        y luego movemos tail_
    */
    void push_back(const T& value) {
        push_front(value);
        tail_ = tail_->next_;
    }

    void push_back(T&& value) {
        push_front(std::move(value));
        tail_ = tail_->next_;
    }

    /* =====================================================
       ELIMINAR PRIMERO
       ===================================================== */

    void pop_front() {

        if (empty())
            throw std::out_of_range("Lista vacía");

        Node* head = tail_->next_;

        if (length_ == 1) {
            // Solo había un nodo
            delete head;
            tail_ = nullptr;
        }
        else {
            // Saltamos el primer nodo
            tail_->next_ = head->next_;
            delete head;
        }

        --length_;
    }

    /* =====================================================
       ELIMINAR ÚLTIMO
       ===================================================== */

    void pop_back() {

        if (empty())
            throw std::out_of_range("Lista vacía");

        if (length_ == 1) {
            delete tail_;
            tail_ = nullptr;
        }
        else {
            /*
                Debemos encontrar el nodo
                anterior al tail_
            */
            Node* current = tail_->next_; // empezamos desde el primero

            while (current->next_ != tail_)
                current = current->next_;

            current->next_ = tail_->next_; // cerramos ciclo
            delete tail_;
            tail_ = current; // nuevo último
        }

        --length_;
    }

    /* =====================================================
       LIMPIAR TODA LA LISTA
       ===================================================== */

    void clear() {
        while (!empty())
            pop_front();
    }

    /* =====================================================
       ITERADOR
       ===================================================== */

    /*
        Problema:
        En lista circular nunca hay nullptr final.

        Solución:
        Controlamos cuántos elementos hemos recorrido.
    */

    class Iterator {
    private:
        Node* current_;   // Nodo actual
        size_t count_;    // Cuántos elementos hemos recorrido
        size_t total_;    // Total a recorrer

    public:

        Iterator(Node* start, size_t total, size_t count = 0)
            : current_(start), count_(count), total_(total) {}

        T& operator*() {
            return current_->value_;
        }

        Iterator& operator++() {
            if (count_ < total_) {
                current_ = current_->next_;
                ++count_;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return count_ != other.count_;
        }
    };

    /*
        begin() comienza en el primer nodo
    */
    Iterator begin() {
        if (empty())
            return Iterator(nullptr, 0);

        return Iterator(tail_->next_, length_);
    }

    /*
        end() simplemente tiene el contador completo
    */
    Iterator end() {
        return Iterator(nullptr, length_, length_);
    }

    /* =====================================================
       IMPRESIÓN
       ===================================================== */

    friend std::ostream& operator<<(std::ostream& os,
                                    const CircularLinkedList& list) {

        if (list.empty()) {
            os << "[]";
            return os;
        }

        os << "[ ";

        Node* current = list.tail_->next_;

        // Recorremos exactamente length_ veces
        for (size_t i = 0; i < list.length_; ++i) {
            os << current->value_ << " ";
            current = current->next_;
        }

        os << "]";
        return os;
    }
};