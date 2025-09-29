#ifndef NODOGENERAL_H
#define NODOGENERAL_H

#include <list>

template <class T>
class NodoGeneral {
public:
    T info;                                // información que guarda el nodo (una Actividad en este caso)
    std::list<NodoGeneral<T>*> hijos;      // lista de punteros a los hijos

    // Constructor
    explicit NodoGeneral(const T& val) : info(val) {}
};

#endif // NODOGENERAL_H

