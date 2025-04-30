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
    NO_CLASIFICADA,
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
    double distancia;

    Vertice() : color(Color::WHITE),
                descubrimiento(0),
                finalizacion(0),
                predecesor(SIN_PREDECESOR),
                distancia(INFINITO) {}
};



struct Arista {
    int origen;
    int destino;
    double peso;
    TipoArista tipo;

    constexpr explicit Arista(const int orig, const int dest,
        const double p = 1.0, const TipoArista t = TipoArista::NO_CLASIFICADA)
        : origen(orig), destino(dest), peso(p), tipo(t) {

        if (orig < 0 || dest < 0) {
            throw std::invalid_argument("Los vertices deben ser positivos");
        }
    }

    bool operator==(const Arista& other) const {
        return  origen == other.origen && destino == other.destino &&
                std::abs(peso - other.peso) < 1e-10 && // Tolerancia para doubles
                tipo == other.tipo;
    }

    bool  operator!=(const Arista& other) const {
        return !(*this == other);
    }

    [[nodiscard]] std::string obtener_tipo_str() const {
        switch (tipo) {
            case TipoArista::NO_CLASIFICADA: return "no clasificada";
            case TipoArista::TREE_EDGE: return "tree";
            case TipoArista::BACK_EDGE: return "back";
            case TipoArista::FORWARD_EDGE: return "forward";
            case TipoArista::CROSS_EDGE: return "cross";
            default: return "tipo desconocido";

        }
    }

};


#endif //TYPES_H
