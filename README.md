
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![CMake](https://img.shields.io/badge/CMake-Build-red)

# Estructuras de Datos en C++

Este repositorio reúne una colección de implementaciones propias de estructuras de datos desarrolladas en C++, concebidas con un enfoque formativo y técnico. Su objetivo es facilitar el estudio profundo de los principios fundamentales que sustentan cada estructura, incluyendo su organización interna, comportamiento en memoria y análisis de complejidad temporal y espacial.

Todas las estructuras han sido implementadas desde cero, sin utilizar contenedores de la biblioteca estándar ni dependencias externas, con el propósito de promover una comprensión rigurosa de su funcionamiento y servir tanto como material de aprendizaje como recurso de consulta profesional.

## Índice

- [Estructura del Proyecto](#estructura-del-proyecto)
- [Estructuras Lineales](#estructuras-de-datos-lineales)
  - [Arreglo Estático](#arreglo-estático)
  - [Arreglo Dinámico](#arreglo-dinámico)
  - [Listas Enlazadas](#listas-enlazadas)
    - [Lista Enlazada Simple](#lista-enlazada-simple)

## Estructura del Proyecto

```
DataStructure/
├── include/          # Tipos de estructuras de datos
│   ├── linear/       # Lineales
│   └── utils/        # Datos de prueba
├── test/             # Ejemplo de uso
│   ├── array_test.hpp
│   └── ...
├── src/              # Principal
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```
---

## Estructuras de Datos Lineales

Las estructuras de datos lineales son aquellas en las que los elementos se organizan en una secuencia ordenada, donde cada elemento (excepto el primero y el último) tiene exactamente un predecesor y un sucesor.

Este tipo de estructuras mantiene un orden lógico claro y permite recorrer los elementos de manera secuencial, ya sea desde el inicio hasta el final o viceversa, dependiendo de su implementación.

Desde el punto de vista de memoria, las estructuras lineales pueden almacenarse de forma contigua (como los arreglos) o mediante enlaces entre nodos (como las listas enlazadas). La principal característica que las define no es cómo se almacenan físicamente, sino que mantienen una relación secuencial entre sus elementos.

Son fundamentales en ciencias de la computación porque constituyen la base para estructuras más complejas y permiten comprender conceptos esenciales como acceso directo, recorrido secuencial, inserciones, eliminaciones y análisis de complejidad temporal.

---

### Arreglo Estático

El arreglo estático es una estructura de datos lineal que almacena elementos en posiciones contiguas de memoria y cuya capacidad máxima se define en tiempo de compilación.

Su característica principal es que el tamaño total del arreglo es fijo e inmutable una vez creado. Sin embargo, puede mantener un tamaño lógico interno que indica cuántos elementos han sido realmente insertados, permitiendo distinguir entre capacidad total y cantidad de elementos utilizados.

Al estar almacenado de forma contigua, el acceso a cualquier elemento mediante su índice es inmediato y tiene complejidad constante O(1). Esta eficiencia se debe a que la posición en memoria puede calcularse directamente a partir del índice.

#### El Arreglo Estático es especialmente eficiente cuando:

- El tamaño máximo es conocido de antemano.
- Se requiere acceso rápido por índice.
- Se desea evitar asignaciones dinámicas en memoria (heap).
- Se busca previsibilidad en el uso de memoria.

#### No obstante, presenta limitaciones importantes:

- No puede redimensionarse dinámicamente.
- Si se alcanza su capacidad máxima, no es posible insertar nuevos elementos sin crear una nueva estructura.
- Las inserciones en posiciones intermedias implican desplazamientos y tienen costo lineal.

Desde una perspectiva conceptual, el Arreglo Estático representa la forma más básica y fundamental de almacenamiento secuencial, sirviendo como base para comprender estructuras dinámicas más avanzadas como los arreglos redimensionables.

---

### Arreglo Dinámico

El Arreglo Dinámico (Dynamic Array) es una extensión del concepto de arreglo estático, diseñado para superar la limitación de tamaño fijo y permitir que la estructura crezca o se reduzca dinámicamente según las necesidades del programa.

A diferencia del arreglo estático, cuya capacidad se define en tiempo de compilación, el arreglo dinámico gestiona su memoria en el heap, aumentando su capacidad automáticamente cuando se supera el límite actual, o permitiendo redimensionamiento manual mediante funciones específicas.

#### Filosofía y características principales:
- Crecimiento automático: Cuando se intenta agregar un elemento y no hay suficiente espacio, el arreglo duplica su capacidad interna, copiando los elementos existentes a un nuevo bloque de memoria. Esto asegura eficiencia amortizada en operaciones de inserción.
- Acceso aleatorio rápido: Al igual que los arreglos estáticos, el acceso por índice tiene complejidad O(1), ya que los elementos se almacenan de forma contigua.
- Redimensionamiento manual: Además del crecimiento automático, es posible aumentar la capacidad de forma explícita mediante un método resize, preservando los datos existentes.
- Flexibilidad y escalabilidad: Permite manejar colecciones de tamaño variable sin preocuparse por definir un límite máximo desde el inicio.	
- Manejo seguro de memoria: Implementaciones modernas liberan automáticamente la memoria al destruir el objeto, evitando fugas de memoria.

#### Ventajas del Arreglo Dinámico

- No requiere conocer el tamaño máximo de antemano.
- Permite crecer según la demanda sin perder datos.
- Mantiene eficiencia en acceso y operaciones básicas.
- Facilita la implementación de estructuras más complejas (listas, vectores, buffers dinámicos).

#### Consideraciones y limitaciones
- Las operaciones de crecimiento pueden implicar copias de todos los elementos, lo que genera un costo O(n) en tiempo de ejecución puntual; sin embargo, el costo amortizado por inserción sigue siendo O(1).
- La memoria se asigna dinámicamente, por lo que existe sobrecosto de heap y posible fragmentación.
- Inserciones en posiciones intermedias requieren desplazamientos, con complejidad O(n).

El Arreglo Dinámico representa un equilibrio entre eficiencia y flexibilidad, combinando la rapidez de acceso de los arreglos estáticos con la capacidad de adaptarse a colecciones de tamaño variable.
Es una estructura fundamental para entender y construir vectores, buffers y listas dinámicas, siendo un pilar en cualquier implementación de estructuras de datos modernas.

---

## Listas Enlazadas

Las listas enlazadas son estructuras de datos lineales en las que cada elemento se almacena en un nodo que contiene el valor y un puntero (o referencia) al siguiente nodo de la secuencia. A diferencia de los arreglos, los elementos no se almacenan de manera contigua en memoria, sino que se enlazan mediante referencias, lo que permite una gran flexibilidad en operaciones de inserción y eliminación.

Las listas enlazadas se caracterizan por que cada nodo mantiene información sobre su contenido y cómo conectarse al siguiente nodo, y en algunos casos también al anterior. Esto permite que los elementos estén vinculados de manera secuencial sin requerir que se almacenen de forma contigua en memoria.

Gracias a esta organización, las listas enlazadas pueden crecer o reducir su tamaño dinámicamente, sin necesidad de copiar grandes bloques de memoria, como sucede en los arreglos dinámicos al redimensionarse.

El acceso a los elementos es secuencial: para llegar a un nodo específico es necesario recorrer la lista avanzando de nodo en nodo, por lo que el acceso aleatorio tiene complejidad O(n).

En última instancia, las listas enlazadas constituyen la base para estructuras más complejas, como las listas doblemente enlazadas, listas circulares, pilas y colas, ofreciendo flexibilidad y eficiencia en operaciones de inserción y eliminación.

> Las listas enlazadas destacan por su eficiencia en inserciones y eliminaciones en posiciones arbitrarias, especialmente cuando no se requiere acceso directo a elementos por índice. Sin embargo, su acceso secuencial y el costo adicional de los punteros son aspectos a considerar.

### Lista Enlazada Simple

La Lista Enlazada Simple es la forma más básica de lista enlazada. Cada nodo de esta lista contiene un valor, que es el dato que se desea almacenar, y un puntero al siguiente nodo, que conecta los elementos de manera secuencial. Esta organización permite que los elementos estén vinculados sin necesidad de ocupar posiciones contiguas en memoria.

La lista mantiene referencias al head, que apunta al primer nodo, y al tail, que apunta al último nodo. Mantener un puntero al tail es opcional, pero resulta muy útil para optimizar inserciones al final de la lista.

Entre las operaciones básicas de la Singly Linked List se encuentran la inserción, con métodos como push_front(val) para añadir un nodo al inicio de la lista (complejidad O(1)), y push_back(val) para añadir un nodo al final (O(n) si no se usa tail, O(1) si se mantiene el puntero tail). También se incluyen operaciones de eliminación, como pop_front() para eliminar el primer nodo (O(1)) y pop_back() para eliminar el último nodo (O(n) porque se debe recorrer la lista hasta el penúltimo).

En cuanto al acceso, se puede obtener el valor del primer nodo con front() y del último con back(). Además, se pueden usar iteradores que permiten recorrer la lista de manera secuencial utilizando la sintaxis moderna de C++ (range-based for). Entre las utilidades adicionales se encuentran empty() para comprobar si la lista está vacía, size() para conocer la cantidad de elementos, y clear() para liberar toda la memoria asociada a los nodos.

Las ventajas de la Singly Linked List incluyen inserciones y eliminaciones al inicio muy rápidas (O(1)), la ventaja de no tener que mover elementos como en un arreglo dinámico, y la flexibilidad de crecer o reducir su tamaño dinámicamente según las necesidades del programa.

Sin embargo, también presenta limitaciones. El acceso aleatorio es lento (O(n)), ya que siempre hay que recorrer la lista nodo por nodo. Operaciones como pop_back() y el acceso al penúltimo nodo requieren recorrer la lista completa si no se mantiene una referencia adicional. Además, cada nodo consume memoria extra para almacenar el puntero al siguiente nodo, lo que genera un mayor consumo de memoria en comparación con un arreglo.

La filosofía de implementación de una SinglyLinkedList moderna en C++ sigue buenas prácticas para garantizar eficiencia y seguridad. Se usan constructores explícitos para evitar conversiones implícitas peligrosas, y constructores de movimiento (T&&) para manejar de forma eficiente objetos pesados utilizando std::move. Se suele implementar un iterador interno para integrarla con range-based for, y las variables de miembro suelen terminar con _ para diferenciar claramente los atributos de las variables locales y mejorar la legibilidad del código.

---

_Isaac Brenes_