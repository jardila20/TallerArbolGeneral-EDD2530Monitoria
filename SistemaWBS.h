#ifndef SISTEMA_WBS_H
#define SISTEMA_WBS_H

#include <string>
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Actividad.h"
#include "ArbolGeneral.h"

class SistemaWBS {
private:
    ArbolGeneral<Actividad> arbol_; 

public:
    SistemaWBS() : arbol_() {}
    explicit SistemaWBS(const Actividad& raiz) : arbol_(raiz) {
        if (raiz.id() != "0") throw std::invalid_argument("La raiz debe tener id \"0\"");
    }

    void cargarDesdeArchivo(const std::string& ruta);
    void recalcularAcumulados();
    double costoTotal();
    double tiempoTotal();

    // Métodos const llamando a métodos no-const del árbol (solución práctica con const_cast)
    unsigned int tamano() const { return const_cast<ArbolGeneral<Actividad>&>(arbol_).tamano(); }
    unsigned int altura() const { return const_cast<ArbolGeneral<Actividad>&>(arbol_).altura(); }
    unsigned int orden()  const { return const_cast<ArbolGeneral<Actividad>&>(arbol_).orden();  }

    std::vector<Actividad> caminoHasta(const std::string& idHoja) const;

private:
    bool dfsCamino_(const ArbolGeneral<Actividad>& sub, const std::string& objetivo,
                    std::vector<Actividad>& camino) const;
    std::pair<double,double> postordenAcum_(ArbolGeneral<Actividad>& sub);
    static std::string padreDeId_(const std::string& id);
};

#endif // SISTEMA_WBS_H
