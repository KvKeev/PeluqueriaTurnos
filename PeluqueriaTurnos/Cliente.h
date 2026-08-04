#pragma once
#include <string>
#include <sstream>
using namespace std;

class Cliente {
private:
    int id;
    string nombre;
    string apellido;
    string telefono;
    bool activo;

public:
    Cliente() {
        id = 0;
        nombre = "";
        apellido = "";
        telefono = "";
        activo = true;
    }

    Cliente(int id, string nombre, string apellido, string telefono) {
        this->id = id;
        this->nombre = nombre;
        this->apellido = apellido;
        this->telefono = telefono;
        this->activo = true;
    }

    int getId() { return id; }
    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    string getTelefono() { return telefono; }
    bool getActivo() { return activo; }

    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }
    void setTelefono(string t) { telefono = t; }
    void setActivo(bool a) { activo = a; }

    string toString() {
        ostringstream oss;
        oss << "ID: " << id << " | " << nombre << " " << apellido
            << " | Telefono: " << telefono
            << " | " << (activo ? "Activo" : "Inactivo");
        return oss.str();
    }

    // Formato: id;nombre;apellido;telefono;activo
    string toArchivo() {
        ostringstream oss;
        oss << id << ";" << nombre << ";" << apellido << ";" << telefono << ";" << activo;
        return oss.str();
    }

    static Cliente desdeArchivo(string linea) {
        Cliente c;
        stringstream ss(linea);
        string campo;

        getline(ss, campo, ';'); c.id = stoi(campo);
        getline(ss, campo, ';'); c.nombre = campo;
        getline(ss, campo, ';'); c.apellido = campo;
        getline(ss, campo, ';'); c.telefono = campo;
        getline(ss, campo, ';'); c.activo = (campo == "1");

        return c;
    }
};