#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;



string invertir(const string &s)
{
    if (s.empty())
        return "";
    return s.back() + invertir(s.substr(0, s.size() - 1));
}

// Verificar si un arreglo está en orden alfabético
bool estaEnOrdenAlfabetico(const vector<string> &palabras)
{
    for (int i = 0; i < palabras.size() - 1; i++)
    {
        if (palabras[i] > palabras[i + 1])
        {
            return false;
        }
    }
    return true;
}

// Numero combinatorio
void backtrack(const int pos,
               const vector<string> &palabras,
               const vector<string> &reversas,
               const vector<long long> &costos,
               vector<int> &elegidos,
               const int r,
               const int N,
               long long &costo_min_global)
{

    if (r == 0) {
        // Construir el arreglo actual sin mutar `palabras`
        vector<string> actual = palabras;
        long long costo_local = 0;

        for (auto n : elegidos) {
           
            actual[n] = reversas[n];
            costo_local += costos[n];
        }

        if (costo_local < costo_min_global && estaEnOrdenAlfabetico(actual)) {
            costo_min_global = costo_local;
        }

        return;
    }

    if (pos >= N)
        return;

    elegidos.push_back(pos);
    backtrack(pos + 1, palabras, reversas, costos, elegidos, r - 1, N, costo_min_global);
    elegidos.pop_back();

    // Solo continúa si quedan suficientes elementos para completar la combinación
    if (N - (pos + 1) >= r) {
        backtrack(pos + 1, palabras, reversas, costos, elegidos, r, N, costo_min_global);
    }
}


// Complejidad temporal O(N*2^N)
long long alfabeticamente(
                const int pos,
                const vector<string> &palabras,
                const vector<string> &reversas,
                const vector<long long> &costos,
                vector<int> &elegidos,
                const int N,
                long long &costo_min_global) {
    
    for (int r = 0; r <= N; ++r) {
        backtrack(0, palabras, reversas, costos, elegidos, r, N, costo_min_global);
    }

      if(costo_min_global == LLONG_MAX) {
        return -1; // Indica que no es posible ordenar
    } else {
        return costo_min_global;
    }

}

void solve(istream& in, ostream& out) {
    long long costo_min_global = LLONG_MAX;
    int N;
    in >> N;

    vector<long long> costos(N);
    for (int i = 0; i < N; ++i) {
        //out << "Ingrese el costo de la palabra " << i + 1 << ": ";
        //out.flush();
        in >> costos[i];
    }

    vector<string> palabras(N);
    for (int i = 0; i < N; ++i) {
        //out << "Ingrese la palabra " << i + 1 << ": ";
        //out.flush(); 
        in >> palabras[i];
    }
    
        
    vector<string> reversas(N);
    for (int i = 0; i < N; ++i)
        reversas[i] = invertir(palabras[i]);
   
    vector<int> elegidos;

    const long long res = alfabeticamente(0, palabras, reversas, costos, elegidos, N, costo_min_global);

    out << res << '\n';
}



//#define LOCAL
#ifdef LOCAL
void test_invertir() {
    assert(invertir("hola") == "aloh");
    assert(invertir("") == "");
    assert(invertir("a") == "a");
}

void test_estaEnOrdenAlfabetico() {
    assert(estaEnOrdenAlfabetico({"a", "b", "c"}));
    assert(!estaEnOrdenAlfabetico({"b", "a", "c"}));
    assert(estaEnOrdenAlfabetico({"a"}));
}

void test_alfabeticamente() {
    vector<string> palabras = {"abc", "def", "ghi"};
    vector<string> reversas = {"cba", "fed", "ihg"};
    vector<long long> costos = {1, 2, 3};
    vector<int> elegidos;
    long long costo_min_global = LLONG_MAX;
    int N = palabras.size();
    long long res = alfabeticamente(0, palabras, reversas, costos, elegidos, N, costo_min_global);
    assert(res == 0); // Ya está ordenado, no hace falta invertir


    vector<string> palabras2 = {"za", "yb", "xc"};
    vector<string> reversas2 = {"az", "by", "cx"};
    vector<long long> costos2 = {100, 200, 300};
    vector<int> elegidos2;
    long long costo_min_global2 = LLONG_MAX;
    int N2 = palabras2.size();
    long long res2 = alfabeticamente(0, palabras2, reversas2, costos2, elegidos2, N2, costo_min_global2);
    assert(res2 == 300); // Se espera que el costo mínimo sea 300


    vector<string> palabras3 = {"casas", "abraza"};
    vector<string> reversas3 = {"sasac", "azarba"};
    vector<long long> costos3 = {0, 0};
    vector<int> elegidos3;
    long long costo_min_global3 = LLONG_MAX;
    int N3 = palabras3.size();
    long long res3 = alfabeticamente(0, palabras3, reversas3, costos3, elegidos3, N3, costo_min_global3);
    assert(res3 == -1); // Se espera que no se puedan ordenar alfabeticamente

    // Caso 4: palabras repetidas, siempre esta ordenado
    vector<string> palabras4 = {"sol", "sol"};
    vector<string> reversas4 = {"los", "los"};
    vector<long long> costos4 = {5, 5};
    vector<int> elegidos4;
    long long costo_min_global4 = LLONG_MAX;
    int N4 = palabras4.size();
    long long res4 = alfabeticamente(0, palabras4, reversas4, costos4, elegidos4, N4, costo_min_global4);
    assert(res4 == 0);

    // Caso 5: Dos palabras, invertir la primera para ordenar
    vector<string> palabras5 = {"ba", "ac"};
    vector<string> reversas5 = {"ab", "ca"};
    vector<long long> costos5 = {10, 20};
    vector<int> elegidos5;
    long long costo_min_global5 = LLONG_MAX;
    int N5 = palabras5.size();
    long long res5 = alfabeticamente(0, palabras5, reversas5, costos5, elegidos5, N5, costo_min_global5);
    assert(res5 == 10);

    // Caso 6: Todas iguales, costo mínimo es 0
    vector<string> palabras6 = {"abc", "abc", "abc"};
    vector<string> reversas6 = {"cba", "cba", "cba"};
    vector<long long> costos6 = {1, 2, 3};
    vector<int> elegidos6;
    long long costo_min_global6 = LLONG_MAX;
    int N6 = palabras6.size();
    long long res6 = alfabeticamente(0, palabras6, reversas6, costos6, elegidos6, N6, costo_min_global6);
    assert(res6 == 0);

    // Caso 7: Invertir todas para ordenar
    vector<string> palabras7 = {"cba", "gad", "aae"};
    vector<string> reversas7 = {"abc", "dag", "eaa"};
    vector<long long> costos7 = {5, 10, 40};
    vector<int> elegidos7;
    long long costo_min_global7 = LLONG_MAX;
    int N7 = palabras7.size();
    long long res7 = alfabeticamente(0, palabras7, reversas7, costos7, elegidos7, N7, costo_min_global7);
    assert(res7 == 50);

    // Caso 8: No se puede ordenar ni invirtiendo
    vector<string> palabras8 = {"z", "y", "x"};
    vector<string> reversas8 = {"z", "y", "x"};
    vector<long long> costos8 = {1, 1, 1};
    vector<int> elegidos8;
    long long costo_min_global8 = LLONG_MAX;
    int N8 = palabras8.size();
    long long res8 = alfabeticamente(0, palabras8, reversas8, costos8, elegidos8, N8, costo_min_global8);
    assert(res8 == -1);

    // Caso 9: ordenar la del medio
    vector<string> palabras9 = {"ge", "an","qm"};
    vector<string> reversas9 = {"eg", "na","mq"};
    vector<long long> costos9 = {510, 800, 150};
    vector<int> elegidos9;
    long long costo_min_global9 = LLONG_MAX;
    int N9 = palabras9.size();
    long long res9 = alfabeticamente(0, palabras9, reversas9, costos9, elegidos9, N9, costo_min_global9);
    assert(res9 == 800);

}
#endif

int main() {
    #ifdef LOCAL
    test_invertir();
    test_estaEnOrdenAlfabetico();
    test_alfabeticamente();
    cout << "OK Todos los tests pasaron.\n";
    #else
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve(cin, cout);
    #endif
    return 0;
}