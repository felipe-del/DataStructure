#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class CircularLinkedList {
private:

    /* =====================================================
       ESTRUCTURA INTERNA DEL NODO
       ===================================================== */
    struct Node {
        T value_;
        Node* next_;

        Node(const T& value)
            : value_(value), next_(nullptr) {}

        Node(T&& value)
            : value_(std::move(value)), next_(nullptr) {}
    };

    Node* tail_;        // Último nodo
    size_t length_;     // Cantidad de elementos

public:

    /* =====================================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================================== */

    CircularLinkedList()
        : tail_(nullptr), length_(0) {}

    ~CircularLinkedList() {
        clear();
    }

    // Move constructor
    CircularLinkedList(CircularLinkedList&& other) noexcept
        : tail_(other.tail_), length_(other.length_) {

        other.tail_ = nullptr;
        other.length_ = 0;
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

    T& front() {
        if (empty())
            throw std::out_of_range("Lista vacía");

        return tail_->next_->value_;
    }

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
            tail_ = node;
            tail_->next_ = tail_;
        } else {
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
        } else {
            node->next_ = tail_->next_;
            tail_->next_ = node;
        }

        ++length_;
    }

    /* =====================================================
       INSERTAR AL FINAL
       ===================================================== */

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
            delete head;
            tail_ = nullptr;
        } else {
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
        } else {

            Node* current = tail_->next_;

            while (current->next_ != tail_)
                current = current->next_;

            current->next_ = tail_->next_;
            delete tail_;
            tail_ = current;
        }

        --length_;
    }

    /* =====================================================
       LIMPIAR
       ===================================================== */

    void clear() {
        while (!empty())
            pop_front();
    }

    /* =====================================================
       ITERADOR CORREGIDO
       ===================================================== */

    class Iterator {
    private:
        Node* current_;
        size_t count_;
        size_t total_;

    public:

        Iterator(Node* node, size_t total, size_t count = 0)
            : current_(node), count_(count), total_(total) {}

        T& operator*() {
            return current_->value_;
        }

        Iterator& operator++() {

            ++count_;

            if (count_ < total_)
                current_ = current_->next_;
            else
                current_ = nullptr;  // CLAVE: convertimos en end real

            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }
    };

    Iterator begin() {
        if (empty())
            return Iterator(nullptr, 0);

        return Iterator(tail_->next_, length_);
    }

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

        for (size_t i = 0; i < list.length_; ++i) {
            os << current->value_ << " ";
            current = current->next_;
        }

        os << "]";
        return os;
    }

    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept {

        if (this != &other) {

            clear();

            tail_ = other.tail_;
            length_ = other.length_;

            other.tail_ = nullptr;
            other.length_ = 0;
        }

        return *this;
    }
};