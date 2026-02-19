#pragma once

#include <cstddef>    // std::size_t
#include <stdexcept>  // std::out_of_range

/*
    Queue (FIFO - First In, First Out)

    Implementación básica usando lista enlazada simple.

    Características:
    - Inserción al final (enqueue)
    - Eliminación desde el frente (dequeue)
    - Acceso al frente en O(1)
    - Todas las operaciones principales en O(1)
*/

template<typename T>
class Queue {
private:
    /*
        Nodo interno de la lista enlazada.
        No es visible fuera de la clase.
    */
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node* front_;          // Apunta al primer elemento
    Node* rear_;           // Apunta al último elemento
    std::size_t size_;     // Cantidad de elementos

public:
    /* =====================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================== */

    Queue() noexcept
        : front_(nullptr), rear_(nullptr), size_(0) {}

    ~Queue() {
        clear();
    }

    /* =====================================
       REGLA DE 5 (versión mínima segura)
       ===================================== */

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&& other) noexcept
        : front_(other.front_),
          rear_(other.rear_),
          size_(other.size_) {
        other.front_ = nullptr;
        other.rear_ = nullptr;
        other.size_ = 0;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();

            front_ = other.front_;
            rear_  = other.rear_;
            size_  = other.size_;

            other.front_ = nullptr;
            other.rear_  = nullptr;
            other.size_  = 0;
        }
        return *this;
    }

    /* =====================================
       ESTADO
       ===================================== */

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    /* =====================================
       ACCESO
       ===================================== */

    T& front() {
        if (empty())
            throw std::out_of_range("Queue: empty queue");
        return front_->data;
    }

    const T& front() const {
        if (empty())
            throw std::out_of_range("Queue: empty queue");
        return front_->data;
    }

    T& back() {
        if (empty())
            throw std::out_of_range("Queue: empty queue");
        return rear_->data;
    }

    const T& back() const {
        if (empty())
            throw std::out_of_range("Queue: empty queue");
        return rear_->data;
    }

    /* =====================================
       MODIFICADORES
       ===================================== */

    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (empty()) {
            front_ = rear_ = newNode;
        } else {
            rear_->next = newNode;
            rear_ = newNode;
        }

        ++size_;
    }

    void dequeue() {
        if (empty())
            throw std::out_of_range("Queue: empty queue");

        Node* temp = front_;
        front_ = front_->next;
        delete temp;

        --size_;

        if (size_ == 0)
            rear_ = nullptr;
    }

    void clear() noexcept {
        while (!empty()) {
            dequeue();
        }
    }
};