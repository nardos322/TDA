#define LOCAL
#include "../src/main.cpp"
#include <gtest/gtest.h>

using namespace std;


TEST(hilocomunicadosTest, sinIncognitas) {
    const string instrucciones = "++--";
    string instrucciones_recibidas = "--++";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 1.0);


}


TEST(hilocomunicadosTest, test1) {
    const string instrucciones = "++";
    string instrucciones_recibidas = "++";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 1.0);


}

TEST(hilocomunicadosTest, test2) {
    const string instrucciones = "+-";
    string instrucciones_recibidas = "?-";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 0.5);

}


TEST(hilocomunicadosTest, test3) {
    const string instrucciones = "++";
    string instrucciones_recibidas = "?-";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 0.0);


}

TEST(hilocomunicadosTest, test4) {
    const string instrucciones = "+++-";
    string instrucciones_recibidas = "????";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 0.25);


}


TEST(hilocomunicadosTest, test5) {
    const string instrucciones = "++-++-++++";
    string instrucciones_recibidas = "??????-?+?";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 0.03125);


}

TEST(hilocomunicadosTest, test6) {
    const string instrucciones = "+-+---";
    string instrucciones_recibidas = "?-?-+?";
    int totalIncognitas = 0;
    double res = 0;
    bool hayInstruNoReconocidas = false;

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
        int posDeseada = posicion(instrucciones);
        int posActual = 0;
        backtrack(instrucciones_recibidas, 0, posActual, posDeseada, contadorCoincidencias);
        res = contadorCoincidencias / pow(2, totalIncognitas);
    }

    EXPECT_DOUBLE_EQ(res, 0.375);


}

