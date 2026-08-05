#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
using namespace std;


// Limpia la pantalla de la consola segun si esta en windows o linux
inline void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Validacion de que sea un numero entero
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

inline string leerTelefono(string mensaje) {
    string valor;
    bool esValido;
    do {
        cout << mensaje;
        getline(cin, valor);

        esValido = !valor.empty();
        for (int i = 0; i < valor.size() && esValido; i++) {
            if (!isdigit(valor[i])) esValido = false;
        }

        if (!esValido) {
            cout << "Telefono invalido. Ingrese solo numeros, sin espacios ni guiones." << endl;
        }
    } while (!esValido);
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