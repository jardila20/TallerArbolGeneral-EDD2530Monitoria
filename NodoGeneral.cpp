#ifndef NODOGENERAL_CPP
#define NODOGENERAL_CPP

#include <list>

// Clase plantilla de nodo general.
// IMPORTANTE: este archivo suele incluirse desde el header del árbol:
//   en ArbolGeneral.h:   #include "NodoGeneral.cpp"

template <class T>
class NodoGeneral {
public:
    T info;
    std::list<NodoGeneral<T>*> hijos;

    explicit NodoGeneral(const T& val) : info(val), hijos() {}
    ~NodoGeneral() = default; // la liberación de hijos la gestiona el Árbol
};

#endif // NODOGENERAL_CPP
