#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;

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
    vector<vector<int>> grafo;
    vector<Vertice> vertices;
    list<int> orden_topologico;
    vector<pair<int,int>> aristas_clasificadas;
    int tiempo;
    bool tiene_ciclo;

    void clasificar_arista(int u, int v, TipoArista tipo) {
        aristas_clasificadas.push_back({u,v});
        string tipo_str;
        switch (tipo) {
            case TipoArista::TREE_EDGE: tipo_str = "tree"; break;
            case TipoArista::BACK_EDGE: tipo_str = "back"; break;
            case TipoArista::FORWARD_EDGE: tipo_str = "forward"; break;
            case TipoArista::CROSS_EDGE: tipo_str = "cross"; break;
        }

        cout << "Arista (" << u << ", " << v << ") es de tipo " << tipo_str << endl;

    }

    void dfs_visiar(int u) {
        tiempo++;
        vertices[u].descubrimiento = tiempo;
        vertices[u].color = Color::GREY;

        for (int v = 0; v < grafo.size(); v++) {

            if (grafo[u][v] == 1) {
                if (vertices[v].color == Color::WHITE) {
                    vertices[v].predecesor = u;
                    clasificar_arista(u, v, TipoArista::TREE_EDGE);
                    dfs_visiar(v);
                } else if (vertices[v].color == Color::GREY) {
                    clasificar_arista(u, v , TipoArista::BACK_EDGE);
                    tiene_ciclo = true;
                } else {
                    if (vertices[u].descubrimiento < vertices[v].descubrimiento) {
                        clasificar_arista(u, v, TipoArista::FORWARD_EDGE);
                    } else {
                        clasificar_arista(u, v, TipoArista::CROSS_EDGE);
                    }
                }
            }
        }
        vertices[u].color = Color::BLACK;
        tiempo++;
        vertices[u].finalizacion = tiempo;
        if (!tiene_ciclo) {
            orden_topologico.push_front(u);
        }

    }

public:
    explicit DFS(const vector<vector<int>>& g) : grafo(g) {
        vertices.resize(g.size());
        tiempo = 0;
        tiene_ciclo = false;
    }

    void ejecutar() {
        for (int u = 0; u < grafo.size(); u++) {
            vertices[u].color = Color::WHITE;
            vertices[u].predecesor = SIN_PREDECESOR;
        }
        tiempo = 0;
        tiene_ciclo = false;
        orden_topologico.clear();
        aristas_clasificadas.clear();

        for (int u = 0; u < grafo.size(); u++) {
            if (vertices[u].color == Color::WHITE) {
                dfs_visiar(u);
            }
        }
    }

    bool hay_ciclo() const { return tiene_ciclo;}

    list<int> obtener_orden_topologico() const {
        return tiene_ciclo ? list<int>() : orden_topologico;
    }

    vector<pair<int,int>> obtener_aristas_clasificadas() const {
        return aristas_clasificadas;
    }

    void imprimir_tiempos() const {
        cout << "Tiempos de descubrimiento y finalización:\n";
        for (int i = 0; i < vertices.size(); i++) {
            cout << "Vertice " << i << ": descubrimiento = "
                 << vertices[i].descubrimiento
                 << ", finalizacion = " << vertices[i].finalizacion
                 << endl;
        }
    }

    void imprimir_arbol_dfs() const {
        cout << "\nÁrbol DFS (vértice: predecesor):\n";
        for (int i = 0; i < vertices.size(); i++) {
            cout << "Vertice " << i << ": predecesor = "
                 << vertices[i].predecesor << endl;
        }
    }

};