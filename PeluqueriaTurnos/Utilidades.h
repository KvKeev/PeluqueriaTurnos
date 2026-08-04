#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <cctype>
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

// Valida que el texto tenga formato dd/mm/aaaa, con numeros reales en cada parte
inline bool esFechaValida(string fecha) {
    if (fecha.size() != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(fecha[i])) return false;
    }
    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));
    if (dia < 1 || dia > 31) return false;
    if (mes < 1 || mes > 12) return false;
    if (anio < 2024 || anio > 2100) return false;
    return true;
}

// Pide una fecha por consola y no deja avanzar hasta que tenga formato valido
inline string leerFecha(string mensaje) {
    string fecha;
    do {
        cout << mensaje << " (formato dd/mm/aaaa): ";
        getline(cin, fecha);
        if (!esFechaValida(fecha)) {
            cout << "Fecha invalida. Debe tener el formato dd/mm/aaaa, por ejemplo 15/08/2026." << endl;
        }
    } while (!esFechaValida(fecha));
    return fecha;
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
// Pide un texto de busqueda que no este vacio (para evitar que matchee todo)
inline string leerTextoBusqueda(string mensaje) {
    string valor;
    do {
        cout << mensaje;
        getline(cin, valor);
        if (valor.empty()) {
            cout << "Tenes que escribir algo para buscar." << endl;
        }
    } while (valor.empty());
    return valor;
}