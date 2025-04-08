#ifndef MAGICUADRADOS_H
#define MAGICUADRADOS_H
#include <iostream>
#include <vector>
using namespace std;

/**
 * Verifica si un tablero es un cuadrado mágico.
 * @param board Tablero a verificar.
 * @return true si el tablero es un cuadrado mágico, false en caso contrario.
 */
bool esMagico(const vector<vector<int>>& board);

/**
 * Función de poda:
 * Verifica que la asignación en (i,j) no haga que la suma de la fila, columna
 * o diagonales sobrepase la suma mágica. Y si alguna de esas quedó completa,
 * comprueba que sea igual a la suma mágica.
 */
bool poda (const vector<vector<int>>& board, const int i, const int j);


/**
 * Función que realiza el backtracking para encontrar y mostrar todos los cuadrados mágicos.
 * @param board Tablero actual.
 * @param used Vector que indica qué números ya han sido usados.
 * @param i Fila actual.
 * @param j Columna actual.
 * @param count referencia al contador de cuantos cuadradosMagicos encontrados hay
 * (i, j) indica la celda actual que estamos intentando llenar
 * used[v] indica si el numero v ya esta usado en el tablero
 */
void backtrack(vector<vector<int>>& board, vector<bool>& used, int i, int j, int& count);


#endif //MAGICUADRADOS_H
