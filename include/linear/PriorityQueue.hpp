#pragma once

#include <cstddef>    // std::size_t
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::move

/*
    PriorityQueue (Max-Heap)

    Implementación usando arreglo dinámico representando
    un Heap Binario Máximo.

    Características:
    - El elemento con MAYOR prioridad (mayor valor) siempre está en la raíz.
    - Inserción en O(log n)
    - Eliminación del máximo en O(log n)
    - Acceso al máximo en O(1)

    Concepto clave:
    Se mantiene la propiedad de heap:
    Para cada nodo i:
        parent(i) >= left(i)
        parent(i) >= right(i)

    Representación en arreglo:
        Padre:        (i - 1) / 2
        Hijo izquierdo: 2*i + 1
        Hijo derecho:   2*i + 2
*/

template<typename T>
class PriorityQueue {
private:
    T *data_; // Arreglo dinámico que almacena el heap
    std::size_t capacity_; // Capacidad máxima
    std::size_t size_; // Cantidad actual de elementos

    /* =====================================
       FUNCIONES AUXILIARES (HEAP)
       ===================================== */

    // Restaura la propiedad del heap hacia arriba
    void heapify_up(std::size_t index) {
        while (index > 0) {
            std::size_t parent = (index - 1) / 2;

            // Si el hijo es mayor que el padre, intercambiamos
            if (data_[index] > data_[parent]) {
                std::swap(data_[index], data_[parent]);
                index = parent;
            } else {
                break; // La propiedad se cumple
            }
        }
    }

    // Restaura la propiedad del heap hacia abajo
    void heapify_down(std::size_t index) {
        while (true) {
            std::size_t left = 2 * index + 1;
            std::size_t right = 2 * index + 2;
            std::size_t largest = index;

            // Verificamos hijo izquierdo
            if (left < size_ && data_[left] > data_[largest]) {
                largest = left;
            }

            // Verificamos hijo derecho
            if (right < size_ && data_[right] > data_[largest]) {
                largest = right;
            }

            // Si el mayor no es el padre, intercambiamos
            if (largest != index) {
                std::swap(data_[index], data_[largest]);
                index = largest;
            } else {
                break; // Heap restaurado
            }
        }
    }

public:
    /* =====================================
       CONSTRUCTOR / DESTRUCTOR
       ===================================== */

    explicit PriorityQueue(std::size_t capacity)
        : data_(new T[capacity]),
          capacity_(capacity),
          size_(0) {
        if (capacity == 0)
            throw std::invalid_argument("PriorityQueue: capacity must be > 0");
    }

    ~PriorityQueue() {
        delete[] data_;
    }

    /* =====================================
       REGLA DE 5
       ===================================== */

    PriorityQueue(const PriorityQueue &) = delete;

    PriorityQueue &operator=(const PriorityQueue &) = delete;

    PriorityQueue(PriorityQueue &&other) noexcept
        : data_(other.data_),
          capacity_(other.capacity_),
          size_(other.size_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    PriorityQueue &operator=(PriorityQueue &&other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.capacity_ = 0;
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

    // Devuelve el elemento de mayor prioridad (raíz del heap)
    T &top() {
        if (empty())
            throw std::out_of_range("PriorityQueue: empty queue");

        return data_[0];
    }

    const T &top() const {
        if (empty())
            throw std::out_of_range("PriorityQueue: empty queue");

        return data_[0];
    }

    /* =====================================
       MODIFICADORES
       ===================================== */

    // Inserta un nuevo elemento
    void push(const T &value) {
        if (full())
            throw std::out_of_range("PriorityQueue: queue is full");

        data_[size_] = value;

        // Restauramos la propiedad del heap hacia arriba
        heapify_up(size_);

        ++size_;
    }

    void push(T &&value) {
        if (full())
            throw std::out_of_range("PriorityQueue: queue is full");

        data_[size_] = std::move(value);

        heapify_up(size_);

        ++size_;
    }

    // Elimina el elemento de mayor prioridad
    void pop() {
        if (empty())
            throw std::out_of_range("PriorityQueue: empty queue");

        // Movemos el último elemento a la raíz
        data_[0] = std::move(data_[size_ - 1]);

        --size_;

        // Restauramos la propiedad del heap hacia abajo
        if (!empty())
            heapify_down(0);
    }

    void clear() noexcept {
        size_ = 0;
    }
};
