#ifndef DFS_H
#define DFS_H
#include <vector>
#include <list>
#include "grafo.h"


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


class DFS {
private:
    const Grafo& grafo;
    std::vector<Vertice> vertices;
    std::list<int> orden_topologico;
    std::vector<std::pair<int,int>> aristas_clasificadas;
    std::vector<std::vector<int>> componentes_fuertemente_conexas;
    std::vector<int> componente_actual;
    int tiempo;
    bool tiene_ciclo;
    void clasificar_arista(int u, int v, TipoArista tipo);
    void dfs_visitar(int u);
    void dfs_visitar_scc(int u);
    std::vector<int> obtener_vertices_por_finalizacion() const;

public:
    explicit DFS(const Grafo& g);
    void ejecutar();
    void encontrar_componentes_fuertemente_conexas();
    std::vector<std::vector<int>> obtener_componentes() const;
    bool hay_ciclo() const;
    std::list<int> obtener_orden_topologico() const;
    std::vector<std::pair<int,int>> obtener_aristas_clasificadas() const;
    void imprimir_tiempos() const;
    void imprimir_arbol_dfs() const;
};
#endif //DFS_H
