#pragma once
#include <string>
#include <sstream>
using namespace std;

class Turno {
private:
    int id;
    int idCliente;
    int idPeluquero;
    string fecha;
    string servicio;
    string estado; // "PENDIENTE", "ATENDIDO" o "CANCELADO"

public:
    Turno() {
        id = 0;
        idCliente = 0;
        idPeluquero = 0;
        fecha = "";
        servicio = "";
        estado = "PENDIENTE";
    }

    Turno(int id, int idCliente, int idPeluquero, string fecha, string servicio) {
        this->id = id;
        this->idCliente = idCliente;
        this->idPeluquero = idPeluquero;
        this->fecha = fecha;
        this->servicio = servicio;
        this->estado = "PENDIENTE";
    }

    int getId() { return id; }
    int getIdCliente() { return idCliente; }
    int getIdPeluquero() { return idPeluquero; }
    string getFecha() { return fecha; }
    string getServicio() { return servicio; }
    string getEstado() { return estado; }
    void setEstado(string e) { estado = e; }

    string toString() {
        ostringstream oss;
        oss << "Turno #" << id << " | Cliente " << idCliente << " | Peluquero " << idPeluquero
            << " | Fecha: " << fecha << " | Servicio: " << servicio << " | Estado: " << estado;
        return oss.str();
    }

    // Formato: id;idCliente;idPeluquero;fecha;servicio;estado
    string toArchivo() {
        ostringstream oss;
        oss << id << ";" << idCliente << ";" << idPeluquero << ";" << fecha << ";" << servicio << ";" << estado;
        return oss.str();
    }

    static Turno desdeArchivo(string linea) {
        Turno t;
        stringstream ss(linea);
        string campo;

        getline(ss, campo, ';'); t.id = stoi(campo);
        getline(ss, campo, ';'); t.idCliente = stoi(campo);
        getline(ss, campo, ';'); t.idPeluquero = stoi(campo);
        getline(ss, campo, ';'); t.fecha = campo;
        getline(ss, campo, ';'); t.servicio = campo;
        getline(ss, campo, ';'); t.estado = campo;

        return t;
    }
};