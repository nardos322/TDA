#ifndef DFS_H
#define DFS_H
#include <vector>
#include <list>
#include <igrafo.h>
#include "types.h"


class DFS {
public:
    explicit DFS(const IGrafo& g);
    void ejecutar();
    void encontrar_componentes_fuertemente_conexas();
    [[nodiscard]] std::vector<std::vector<int>> obtener_componentes() const;
    [[nodiscard]] bool hay_ciclo() const;
    [[nodiscard]] std::list<int> obtener_orden_topologico() const;
    [[nodiscard]] std::vector<std::pair<int,int>> obtener_aristas_clasificadas() const;
    void imprimir_tiempos() const;
    void imprimir_arbol_dfs() const;

private:
    const IGrafo& grafo;
    std::vector<Vertice> vertices;
    std::list<int> orden_topologico;
    std::vector<std::pair<int,int>> aristas_clasificadas;
    std::vector<std::vector<int>> componentes_fuertemente_conexas;
    std::vector<int> componente_actual;
    int tiempo;
    bool tiene_ciclo;
    void clasificar_arista(int u, int v, TipoArista tipo);
    void dfs_visitar(int u);
    void dfs_visitar_scc(int u, const IGrafo& g_transpuesto);
    [[nodiscard]] std::vector<int> obtener_vertices_por_finalizacion() const;


};
#endif //DFS_H
