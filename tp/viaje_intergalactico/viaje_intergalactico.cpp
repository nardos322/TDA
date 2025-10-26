#include <bits/stdc++.h>
using namespace std;


void initialize_single_source(vector<int>& dist, int source) {
    fill(dist.begin(), dist.end(), INT_MAX);
    dist[source] = 0;
}

void relax(int u, int v, int w, vector<int>& dist, vector<vector<int>>& llegada_viajeros) {
    if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
    }
}

void dijkstra(int source, const vector<vector<pair<int, int>>>& G, vector<int>& dist, vector<vector<int>>& llegada_viajeros ) {
    initialize_single_source(dist, source);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});


    
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cout << "¡Hola, viajero intergaláctico!" << endl;
    return 0;
}