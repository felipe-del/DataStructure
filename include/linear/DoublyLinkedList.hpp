#pragma once

#include <cstddef>    // std::size_t
#include <stdexcept>  // std::out_of_range
#include <iostream>   // std::ostream
#include <utility>    // std::move

// ============================================================
// Nodo de lista doblemente enlazada
// Cada nodo conoce:
//  - Su valor almacenado
//  - El siguiente nodo
//  - El nodo anterior
// ============================================================
template<typename T>
struct DNode {
    T value_;         // Valor almacenado
    DNode* next_;     // Puntero al siguiente nodo
    DNode* prev_;     // Puntero al nodo anterior

    // Constructor para lvalues
    // explicit evita conversiones implícitas no deseadas
    explicit DNode(const T& val)
        : value_(val), next_(nullptr), prev_(nullptr) {}

    // Constructor para rvalues (move semantics)
    // Permite transferir recursos en vez de copiarlos
    explicit DNode(T&& val)
        : value_(std::move(val)), next_(nullptr), prev_(nullptr) {}
};


// ============================================================
// Lista doblemente enlazada (Doubly Linked List)
// - Inserciones en O(1) al inicio y final
// - Eliminaciones en O(1) al inicio y final
// - Bidireccional gracias a prev_
// ============================================================
template<typename T>
class DoublyLinkedList {
private:
    DNode<T>* head_{nullptr};     // Primer nodo
    DNode<T>* tail_{nullptr};     // Último nodo
    std::size_t length_{0};       // Cantidad de elementos

public:

    // ========================================================
    // CONSTRUCTORES Y DESTRUCTOR
    // ========================================================

    DoublyLinkedList() = default;

    // Destructor: libera toda la memoria dinámica
    ~DoublyLinkedList() { clear(); }

    // Se elimina la copia para evitar copias accidentales
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // Constructor por movimiento
    // Transfiere la propiedad de los nodos sin copiar
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), length_(other.length_) {

        // Dejamos el objeto fuente en estado válido y vacío
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.length_ = 0;
    }

    // Operador de asignación por movimiento
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this == &other) return *this;

        clear(); // Liberar lo actual

        head_ = other.head_;
        tail_ = other.tail_;
        length_ = other.length_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.length_ = 0;

        return *this;
    }


    // ========================================================
    // CONSULTAS BÁSICAS
    // ========================================================

    [[nodiscard]] bool empty() const noexcept {
        return length_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return length_;
    }


    // ========================================================
    // INSERCIONES
    // ========================================================

    // Inserta al final (lvalue)
    void push_back(const T& value) {
        auto* node = new DNode<T>(value);

        if (!tail_) { // Lista vacía
            head_ = tail_ = node;
        } else {
            node->prev_ = tail_;
            tail_->next_ = node;
            tail_ = node;
        }

        ++length_;
    }

    // Inserta al final (rvalue)
    void push_back(T&& value) {
        auto* node = new DNode<T>(std::move(value));

        if (!tail_) {
            head_ = tail_ = node;
        } else {
            node->prev_ = tail_;
            tail_->next_ = node;
            tail_ = node;
        }

        ++length_;
    }

    // Inserta al inicio (lvalue)
    void push_front(const T& value) {
        auto* node = new DNode<T>(value);

        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next_ = head_;
            head_->prev_ = node;
            head_ = node;
        }

        ++length_;
    }

    // Inserta al inicio (rvalue)
    void push_front(T&& value) {
        auto* node = new DNode<T>(std::move(value));

        if (!head_) {
            head_ = tail_ = node;
        } else {
            node->next_ = head_;
            head_->prev_ = node;
            head_ = node;
        }

        ++length_;
    }


    // ========================================================
    // ELIMINACIONES
    // ========================================================

    // Elimina el primer elemento (O(1))
    void pop_front() {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");

        DNode<T>* tmp = head_;
        head_ = head_->next_;

        if (head_)
            head_->prev_ = nullptr;
        else
            tail_ = nullptr; // La lista quedó vacía

        delete tmp;
        --length_;
    }

    // Elimina el último elemento (O(1))
    void pop_back() {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");

        DNode<T>* tmp = tail_;
        tail_ = tail_->prev_;

        if (tail_)
            tail_->next_ = nullptr;
        else
            head_ = nullptr; // La lista quedó vacía

        delete tmp;
        --length_;
    }


    // ========================================================
    // ACCESO A ELEMENTOS
    // ========================================================

    T& front() {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");
        return head_->value_;
    }

    const T& front() const {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");
        return head_->value_;
    }

    T& back() {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");
        return tail_->value_;
    }

    const T& back() const {
        if (empty())
            throw std::out_of_range("DoublyLinkedList: lista vacía");
        return tail_->value_;
    }


    // ========================================================
    // LIMPIEZA
    // ========================================================

    // Libera todos los nodos
    void clear() noexcept {
        while (head_) {
            DNode<T>* tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }
        tail_ = nullptr;
        length_ = 0;
    }


    // ========================================================
    // ITERADOR (Forward)
    // Permite usar range-based for
    // ========================================================
    struct Iterator {
        DNode<T>* node_;

        // explicit evita conversiones implícitas desde punteros
        explicit Iterator(DNode<T>* n) : node_(n) {}

        // Desreferenciación
        T& operator*() {
            return node_->value_;
        }

        // Avanzar al siguiente nodo
        Iterator& operator++() {
            node_ = node_->next_;
            return *this;
        }

        // Comparación para finalizar iteración
        bool operator!=(const Iterator& other) const {
            return node_ != other.node_;
        }
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end()   { return Iterator(nullptr); }


    // ========================================================
    // OPERADOR DE IMPRESIÓN
    // ========================================================
    friend std::ostream& operator<<(std::ostream& os,
                                    const DoublyLinkedList& list) {

        os << "[";
        DNode<T>* current = list.head_;

        while (current) {
            os << current->value_;
            if (current->next_)
                os << " <-> ";
            current = current->next_;
        }

        os << "]";
        return os;
    }
};