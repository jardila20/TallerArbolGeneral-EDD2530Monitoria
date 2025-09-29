#include <iostream>
#include <string>
#include <vector>
#include "SistemaWBS.h"

// Función auxiliar para imprimir un camino de actividades
void imprimirCamino(const std::vector<Actividad>& camino) {
    if (camino.empty()) {
        std::cout << "No se encontro la actividad solicitada.\n";
        return;
    }
    std::cout << "Camino raiz -> actividad (descripcion, costo):\n";
    for (const auto& a : camino) {
        std::cout << " - " << a.descripcion() << " (costo=" << a.costo() << ")\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_wbs.txt>\n";
        return 1;
    }

    try {
        SistemaWBS sistema;
        sistema.cargarDesdeArchivo(argv[1]);

        std::cout << "== WBS cargado desde archivo: " << argv[1] << " ==\n\n";
        std::cout << "Tamano (nodos): " << sistema.tamano() << "\n";
        std::cout << "Altura        : " << sistema.altura() << "\n";
        std::cout << "Orden         : " << sistema.orden() << "\n";

        sistema.recalcularAcumulados();

        std::cout << "\n== Totales del proyecto ==\n";
        std::cout << "Costo total : " << sistema.costoTotal() << "\n";
        std::cout << "Tiempo total: " << sistema.tiempoTotal() << "\n";

        std::cout << "\nIngrese un id de actividad terminal (ejemplo: 2.1.2), o EOF para salir:\n";
        std::string idhoja;
        while (std::cin >> idhoja) {
            auto camino = sistema.caminoHasta(idhoja);
            imprimirCamino(camino);
            std::cout << "\nIngrese otro id (o EOF para salir):\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 2;
    }

    return 0;
}
