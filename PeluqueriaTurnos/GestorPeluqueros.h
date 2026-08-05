#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Peluquero.h"
#include "Utilidades.h"
using namespace std;

class GestorPeluqueros {
private:
    //Vector de peluqueros mantiene la lista en memoria mientras corre el programa
    vector<Peluquero> lista;
    string nombreArchivo;

	//Reescribe el archivo de peluqueros con la lista completa en memoria
    void guardarEnArchivo() {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (int i = 0; i < lista.size(); i++) {
                archivo << lista[i].toArchivo() << endl;
            }
            archivo.close();
        }
        else {
            cerr << "Error al abrir el archivo de peluqueros." << endl;
        }
    }

public:
    GestorPeluqueros() {
        nombreArchivo = "peluqueros.txt";
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                if (linea != "") {
                    lista.push_back(Peluquero::desdeArchivo(linea));
                }
            }
            archivo.close();
        }
    }
	//Busca el id mas alto y devuelve el siguiente para asignar a un nuevo peluquero
    int nuevoId() {
        int maxId = 0;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getId() > maxId) maxId = lista[i].getId();
        }
        return maxId + 1;
    }

	//Busca coincidencias en nombre y apellido, devuelve un vector con los peluqueros encontrados
    vector<Peluquero> buscarCoincidencias(string textoBuscado) {
        string buscado = aMinusculas(textoBuscado);
        vector<Peluquero> resultado;
        for (int i = 0; i < lista.size(); i++) {
            if (!lista[i].getActivo()) continue;
            string nombreCompleto = aMinusculas(lista[i].getNombre() + " " + lista[i].getApellido());
            if (nombreCompleto.find(buscado) != string::npos) {
                resultado.push_back(lista[i]);
            }
        }
        return resultado;
    }
    // Devuelve todos los peluqueros activos, sin filtrar por nombre.
    vector<Peluquero> getActivos() {
        vector<Peluquero> resultado;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getActivo()) resultado.push_back(lista[i]);
        }
        return resultado;
    }


    void alta(Peluquero p) {
        lista.push_back(p);
        guardarEnArchivo();
    }
	//No elimina, solo marca como inactivo y reescribe el archivo
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
    //Lista los peluqueros activos
    void listar() {
        bool hayAlguno = false;
        for (int i = 0; i < lista.size(); i++) {
            if (lista[i].getActivo()) {
                cout << lista[i].toString() << endl;
                hayAlguno = true;
            }
        }
        if (!hayAlguno) cout << "No hay peluqueros cargados." << endl;
    }
};