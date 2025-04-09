#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


int probabilidad(const string& a, const string& b) {
    int sumaAvanzarA = 0, sumaRetrocederA = 0, sumaAvanzarB = 0, sumaRetrocederB = 0;
    int posParcialA = 0, posParcialB = 0;
    for(int i = 0; i < a.size(); i++) {
        if (a[i] == '+') {
            sumaAvanzarA++;
        } else {
            sumaRetrocederA++;
        }

    }
    for(int i = 0; i < b.size(); i++) {
        if (b[i] == '+') {
            sumaAvanzarB++;
        } else {
            sumaRetrocederB++;
        }
    }
    posParcialA = sumaAvanzarA - sumaRetrocederA;
    posParcialB = sumaAvanzarB - sumaRetrocederB;

    if (posParcialA == posParcialB) {
        return 1;
    }
    return 0;

}

void backtrack(const string& a ,string& b, int i, int& c, int d) {

    if (i == b.length()) {
        if (b == a) {
            c++;
        }
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
