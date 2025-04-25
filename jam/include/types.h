#ifndef TYPES_H
#define TYPES_H

constexpr int SIN_PREDECESOR = -1;

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


#endif //TYPES_H
