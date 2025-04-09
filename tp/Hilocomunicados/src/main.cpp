#include <iostream>
#include <string>
#include <cmath>

using namespace std;

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


int probabilidad(const string& a, const string& b) {

    const int posDeseada = posicion(a);
    const int posParcialB = posicion(b);

    if (posDeseada == posParcialB) {
        return 1;
    }
    return 0;

}

void backtrack(const string& a ,string& b, int i, int& c, int d) {

    if (i == b.length()) {

        if (probabilidad(a, b) == 1) {
            c++;
        }
        cout << b << endl;
        return;
    }

    if (b[i] == '?') {
        string pos = "+-";
        for (const auto j : pos) {
            b[i] = j;
            backtrack(a, b, i + 1, c, d);
            b[i] = '?';
        }
    } else {
        backtrack(a, b, i + 1, c, d);
    }



}


int main() {
    string instrucciones;
    string instrucciones_recibidas;
    int contadorInstruccionesNoReconocidas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;
    cin >> instrucciones;
    cin >> instrucciones_recibidas;

    for (int i = 0; i < instrucciones_recibidas.size(); i++) {
        if (instrucciones_recibidas[i] == '?') {
            contadorInstruccionesNoReconocidas++;
            hayInstruNoReconocidas = true;
        }
    }

    if (!hayInstruNoReconocidas) {
        res = probabilidad(instrucciones, instrucciones_recibidas);
    } else {
        int contadorInstruccionesIguales = 0;
        backtrack(instrucciones, instrucciones_recibidas, 0, contadorInstruccionesIguales, contadorInstruccionesNoReconocidas);
        res = contadorInstruccionesIguales / pow(2, contadorInstruccionesNoReconocidas);

    }

    cout << res << endl;
    return 0;






}
