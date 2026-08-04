#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
using namespace std;

inline void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline int leerEntero(string mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Dato invalido, ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

inline int leerEnteroEnRango(string mensaje, int minimo, int maximo) {
    int valor = leerEntero(mensaje);
    while (valor < minimo || valor > maximo) {
        cout << "El valor debe estar entre " << minimo << " y " << maximo << "." << endl;
        valor = leerEntero(mensaje);
    }
    return valor;
}

inline string leerTexto(string mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

inline void pausar() {
    cout << endl << "Presione Enter para continuar...";
    cin.get();
}

inline string aMinusculas(string texto) {
    for (int i = 0; i < texto.size(); i++) {
        texto[i] = tolower(texto[i]);
    }
    return texto;
}