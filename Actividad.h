#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include <string>
#include <stdexcept>
#include <utility>

class Actividad {
private:
    std::string id_;
    std::string descripcion_;
    double costo_;
    double tiempo_;

public:
    Actividad() : id_(""), descripcion_(""), costo_(0.0), tiempo_(0.0) {}

    Actividad(std::string id, std::string descripcion, double costo, double tiempo)
        : id_(std::move(id)), descripcion_(std::move(descripcion)), costo_(costo), tiempo_(tiempo) {
        if (id_.empty()) throw std::invalid_argument("Actividad: id vacio");
        if (descripcion_.empty()) throw std::invalid_argument("Actividad: descripcion vacia");
        if (costo_ < 0.0) throw std::invalid_argument("Actividad: costo negativo");
        if (tiempo_ < 0.0) throw std::invalid_argument("Actividad: tiempo negativo");
    }

    const std::string& id() const { return id_; }
    const std::string& descripcion() const { return descripcion_; }
    double costo() const { return costo_; }
    double tiempo() const { return tiempo_; }

    void fijarDescripcion(const std::string& d) {
        if (d.empty()) throw std::invalid_argument("Actividad: descripcion vacia");
        descripcion_ = d;
    }
    void fijarCosto(double c) {
        if (c < 0.0) throw std::invalid_argument("Actividad: costo negativo");
        costo_ = c;
    }
    void fijarTiempo(double t) {
        if (t < 0.0) throw std::invalid_argument("Actividad: tiempo negativo");
        tiempo_ = t;
    }

    bool esIntermedia() const { return costo_ == 0.0 && tiempo_ == 0.0; }

    bool operator==(const Actividad& other) const { return id_ == other.id_; }
    bool operator!=(const Actividad& other) const { return !(*this == other); }
    bool operator<(const Actividad& other) const { return id_ < other.id_; }
};

#endif // ACTIVIDAD_H
