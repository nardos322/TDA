#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct ResultSuma {
    long long suma; // Usamos long long para evitar overflow
    std::vector<int> subconjunto;
};


/**
 * @brief Encuentra la suma de los k números más grandes de un vector y el subconjunto que la forma
 * @details Ordena el vector de mayor a menor y selecciona los primeros k elementos
 *
 * @param x Vector de enteros del cual se seleccionarán los elementos
 * @param k Cantidad de elementos más grandes a seleccionar
 * @throw std::invalid_argument Si k es mayor o igual al tamaño del vector
 * @return ResultSuma Estructura con la suma total y el subconjunto de k elementos
 * @complexity Tiempo: O(n log n), donde n es el tamaño del vector
 *            Espacio: O(k)
 */
ResultSuma suma_selectiva(std::vector<int>& x, const int k) {
    if (k >= x.size()) {
        throw std::invalid_argument("k debe ser menor que el tamaño de x");
    }
    std::ranges::sort(x, std::greater<int>());
    std::vector<int> subconjunto;
    subconjunto.reserve(k);
    long long total_suma = 0;

    for (int i = 0; i < k; i++) {
        total_suma += x[i];
        subconjunto.push_back(x[i]);
    }

    return {total_suma, subconjunto};
}

/**
 * @brief Encuentra la suma de los k números más grandes de un vector y el subconjunto que la forma
 * @details Implementa un algoritmo eficiente usando un min-heap para mantener los k elementos más grandes
 *
 * @param x Vector de enteros del cual se seleccionarán los elementos
 * @param k Cantidad de elementos más grandes a seleccionar
 * @throw std::invalid_argument Si k es mayor o igual al tamaño del vector
 * @return ResultSuma Estructura con la suma total y el subconjunto de k elementos
 * @complexity Tiempo: O(n log k), donde n es el tamaño del vector
 *            Espacio: O(k)
 */
ResultSuma suma_selectiva_eficiente(const std::vector<int>& x, const int k) {
    // 1. Validación corregida
    if (k < 0 || k > x.size()) {
        throw std::invalid_argument("k inválido");
    }
    
    // Caso borde: k=0
    if (k == 0) return {0, {}};

    // Min-Heap: Mantiene los k elementos más grandes vistos hasta ahora.
    // La cima (top) es el "más pequeño de los grandes", actuando como portero.
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    for (int valor : x) {
        if (min_heap.size() < k) {
            min_heap.push(valor);
        } else {
            // Solo si el nuevo valor es mayor que el "peor" de nuestro top-k,
            // vale la pena hacer el intercambio.
            if (valor > min_heap.top()) {
                min_heap.pop();
                min_heap.push(valor);
            }
        }
    }

    long long total_suma = 0;
    std::vector<int> subconjunto;
    subconjunto.reserve(k);

    while (!min_heap.empty()) {
        int val = min_heap.top();
        total_suma += val;
        subconjunto.push_back(val);
        min_heap.pop();
    }
    
    // Opcional: Si quieres devolverlos de mayor a menor como el Greedy original
    // std::reverse(subconjunto.begin(), subconjunto.end());

    return {total_suma, subconjunto};
}


int main() {
    std::vector<int> x1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> x2 = x1;

    constexpr int k = 5;

    std::cout << "Probando suma_selectiva:" << std::endl;
    const auto [total1, subconjunto1] = suma_selectiva(x1, k);
    std::cout << "Suma total: " << total1 << std::endl;
    std::cout << "subconjuntoMax: ";
    for (const auto& i : subconjunto1) {
        std::cout << i << " ";
    }
    std::cout << "\n\n";


    std::cout << "Probando suma_selectiva_eficiente:" << std::endl;
    const auto [total2, subconjunto2] = suma_selectiva_eficiente(x2, k);
    std::cout << "Suma total: " << total2 << std::endl;
    std::cout << "subconjuntoMax: ";
    for (const auto& i : subconjunto2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
