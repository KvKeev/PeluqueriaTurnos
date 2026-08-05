#include <iostream>
#include <vector>
#include "GestorPeluqueros.h"
#include "GestorClientes.h"
#include "GestorTurnos.h"
#include "Utilidades.h"
using namespace std;

// Busca clientes por nombre/apellido y muestra una lista numerada para elegir.
// Se puede cancelar dejando la busqueda vacia, o eligiendo la opcion 0 de la lista.
// Devuelve -1 si no encuentra nada o si el usuario cancela.
int seleccionarClientePorNombre(GestorClientes& g) {
    string texto = leerTexto("Nombre o apellido a buscar (Enter para cancelar): ");
    if (texto.empty()) {
        cout << "Operacion cancelada." << endl;
        return -1;
    }

    vector<Cliente> coincidencias = g.buscarCoincidencias(texto);
    if (coincidencias.empty()) {
        cout << "No se encontraron clientes con ese nombre." << endl;
        return -1;
    }

    cout << "Se encontraron los siguientes clientes:" << endl;
    for (int i = 0; i < coincidencias.size(); i++) {
        cout << (i + 1) << ") " << coincidencias[i].getNombre() << " " << coincidencias[i].getApellido()
            << " | Tel: " << coincidencias[i].getTelefono() << endl;
    }
    cout << "0) Cancelar" << endl;
    int opcion = leerEnteroEnRango("Elegi un numero: ", 0, (int)coincidencias.size());
    if (opcion == 0) {
        cout << "Operacion cancelada." << endl;
        return -1;
    }
    return coincidencias[opcion - 1].getId();
}

// Lo mismo pero para peluqueros
int seleccionarPeluqueroPorNombre(GestorPeluqueros& g) {
    string texto = leerTexto("Nombre o apellido a buscar (Enter para cancelar): ");
    if (texto.empty()) {
        cout << "Operacion cancelada." << endl;
        return -1;
    }

    vector<Peluquero> coincidencias = g.buscarCoincidencias(texto);
    if (coincidencias.empty()) {
        cout << "No se encontraron peluqueros con ese nombre." << endl;
        return -1;
    }

    cout << "Se encontraron los siguientes peluqueros:" << endl;
    for (int i = 0; i < coincidencias.size(); i++) {
        cout << (i + 1) << ") " << coincidencias[i].getNombre() << " " << coincidencias[i].getApellido()
            << " | Tel: " << coincidencias[i].getTelefono() << endl;
    }
    cout << "0) Cancelar" << endl;
    int opcion = leerEnteroEnRango("Elegi un numero: ", 0, (int)coincidencias.size());
    if (opcion == 0) {
        cout << "Operacion cancelada." << endl;
        return -1;
    }
    return coincidencias[opcion - 1].getId();
}

void menuPeluqueros(GestorPeluqueros& g) {
    int op;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE PELUQUEROS ===" << endl;
        cout << "1. Alta" << endl;
        cout << "2. Baja" << endl;
        cout << "3. Modificar" << endl;
        cout << "4. Listar" << endl;
        cout << "5. Buscar por nombre" << endl;
        cout << "0. Volver" << endl;
        op = leerEnteroEnRango("Opcion: ", 0, 5);

        if (op == 1) {
            int id = g.nuevoId();
            cout << "ID asignado: " << id << endl;
            string nombre = leerTexto("Nombre: ");
            string apellido = leerTexto("Apellido: ");
            string telefono = leerTelefono("Telefono: ");
            g.alta(Peluquero(id, nombre, apellido, telefono));
            cout << "Peluquero cargado con exito." << endl;
        }
        else if (op == 2) {
            int id = seleccionarPeluqueroPorNombre(g);
            if (id != -1) {
                if (g.baja(id)) cout << "Baja realizada." << endl;
                else cout << "No se pudo dar de baja." << endl;
            }
        }
        else if (op == 3) {
            int id = seleccionarPeluqueroPorNombre(g);
            if (id != -1) {
                string nombre = leerTexto("Nuevo nombre: ");
                string apellido = leerTexto("Nuevo apellido: ");
                string telefono = leerTelefono("Nuevo telefono: ");
                if (g.modificar(id, nombre, apellido, telefono)) cout << "Peluquero modificado con exito." << endl;
                else cout << "No se pudo modificar." << endl;
            }
        }
        else if (op == 4) {
            g.listar();
        }
        else if (op == 5) {
            string texto = leerTexto("Nombre o apellido a buscar: ");
            if (texto.empty()) {
                cout << "Tenes que escribir algo para buscar." << endl;
            }
            else {
                vector<Peluquero> coincidencias = g.buscarCoincidencias(texto);
                if (coincidencias.empty()) cout << "No se encontraron peluqueros con ese nombre." << endl;
                else for (int i = 0; i < coincidencias.size(); i++) cout << coincidencias[i].toString() << endl;
            }
        }

        if (op != 0) pausar();
    } while (op != 0);
}

void menuClientes(GestorClientes& g) {
    int op;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE CLIENTES ===" << endl;
        cout << "1. Alta" << endl;
        cout << "2. Baja" << endl;
        cout << "3. Modificar" << endl;
        cout << "4. Listar" << endl;
        cout << "5. Buscar por nombre" << endl;
        cout << "0. Volver" << endl;
        op = leerEnteroEnRango("Opcion: ", 0, 5);

        if (op == 1) {
            int id = g.nuevoId();
            cout << "ID asignado: " << id << endl;
            string nombre = leerTexto("Nombre: ");
            string apellido = leerTexto("Apellido: ");
            string telefono = leerTelefono("Telefono: ");
            g.alta(Cliente(id, nombre, apellido, telefono));
            cout << "Cliente cargado con exito." << endl;
        }
        else if (op == 2) {
            int id = seleccionarClientePorNombre(g);
            if (id != -1) {
                if (g.baja(id)) cout << "Baja realizada." << endl;
                else cout << "No se pudo dar de baja." << endl;
            }
        }
        else if (op == 3) {
            int id = seleccionarClientePorNombre(g);
            if (id != -1) {
                string nombre = leerTexto("Nuevo nombre: ");
                string apellido = leerTexto("Nuevo apellido: ");
                string telefono = leerTelefono("Nuevo telefono: ");
                if (g.modificar(id, nombre, apellido, telefono)) cout << "Cliente modificado con exito." << endl;
                else cout << "No se pudo modificar." << endl;
            }
        }
        else if (op == 4) {
            g.listar();
        }
        else if (op == 5) {
            string texto = leerTexto("Nombre o apellido a buscar: ");
            if (texto.empty()) {
                cout << "Tenes que escribir algo para buscar." << endl;
            }
            else {
                vector<Cliente> coincidencias = g.buscarCoincidencias(texto);
                if (coincidencias.empty()) cout << "No se encontraron clientes con ese nombre." << endl;
                else for (int i = 0; i < coincidencias.size(); i++) cout << coincidencias[i].toString() << endl;
            }
        }

        if (op != 0) pausar();
    } while (op != 0);
}

void menuTurnos(GestorTurnos& gt, GestorClientes& gc, GestorPeluqueros& gp) {
    int op;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE TURNOS ===" << endl;
        cout << "1. Asignar turno" << endl;
        cout << "2. Cancelar turno" << endl;
        cout << "3. Atender siguiente" << endl;
        cout << "4. Ver historial de atendidos" << endl;
        cout << "5. Ver todos los turnos" << endl;
        cout << "0. Volver" << endl;
        op = leerEnteroEnRango("Opcion: ", 0, 5);

        if (op == 1) {
            cout << "--- Cliente ---" << endl;
            int idCliente = seleccionarClientePorNombre(gc);
            if (idCliente != -1) {
                cout << "--- Peluquero ---" << endl;
                int idPeluquero = seleccionarPeluqueroPorNombre(gp);
                if (idPeluquero != -1) {
                    string servicio = leerTexto("Servicio: ");
                    gt.asignar(idCliente, idPeluquero, servicio);
                    cout << "Turno asignado con exito." << endl;
                }
            }
        }
        else if (op == 2) {
            gt.listarTodos();
            int id = leerEntero("Numero de turno a cancelar: ");
            if (gt.cancelar(id)) cout << "Turno cancelado." << endl;
            else cout << "No se encontro un turno pendiente con ese ID." << endl;
        }
        else if (op == 3) {
            if (gt.atenderSiguiente()) cout << "Se atendio al siguiente cliente de la fila." << endl;
            else cout << "No hay turnos pendientes en la fila." << endl;
        }
        else if (op == 4) {
            gt.listarHistorial();
        }
        else if (op == 5) {
            gt.listarTodos();
        }

        if (op != 0) pausar();
    } while (op != 0);
}

int main() {

	// Inicializa los gestores de peluqueros, clientes y turnos
    GestorPeluqueros gp;
    GestorClientes gc;
    GestorTurnos gt;

    int op;
    do {
        limpiarPantalla();
        cout << "====== SISTEMA DE TURNOS - PELUQUERIA ======" << endl;
        cout << "1. Gestion de Peluqueros" << endl;
        cout << "2. Gestion de Clientes" << endl;
        cout << "3. Gestion de Turnos" << endl;
        cout << "0. Salir" << endl;
        op = leerEnteroEnRango("Opcion: ", 0, 3);

        if (op == 1) menuPeluqueros(gp);
        else if (op == 2) menuClientes(gc);
        else if (op == 3) menuTurnos(gt, gc, gp);

    } while (op != 0);

    cout << "Saliendo del sistema..." << endl;
    return 0;
}