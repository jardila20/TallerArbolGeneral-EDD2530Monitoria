#include "ArbolGeneral.h"
#include <queue>
#include <algorithm>
#include <stdexcept>   // <-- necesario para std::runtime_error

// ================== Helpers (en archivo de implementación) ==================
namespace {
    template <class T>
    NodoGeneral<T>* copiarNodo(const NodoGeneral<T>* src) {
        if (!src) return nullptr;
        auto* nuevo = new NodoGeneral<T>(src->info);
        for (auto* h : src->hijos) {
            nuevo->hijos.push_back(copiarNodo(h));
        }
        return nuevo;
    }

    template <class T>
    void destruirNodo(NodoGeneral<T>* n) {
        if (!n) return;
        for (auto* h : n->hijos) destruirNodo(h);
        delete n;
    }

    template <class T>
    NodoGeneral<T>* buscar(NodoGeneral<T>* r, const T& val) {
        if (!r) return nullptr;
        if (r->info == val) return r;
        for (auto* h : r->hijos) {
            if (auto* res = buscar(h, val)) return res;
        }
        return nullptr;
    }

    template <class T>
    bool buscarPadre(NodoGeneral<T>* r, const T& val,
                     NodoGeneral<T>** padreOut, typename std::list<NodoGeneral<T>*>::iterator* itOut) {
        if (!r) return false;
        for (auto it = r->hijos.begin(); it != r->hijos.end(); ++it) {
            NodoGeneral<T>* h = *it;
            if (h->info == val) {
                if (padreOut) *padreOut = r;
                if (itOut) *itOut = it;
                return true;
            }
            if (buscarPadre(h, val, padreOut, itOut)) return true;
        }
        return false;
    }

    template <class T>
    unsigned int alturaRec(NodoGeneral<T>* r) {
        if (!r) return 0;
        if (r->hijos.empty()) return 0;
        unsigned int maxh = 0;
        for (auto* h : r->hijos)
            maxh = std::max(maxh, 1u + alturaRec(h));
        return maxh;
    }

    template <class T>
    unsigned int tamanoRec(NodoGeneral<T>* r) {
        if (!r) return 0;
        unsigned int s = 1;
        for (auto* h : r->hijos) s += tamanoRec(h);
        return s;
    }

    template <class T>
    unsigned int ordenRec(NodoGeneral<T>* r) {
        if (!r) return 0;
        unsigned int m = static_cast<unsigned int>(r->hijos.size());
        for (auto* h : r->hijos) m = std::max(m, ordenRec(h));
        return m;
    }
} // namespace

// ================== Implementación de ArbolGeneral<T> ==================

template <class T>
ArbolGeneral<T>::ArbolGeneral() : raiz(nullptr) {}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) : raiz(new NodoGeneral<T>(val)) {}

template <class T>
ArbolGeneral<T>::ArbolGeneral(NodoGeneral<T>* r) : raiz(r) {}

template <class T>
ArbolGeneral<T>::ArbolGeneral(const ArbolGeneral<T>& other)
    : raiz(copiarNodo<T>(other.raiz)) {}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    destruirNodo<T>(raiz);
    raiz = nullptr;
}

template <class T>
std::list< ArbolGeneral<T> > ArbolGeneral<T>::subArbolN() {
    std::list< ArbolGeneral<T> > lista;
    if (!raiz) return lista;
    for (auto* h : raiz->hijos) {
        lista.emplace_back(copiarNodo<T>(h));
    }
    return lista;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    return raiz == nullptr;
}

template <class T>
T ArbolGeneral<T>::obtenerRaiz() {
    if (!raiz) throw std::runtime_error("ArbolGeneral::obtenerRaiz: arbol vacio");
    return raiz->info;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(T v) {
    if (!raiz) {
        raiz = new NodoGeneral<T>(v);
    } else {
        raiz->info = v;
    }
}

template <class T>
ArbolGeneral<T>& ArbolGeneral<T>::operator=(const ArbolGeneral<T>& other) {
    if (this == &other) return *this;
    destruirNodo<T>(raiz);
    raiz = copiarNodo<T>(other.raiz);
    return *this;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(const T& padre, const T& n) {
    if (!raiz) return false;
    if (raiz->info == padre) {
        raiz->hijos.push_back(new NodoGeneral<T>(n));
        return true;
    }
    if (NodoGeneral<T>* p = buscar<T>(raiz, padre)) {
        p->hijos.push_back(new NodoGeneral<T>(n));
        return true;
    }
    return false;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(const T& n) {
    if (!raiz) return false;
    if (raiz->info == n) {
        destruirNodo<T>(raiz);
        raiz = nullptr;
        return true;
    }
    NodoGeneral<T>* padre = nullptr;
    typename std::list<NodoGeneral<T>*>::iterator it;
    if (buscarPadre<T>(raiz, n, &padre, &it)) {
        NodoGeneral<T>* victima = *it;
        padre->hijos.erase(it);
        destruirNodo<T>(victima);
        return true;
    }
    return false;
}

template <class T>
unsigned int ArbolGeneral<T>::altura() {
    return alturaRec<T>(raiz);
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    return tamanoRec<T>(raiz);
}

template <class T>
unsigned int ArbolGeneral<T>::orden() {
    return ordenRec<T>(raiz);
}

// ================== Instanciación explícita ==================
#include "Actividad.h"
template class ArbolGeneral<Actividad>;
