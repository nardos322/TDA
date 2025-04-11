#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * @brief Calcula la posición final basada en una cadena de instrucciones.
 *
 * @param a Cadena de instrucciones que contiene caracteres '+' (avanzar) y '-' (retroceder).
 * @return La posición final calculada como la diferencia entre los movimientos hacia adelante y hacia atrás.
 *
 * @details
 * - La función recorre la cadena `a` y cuenta cuántos movimientos son hacia adelante ('+') y cuántos son hacia atrás ('-').
 * - La posición final se calcula como la diferencia entre el número de movimientos hacia adelante y hacia atrás.
 * - Si la cadena está vacía, la posición final será 0.
 */
int posicion(const string& a) {
    int sumaAvanzar = 0, sumaRetroceder = 0;
    for(int i = 0; i < a.size(); i++) {
        if (a[i] == '+') {
            sumaAvanzar++;
        } else {
            sumaRetroceder++;
        }
    }
    return sumaAvanzar - sumaRetroceder;
}

/**
 * @brief Determina si es posible alcanzar la posición deseada desde el estado actual.
 *
 * @param posDeseada La posición que se desea alcanzar.
 * @param posActual La posición actual en el recorrido.
 * @param i Índice actual en la cadena `b` que se está procesando.
 * @param b Cadena de instrucciones recibidas, que puede contener caracteres '+' (avanzar),
 *          '-' (retroceder) o '?' (indeterminado).
 * @return `true` si no es posible alcanzar la posición deseada desde el estado actual,
 *         `false` en caso contrario.
 *
 * @details
 * - La función utiliza dos criterios para determinar si es imposible alcanzar la posición deseada:
 *   1. Si la diferencia entre la posición deseada y la posición actual es mayor que los pasos restantes.
 *   2. Si la diferencia entre la posición deseada y la posición actual tiene una paridad distinta
 *      a la de los pasos restantes.
 * - Si cualquiera de estas condiciones se cumple, la función devuelve `true` para podar la rama
 *   de exploración.
 */
bool poda(int posDeseada, int posActual, int i,  const string& b) {
    int restantes = b.size() - i;
    int diferencia = abs(posDeseada - posActual);

    // Si la diferencia es mayor que los pasos restantes, es imposible llegar
    if (diferencia > restantes)
        return true;

    // Si la diferencia y los pasos restantes tienen distinta paridad, también es imposible
    return (diferencia % 2) != (restantes % 2);
}
int probabilidad(const string& a, const string& b) {

    const int posDeseada = posicion(a);
    const int posParcialB = posicion(b);

    if (posDeseada == posParcialB) {
        return 1;
    }
    return 0;

}

/**
 * @brief Realiza un recorrido en profundidad (backtracking) para calcular las coincidencias
 *        entre las posiciones deseadas y las posibles combinaciones de movimientos.
 *
 * @param b Cadena de instrucciones recibidas, que puede contener caracteres '+' (avanzar),
 *          '-' (retroceder) o '?' (indeterminado).
 * @param i Índice actual en la cadena `b` que se está procesando.
 * @param posActual Posición actual calculada en el recorrido.
 * @param posDeseada Posición deseada que se intenta alcanzar.
 * @param coincidencias Referencia a un contador que acumula las coincidencias en las que
 *                      `posActual` coincide con `posDeseada` al final del recorrido.
 *
 * @details
 * - Si la poda determina que no es posible alcanzar la posición deseada desde el estado
 *   actual, la función termina la rama de exploración.
 * - Si se alcanza el final de la cadena `b`, verifica si la posición actual coincide con
 *   la posición deseada y, de ser así, incrementa el contador de coincidencias.
 * - Si el carácter actual en `b` es indeterminado ('?'), explora ambas posibilidades:
 *   avanzar ('+') o retroceder ('-').
 * - Si el carácter actual es conocido ('+' o '-'), continúa el recorrido en la dirección
 *   correspondiente.
 */
void backtrack(string& b, int i, int posActual, int posDeseada, int& coincidencias) {
    if (poda(posDeseada, posActual, i, b)) {
        return;  // Si no es posible llegar a posDeseada, terminamos esta rama
    }
    if (i == b.length()) {
        if (posActual == posDeseada) {
            coincidencias++;
        }
        return;
    }
    if (b[i] == '+') {
        backtrack(b, i + 1, posActual + 1, posDeseada, coincidencias);
    } else if (b[i] == '-') {
        backtrack(b, i + 1, posActual - 1, posDeseada, coincidencias);
    } else { // si b[i] == '?'
        // dos ramas: + o -
        backtrack(b, i + 1, posActual + 1, posDeseada, coincidencias);
        backtrack(b, i + 1, posActual - 1, posDeseada, coincidencias);
    }

}

#ifndef LOCAL
int main() {
    string instrucciones;
    string instrucciones_recibidas;
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;
    cin >> instrucciones;
    cin >> instrucciones_recibidas;

    for (int i = 0; i < instrucciones_recibidas.size(); i++) {
        if (instrucciones_recibidas[i] == '?') {
            totalIncognitas++;
            hayInstruNoReconocidas = true;
        }
    }

    if (!hayInstruNoReconocidas) {
        res = probabilidad(instrucciones, instrucciones_recibidas);
    } else {
        int contadorCoincidencias = 0;
        const int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);

    }

    cout << fixed << setprecision(9) << res << endl;
    return 0;


}

#endif

