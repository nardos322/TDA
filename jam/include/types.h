#ifndef TYPES_H
#define TYPES_H
#include <limits>

constexpr int SIN_PREDECESOR = -1;
constexpr double INFINITO = std::numeric_limits<double>::infinity();


enum class Color {
    WHITE,
    GREY,
    BLACK
};

enum class TipoArista {
    TREE_EDGE,
    BACK_EDGE,
    FORWARD_EDGE,
    CROSS_EDGE
};

struct Vertice {
    Color color;
    int descubrimiento;
    int finalizacion;
    int predecesor;
};

struct AristaPonderada {
    int destino;
    double peso;

    AristaPonderada(int dest, double p) : destino(dest), peso(p) {}

    bool operator==(const AristaPonderada& other) const {
        return destino == other.destino;
    }
};

struct Arista {
    int destino;
    constexpr explicit Arista(int dest) : destino(dest) {}
    bool operator==(const Arista& other) const {
        return destino == other.destino;
    }
};


#endif //TYPES_H
