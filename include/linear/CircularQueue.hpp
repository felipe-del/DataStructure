#pragma once

#include <cstddef>    // std::size_t
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::move

/*
    CircularQueue (FIFO - First In, First Out)

    Implementación usando arreglo dinámico con técnica circular.

    Características:
    - Inserción al final (enqueue)
    - Eliminación desde el frente (dequeue)
    - Reutiliza espacios libres mediante aritmética modular
    - No desplaza elementos en memoria
    - Todas las operaciones principales en O(1)

    Concepto clave:
    Los índices "envuelven" usando el operador módulo (%),
    lo que permite reutilizar posiciones liberadas.
*/

template<typename T>
class CircularQueue {
private:
    T* data_;               // Arreglo dinámico que almacena los elementos
    std::size_t capacity_;  // Capacidad máxima del buffer
    std::size_t front_;     // Índice del primer elemento
    std::size_t rear_;      // Índice donde se insertará el siguiente elemento
    std::size_t size_;      // Cantidad actual de elementos

public:
    /* =====================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================== */

    explicit CircularQueue(std::size_t capacity)
        : data_(new T[capacity]),
          capacity_(capacity),
          front_(0),
          rear_(0),
          size_(0) {

        if (capacity == 0)
            throw std::invalid_argument("CircularQueue: capacity must be > 0");
    }

    ~CircularQueue() {
        delete[] data_;
    }

    /* =====================================
       REGLA DE 5
       ===================================== */

    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    CircularQueue(CircularQueue&& other) noexcept
        : data_(other.data_),
          capacity_(other.capacity_),
          front_(other.front_),
          rear_(other.rear_),
          size_(other.size_) {

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.front_ = 0;
        other.rear_ = 0;
        other.size_ = 0;
    }

    CircularQueue& operator=(CircularQueue&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            capacity_ = other.capacity_;
            front_ = other.front_;
            rear_ = other.rear_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.capacity_ = 0;
            other.front_ = 0;
            other.rear_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    /* =====================================
       ESTADO
       ===================================== */

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] bool full() const noexcept {
        return size_ == capacity_;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }

    /* =====================================
       ACCESO
       ===================================== */

    T& front() {
        if (empty())
            throw std::out_of_range("CircularQueue: empty queue");

        return data_[front_];
    }

    const T& front() const {
        if (empty())
            throw std::out_of_range("CircularQueue: empty queue");

        return data_[front_];
    }

    T& back() {
        if (empty())
            throw std::out_of_range("CircularQueue: empty queue");

        // El último elemento insertado está justo antes de rear_
        std::size_t index = (rear_ + capacity_ - 1) % capacity_;
        return data_[index];
    }

    const T& back() const {
        if (empty())
            throw std::out_of_range("CircularQueue: empty queue");

        std::size_t index = (rear_ + capacity_ - 1) % capacity_;
        return data_[index];
    }

    /* =====================================
       MODIFICADORES
       ===================================== */

    void enqueue(const T& value) {
        if (full())
            throw std::out_of_range("CircularQueue: queue is full");

        data_[rear_] = value;

        // Avanzamos circularmente
        rear_ = (rear_ + 1) % capacity_;

        ++size_;
    }

    void enqueue(T&& value) {
        if (full())
            throw std::out_of_range("CircularQueue: queue is full");

        data_[rear_] = std::move(value);

        rear_ = (rear_ + 1) % capacity_;

        ++size_;
    }

    void dequeue() {
        if (empty())
            throw std::out_of_range("CircularQueue: empty queue");

        // Avanzamos el frente circularmente
        front_ = (front_ + 1) % capacity_;

        --size_;
    }

    void clear() noexcept {
        front_ = 0;
        rear_ = 0;
        size_ = 0;
    }
};