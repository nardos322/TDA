#include <vector>
#include "../include/grafo.h""
using namespace std;


Grafo::Grafo(int num_vertices): lista_adyacencia(num_vertices) {}

void Grafo::agregar_arista(int origen, int destino) {
    lista_adyacencia[origen].push_back(destino);
}

const vector<vector<int>>& Grafo::obtener_lista_adyacencia() const {
    return lista_adyacencia;
}

int Grafo::obtener_num_vertices() const {
    return lista_adyacencia.size();
}
