#pragma once

#include <cstddef>   // std::size_t
#include <stdexcept> // std::out_of_range
#include <iostream>  // std::ostream
#include <utility>   // std::move

// Nodo de la lista enlazada simple
template<typename T>
struct SNode {
    T value_;        // Valor almacenado en el nodo
    SNode* next_;    // Puntero al siguiente nodo

    // Constructores
    // Explicit se usa para evitar conversiones implícitas no deseadas
    // Por ejemplo, sin 'explicit', podrías hacer algo como: SNode<int> node = 5; lo cual no es deseable
    explicit SNode(const T &val) : value_(val), next_(nullptr) {}
    // Constructor de movimiento para eficiencia con tipos que soportan move semantics
    // Se utiliza std::move para transferir la propiedad del recurso sin copiarlo
    // Este constructor se llamará cuando se pase un valor temporal (rvalue) o se use std::move al crear el nodo
    explicit SNode(T &&val) : value_(std::move(val)), next_(nullptr) {}
};

// Clase plantilla para Singly Linked List (Lista enlazada simple)
template<typename T>
class SinglyLinkedList {
private:
    SNode<T>* head_{nullptr};       // Primer nodo de la lista
    SNode<T>* tail_{nullptr};       // Último nodo de la lista
    std::size_t length_{0};         // Cantidad de nodos

public:
    // Constructor por defecto
    SinglyLinkedList() = default;

    // Destructor: libera toda la memoria
    ~SinglyLinkedList() { clear(); }

    // Evita copia accidental
    SinglyLinkedList(const SinglyLinkedList &) = delete;
    SinglyLinkedList &operator=(const SinglyLinkedList &) = delete;

    // Constructor por movimiento
    SinglyLinkedList(SinglyLinkedList &&other) noexcept
        : head_(other.head_), tail_(other.tail_), length_(other.length_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.length_ = 0;
    }

    // Operador de asignación por movimiento
    SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept {
        if (this == &other) return *this;
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        length_ = other.length_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.length_ = 0;
        return *this;
    }

    // Devuelve si la lista está vacía
    [[nodiscard]] bool empty() const noexcept { return length_ == 0; }

    // Devuelve la cantidad de elementos
    [[nodiscard]] std::size_t size() const noexcept { return length_; }

    // Inserta al final (lvalue)
    void push_back(const T &value) {
        SNode<T>* node = new SNode<T>(value);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next_ = node;
            tail_ = node;
        }
        ++length_;
    }

    // Inserta al final (rvalue)
    void push_back(T &&value) {
        SNode<T>* node = new SNode<T>(std::move(value));
        if (!head_) {
            head_ = tail_ = node;
        } else {
            tail_->next_ = node;
            tail_ = node;
        }
        ++length_;
    }

    // Inserta al inicio (lvalue)
    void push_front(const T &value) {
        SNode<T>* node = new SNode<T>(value);
        node->next_ = head_;
        head_ = node;
        if (!tail_) tail_ = head_;
        ++length_;
    }

    // Inserta al inicio (rvalue)
    void push_front(T &&value) {
        SNode<T>* node = new SNode<T>(std::move(value));
        node->next_ = head_;
        head_ = node;
        if (!tail_) tail_ = head_;
        ++length_;
    }

    // Elimina el primer elemento
    void pop_front() {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        SNode<T>* tmp = head_;
        head_ = head_->next_;
        delete tmp;
        --length_;
        if (!head_) tail_ = nullptr; // lista quedó vacía
    }

    // Elimina el último elemento (O(n))
    void pop_back() {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        if (head_ == tail_) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            SNode<T>* current = head_;
            while (current->next_ != tail_) {
                current = current->next_;
            }
            delete tail_;
            tail_ = current;
            tail_->next_ = nullptr;
        }
        --length_;
    }

    // Acceso al primer elemento
    T &front() {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        return head_->value_;
    }

    const T &front() const {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        return head_->value_;
    }

    // Acceso al último elemento
    T &back() {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        return tail_->value_;
    }

    const T &back() const {
        if (empty()) throw std::out_of_range("SinglyLinkedList: lista vacía");
        return tail_->value_;
    }

    // Vacía la lista
    void clear() noexcept {
        while (head_) {
            SNode<T>* tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }
        tail_ = nullptr;
        length_ = 0;
    }

    // Iterador simple (para range-based for)
    struct Iterator {
        SNode<T>* node_;

        Iterator(SNode<T>* n) : node_(n) {}

        T &operator*() { return node_->value_; }

        Iterator &operator++() {
            node_ = node_->next_;
            return *this;
        }

        bool operator!=(const Iterator &other) const { return node_ != other.node_; }
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

    // Operador de salida
    friend std::ostream &operator<<(std::ostream &os, const SinglyLinkedList &list) {
        os << "[";
        SNode<T>* current = list.head_;
        while (current) {
            os << current->value_;
            if (current->next_) os << " -> ";
            current = current->next_;
        }
        os << "]";
        return os;
    }
};