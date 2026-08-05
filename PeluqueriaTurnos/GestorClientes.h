#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Cliente.h"
#include "Utilidades.h"
using namespace std;

class GestorClientes {
private:
	//Vector de clientes mantiene la lista en memoria mientras corre el programa
    vector<Cliente> lista;
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
            cerr << "Error al abrir el archivo de clientes." << endl;
        }
    }

public:
    GestorClientes() {
        nombreArchivo = "clientes.txt";
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                if (linea != "") {
                    lista.push_back(Cliente::desdeArchivo(linea));
                }
            }
            archivo.close();
        }
    }

	//Busca el id mas alto y devuelve el siguiente para asignar a un nuevo cliente
    int nuevoId() {
        int maxId = 0;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() > maxId) maxId = lista[i].getId();
        }
        return maxId + 1;
    }

	//Busca coincidencias en nombre y apellido, devuelve un vector con los clientes encontrados
    vector<Cliente> buscarCoincidencias(string textoBuscado) {
        string buscado = aMinusculas(textoBuscado);
        vector<Cliente> resultado;
        for (int i = 0; i < lista.size(); i++) {
            if (!lista[i].getActivo()) continue;
            string nombreCompleto = aMinusculas(lista[i].getNombre() + " " + lista[i].getApellido());
            if (nombreCompleto.find(buscado) != string::npos) {
                resultado.push_back(lista[i]);
            }
        }
        return resultado;
    }

    void alta(Cliente c) {
        lista.push_back(c);
        guardarEnArchivo();
    }

    bool baja(int id) {
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() == id && lista[i].getActivo()) {
                lista[i].setActivo(false);
                guardarEnArchivo();
                return true;
            }
        }
        return false;
    }

    bool modificar(int id, string nombre, string apellido, string telefono) {
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() == id && lista[i].getActivo()) {
                lista[i].setNombre(nombre);
                lista[i].setApellido(apellido);
                lista[i].setTelefono(telefono);
                guardarEnArchivo();
                return true;
            }
        }
        return false;
    }
	// Muestra todos los clientes activos en la consola
    void listar() {
        bool hayAlguno = false;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getActivo()) {
                cout << lista[i].toString() << endl;
                hayAlguno = true;
            }
        }
        if (!hayAlguno) cout << "No hay clientes cargados." << endl;
    }
};