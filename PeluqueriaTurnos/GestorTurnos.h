#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include "Turno.h"
using namespace std;

class GestorTurnos {
private:
	vector<Turno> lista;       // Lista completa de turnos (pendientes, atendidos y cancelados)
	queue<Turno> pendientes;   // turnos pendientes de atender
	stack<Turno> historial;    // Historial de turnos atendidos
    string nombreArchivo;

    void guardarEnArchivo() {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (int i = 0; i < lista.size(); i++) {
                archivo << lista[i].toArchivo() << endl;
            }
            archivo.close();
        }
        else {
            cerr << "Error al abrir el archivo de turnos." << endl;
        }
    }

	// Reconstruye la cola de pendientes a partir de la lista completa
    void rearmarCola() {
        while (!pendientes.empty()) pendientes.pop();
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getEstado() == "PENDIENTE") pendientes.push(lista[i]);
        }
    }

public:
	// Constructor que carga los turnos desde el archivo y reconstruye la cola de pendientes y la pila de historial
    GestorTurnos() {
        nombreArchivo = "turnos.txt";
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                if (linea != "") {
                    lista.push_back(Turno::desdeArchivo(linea));
                }
            }
            archivo.close();
        }
        rearmarCola();
		// Reconstruye la pila de historial a partir de la lista completa
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getEstado() == "ATENDIDO") historial.push(lista[i]);
        }
    }

    int nuevoId() {
        int maxId = 0;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() > maxId) maxId = lista[i].getId();
        }
        return maxId + 1;
    }
	// Crea un nuevo turno, lo agrega a la lista completa y a la cola de pendientes
    void asignar(int idCliente, int idPeluquero, string servicio) {
        Turno t(nuevoId(), idCliente, idPeluquero, servicio);
        lista.push_back(t);
        pendientes.push(t); // entra al final de la fila
        guardarEnArchivo();
    }

    // Saca el primero de la cola y lo marca ATENDIDO
    bool atenderSiguiente() {
        if (pendientes.empty()) return false;

        Turno t = pendientes.front();
        pendientes.pop();

        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() == t.getId()) {
                lista[i].setEstado("ATENDIDO");
                historial.push(lista[i]); // se apila para el historial
                break;
            }
        }
        guardarEnArchivo();
        return true;
    }

    bool cancelar(int id) {
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() == id && lista[i].getEstado() == "PENDIENTE") {
                lista[i].setEstado("CANCELADO");
                rearmarCola(); // lo saca de la fila porque ya no esta pendiente
                guardarEnArchivo();
                return true;
            }
        }
        return false;
    }

	// Muestra los turnos atendidos en orden inverso al que fueron atendidos. Realiza una copia de la pila para no vaciar la original.
    void listarHistorial() {
        if (historial.empty()) {
            cout << "Todavia no se atendio ningun turno." << endl;
            return;
        }
        stack<Turno> copia = historial; // se copia para no vaciar la pila real
        while (!copia.empty()) {
            cout << copia.top().toString() << endl;
            copia.pop();
        }
    }

    void listarTodos() {
        if (lista.empty()) {
            cout << "No hay turnos cargados." << endl;
            return;
        }
        for (int i = 0; i < lista.size(); i++) {
            cout << lista[i].toString() << endl;
        }
    }
};