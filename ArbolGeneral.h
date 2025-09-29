#ifndef ARBOLGENERAL_H_INCLUDED
#define ARBOLGENERAL_H_INCLUDED

#include "NodoGeneral.cpp"
#include <list>

template <class T>
class ArbolGeneral
{
    private:
        NodoGeneral<T>* raiz;
    public:
        ArbolGeneral();//constructor por omision
        ArbolGeneral(T val); //constructor con valor de la raiz
        ArbolGeneral(NodoGeneral<T>*);//cosntructor a partir de un nodo
        ArbolGeneral(const ArbolGeneral<T> &); //constructor copia
        ~ArbolGeneral();//destructor
        std::list< ArbolGeneral<T>  > subArbolN();//analizador lista de subarboles asociados
        bool esVacio();//Analizadora esta vacío
        T obtenerRaiz();// Analizadora obtener Información en la raiz
        void fijarRaiz(T);//Modificadora cambiar la información de la raiz
        ArbolGeneral<T>& operator=(const ArbolGeneral<T>& other);//Sobrecarga operador =

        bool insertarNodo(const T &padre,const  T  &n);//Insertar un hijo  con información n en el padre padre
        bool eliminarNodo(const T &n);//eliminar el nodo cuya información es n

        unsigned int altura();//Calcular la altura del arbol
        unsigned int tamano();//Calcular el peso, numero de elementos en el arbol
        unsigned int orden();//Clacular el orden, numero máximo de subarboles presentes en un arbol
};
#endif // ARBOLGENERAL_H_INCLUDED

