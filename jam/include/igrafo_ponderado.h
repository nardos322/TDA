#ifndef IGRAFO_PONDERADO_H
#define IGRAFO_PONDERADO_H
#include "igrafo.h"

/**
 * @class IGrafoPonderado
 * @brief Interfaz para representar un grafo ponderado.
 *
 * Esta clase extiende la funcionalidad de IGrafo e introduce operaciones
 * específicas para grafos donde las aristas tienen pesos asociados.
 */
class IGrafoPonderado: public IGrafo {

public:
    virtual double obtener_peso(int origen, int destino) const = 0;
    using IGrafo::agregar_arista;
    virtual void agregar_arista(int origen, int destino, double peso) = 0;
    virtual void modificar_peso(int origen, int destino, double nuevo_peso) = 0;
};
#endif //IGRAFO_PONDERADO_H
