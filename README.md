
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![CMake](https://img.shields.io/badge/CMake-Build-red)

## Índice

- [Estructura del Proyecto](#estructura-del-proyecto)
- [Estructuras Lineales](#estructuras-de-datos-lineales)
- [Arreglo Estático](#arreglo-estático)


# Estructuras de Datos en C++

Este repositorio reúne una colección de implementaciones propias de estructuras de datos desarrolladas en C++, concebidas con un enfoque formativo y técnico. Su objetivo es facilitar el estudio profundo de los principios fundamentales que sustentan cada estructura, incluyendo su organización interna, comportamiento en memoria y análisis de complejidad temporal y espacial.

Todas las estructuras han sido implementadas desde cero, sin utilizar contenedores de la biblioteca estándar ni dependencias externas, con el propósito de promover una comprensión rigurosa de su funcionamiento y servir tanto como material de aprendizaje como recurso de consulta profesional.

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



