#include "SistemaWBS.h"

std::string SistemaWBS::padreDeId_(const std::string& id) {
    if (id == "0") return "";
    auto pos = id.rfind('.');
    if (pos == std::string::npos) return "0";
    return id.substr(0, pos);
}

bool SistemaWBS::dfsCamino_(const ArbolGeneral<Actividad>& sub, const std::string& objetivo,
                            std::vector<Actividad>& camino) const {
    if (sub.esVacio()) return false;
    Actividad raiz = sub.obtenerRaiz();
    camino.push_back(raiz);
    if (raiz.id() == objetivo) return true;

    std::list< ArbolGeneral<Actividad> > hijos = sub.subArbolN();
    for (auto& h : hijos) {
        std::vector<Actividad> copia = camino;
        if (dfsCamino_(h, objetivo, copia)) { camino = copia; return true; }
    }
    return false;
}

std::pair<double,double> SistemaWBS::postordenAcum_(ArbolGeneral<Actividad>& sub) {
    if (sub.esVacio()) return {0.0, 0.0};
    std::list< ArbolGeneral<Actividad> > hijos = sub.subArbolN();
    if (hijos.empty()) {
        Actividad a = sub.obtenerRaiz();
        return {a.costo(), a.tiempo()};
    }
    double sumaC = 0.0, sumaT = 0.0;
    for (auto& h : hijos) {
        auto par = postordenAcum_(h);
        sumaC += par.first;
        sumaT += par.second;
    }
    Actividad a = sub.obtenerRaiz();
    a.fijarCosto(sumaC);
    a.fijarTiempo(sumaT);
    sub.fijarRaiz(a);
    return {sumaC, sumaT};
}

void SistemaWBS::cargarDesdeArchivo(const std::string& ruta) {
    std::ifstream in(ruta);
    if (!in.is_open()) throw std::runtime_error("No se pudo abrir el archivo");

    arbol_ = ArbolGeneral<Actividad>();

    std::string id, desc;
    double costo, tiempo;
    std::vector<Actividad> acts;
    while (in >> id >> desc >> costo >> tiempo) {
        acts.emplace_back(id, desc, costo, tiempo);
    }

    bool tieneRaiz = false;
    for (const auto& a : acts) {
        if (a.id() == "0") { arbol_ = ArbolGeneral<Actividad>(a); tieneRaiz = true; break; }
    }
    if (!tieneRaiz) throw std::runtime_error("No hay raiz con id 0");

    auto nivelId = [](const std::string& s){ return (s=="0")?0: (int)std::count(s.begin(),s.end(),'.')+1; };
    std::sort(acts.begin(), acts.end(), [&](auto& a, auto& b){ return nivelId(a.id()) < nivelId(b.id()); });

    for (const auto& a : acts) {
        if (a.id() == "0") continue;
        std::string padre = padreDeId_(a.id());
        Actividad padreDummy(padre, "PADRE", 0, 0);
        if (!arbol_.insertarNodo(padreDummy, a)) {
            throw std::runtime_error("Error insertando " + a.id());
        }
    }
}

void SistemaWBS::recalcularAcumulados() { postordenAcum_(arbol_); }
double SistemaWBS::costoTotal() { return arbol_.esVacio()?0:arbol_.obtenerRaiz().costo(); }
double SistemaWBS::tiempoTotal() { return arbol_.esVacio()?0:arbol_.obtenerRaiz().tiempo(); }

std::vector<Actividad> SistemaWBS::caminoHasta(const std::string& idHoja) const {
    std::vector<Actividad> camino;
    if (dfsCamino_(arbol_, idHoja, camino)) return camino;
    return {};
}
