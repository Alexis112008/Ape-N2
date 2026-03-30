#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Curso.h"

using namespace std;

// ══════════════════════════════════════════════════════════════
//  Utilidades de E/S
// ══════════════════════════════════════════════════════════════
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    limpiarBuffer();
}

void limpiarPantalla() {
    cout << "\033[2J\033[1;1H";
}

int leerEntero(const string& prompt, int minVal, int maxVal) {
    int valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor >= minVal && valor <= maxVal) {
            limpiarBuffer();
            return valor;
        }
        cin.clear();
        limpiarBuffer();
        cout << "  [!] Ingrese un numero entre " << minVal << " y " << maxVal << ".\n";
    }
}

double leerDouble(const string& prompt, double minVal, double maxVal) {
    double valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor >= minVal && valor <= maxVal) {
            limpiarBuffer();
            return valor;
        }
        cin.clear();
        limpiarBuffer();
        cout << "  [!] Ingrese un numero entre " << minVal << " y " << maxVal << ".\n";
    }
}

string leerLinea(const string& prompt) {
    string linea;
    while (true) {
        cout << prompt;
        getline(cin, linea);
        size_t ini = linea.find_first_not_of(" \t");
        if (ini != string::npos) {
            linea = linea.substr(ini);
            size_t fin = linea.find_last_not_of(" \t");
            linea = linea.substr(0, fin + 1);
        }
        if (!linea.empty()) return linea;
        cout << "  [!] El campo no puede estar vacio.\n";
    }
}

bool confirmar(const string& pregunta) {
    char resp;
    cout << pregunta << " (s/n): ";
    cin  >> resp;
    limpiarBuffer();
    return (resp == 's' || resp == 'S');
}

// ══════════════════════════════════════════════════════════════
//  Mostrar listado de estudiantes
// ══════════════════════════════════════════════════════════════
void mostrarListado(Curso& curso) {
    cout << "\n"
         << left
         << setw(4)  << "#"
         << setw(14) << "Cedula"
         << setw(20) << "Nombres"
         << setw(20) << "Apellidos"
         << setw(12) << "Fec.Nac"
         << setw(5)  << "Edad"
         << "\n"
         << string(75, '-') << "\n";

    for (int i = 0; i < curso.getCantEstudiantes(); i++) {
        Estudiante& e = curso.getEstudiante(i);
        string fec = to_string(e.getDia())  + "/" +
                     to_string(e.getMes())  + "/" +
                     to_string(e.getAnio());
        cout << left
             << setw(4)  << (i + 1)
             << setw(14) << e.getCedula()
             << setw(20) << e.getNombres()
             << setw(20) << e.getApellidos()
             << setw(12) << fec
             << setw(5)  << e.calcularEdad()
             << "\n";
    }
}

// ══════════════════════════════════════════════════════════════
//  OPCIÓN 1 — Gestión de estudiantes
// ══════════════════════════════════════════════════════════════

void insertarEstudiante(Curso& curso) {
    if (curso.estaLleno()) {
        cout << "\n[!] El curso ya tiene el maximo de "
             << curso.getMaxEstudiantes() << " estudiantes.\n";
        return;
    }
    bool seguir = true;
    while (seguir && !curso.estaLleno()) {
        cout << "\n--- Nuevo estudiante ---\n";
        string ced = leerLinea("  Cedula       : ");
        string nom = leerLinea("  Nombres      : ");
        string ape = leerLinea("  Apellidos    : ");
        int d = leerEntero("  Dia nac.     : ", 1, 31);
        int m = leerEntero("  Mes nac.     : ", 1, 12);
        int a = leerEntero("  Anio nac.    : ", 1900, 2100);

        Estudiante nuevo(ced, nom, ape, d, m, a);
        if (curso.insertar(nuevo))
            cout << "  [OK] Estudiante registrado.\n";
        else
            cout << "  [!] Ya existe un estudiante con esa cedula.\n";

        if (!curso.estaLleno())
            seguir = confirmar("  ¿Ingresar otro estudiante?");
        else {
            cout << "  [!] Se alcanzo el maximo de estudiantes.\n";
            seguir = false;
        }
    }
}

void modificarEstudiante(Curso& curso) {
    if (curso.estaVacio()) {
        cout << "\n[!] No hay estudiantes registrados.\n";
        return;
    }
    bool seguir = true;
    while (seguir) {
        mostrarListado(curso);
        int num = leerEntero("\n  Numero a modificar (0 = cancelar): ",
                             0, curso.getCantEstudiantes());
        if (num == 0) return;

        Estudiante& e = curso.getEstudiante(num - 1);
        cout << "\n  (ENTER para conservar valor actual)\n\n";

        cout << "  Cedula [" << e.getCedula() << "]: ";
        string tmp; getline(cin, tmp);
        string ced = tmp.empty() ? "" : tmp;

        cout << "  Nombres [" << e.getNombres() << "]: ";
        getline(cin, tmp);
        string nom = tmp;

        cout << "  Apellidos [" << e.getApellidos() << "]: ";
        getline(cin, tmp);
        string ape = tmp;

        cout << "  Dia [" << e.getDia() << "]: ";
        getline(cin, tmp);
        int d = tmp.empty() ? 0 : stoi(tmp);

        cout << "  Mes [" << e.getMes() << "]: ";
        getline(cin, tmp);
        int m = tmp.empty() ? 0 : stoi(tmp);

        cout << "  Anio [" << e.getAnio() << "]: ";
        getline(cin, tmp);
        int a = tmp.empty() ? 0 : stoi(tmp);

        if (curso.modificar(num - 1, ced, nom, ape, d, m, a))
            cout << "  [OK] Datos actualizados.\n";
        else
            cout << "  [!] Cedula duplicada. No se pudo actualizar.\n";

        seguir = confirmar("  ¿Modificar otro estudiante?");
    }
}

void eliminarEstudiante(Curso& curso) {
    if (curso.estaVacio()) {
        cout << "\n[!] No hay estudiantes para eliminar.\n";
        return;
    }
    bool seguir = true;
    while (seguir && !curso.estaVacio()) {
        mostrarListado(curso);
        int num = leerEntero("\n  Numero a eliminar (0 = cancelar): ",
                             0, curso.getCantEstudiantes());
        if (num == 0) return;

        Estudiante& e = curso.getEstudiante(num - 1);
        cout << "  Eliminar: " << e.getNombres() << " " << e.getApellidos() << "\n";
        if (confirmar("  ¿Confirma?")) {
            curso.eliminar(num - 1);
            cout << "  [OK] Estudiante eliminado.\n";
        } else {
            cout << "  Cancelado.\n";
        }
        if (!curso.estaVacio())
            seguir = confirmar("  ¿Eliminar otro estudiante?");
    }
}

void menuEstudiantes(Curso& curso) {
    int op;
    do {
        limpiarPantalla();
        cout << "\n=== GESTION DE ESTUDIANTES ===\n";
        cout << "Registrados: " << curso.getCantEstudiantes()
             << " / " << curso.getMaxEstudiantes() << "\n";

        if (!curso.estaVacio())
            mostrarListado(curso);
        else
            cout << "\n  (Sin estudiantes registrados)\n";

        cout << "\n  1. Ingresar\n"
             << "  2. Modificar\n"
             << "  3. Eliminar\n"
             << "  0. Volver\n";
        op = leerEntero("\n  Opcion (0-3): ", 0, 3);

        switch (op) {
            case 1: insertarEstudiante(curso); pausar(); break;
            case 2: modificarEstudiante(curso); pausar(); break;
            case 3: eliminarEstudiante(curso);  pausar(); break;
        }
    } while (op != 0);
}

// ══════════════════════════════════════════════════════════════
//  OPCIÓN 2 — Registro de calificaciones
// ══════════════════════════════════════════════════════════════
void menuCalificaciones(Curso& curso) {
    if (curso.estaVacio()) {
        cout << "\n[!] No hay estudiantes registrados.\n";
        pausar();
        return;
    }

    bool buscarOtro = true;
    while (buscarOtro) {
        limpiarPantalla();
        cout << "\n=== REGISTRO DE CALIFICACIONES ===\n";
        string ced = leerLinea("  Cedula del estudiante: ");
        int idx = curso.buscar(ced);

        if (idx == -1) {
            cout << "  [!] No se encontro estudiante con cedula: " << ced << "\n";
            buscarOtro = confirmar("  ¿Ingresar otra cedula?");
            continue;
        }

        Estudiante& e = curso.getEstudiante(idx);
        bool gestionando = true;

        while (gestionando) {
            limpiarPantalla();
            cout << "\n=== CALIFICACIONES ===\n";
            cout << "  Estudiante : " << e.getNombres() << " " << e.getApellidos() << "\n";
            cout << "  Edad       : " << e.calcularEdad() << " anios\n";
            cout << "  Notas (" << e.getCantNotas() << "/" << curso.getMaxNotas() << "):\n";

            if (e.getCantNotas() == 0) {
                cout << "    (Sin calificaciones)\n";
            } else {
                vector<double> notas = e.getNotas();
                for (int i = 0; i < (int)notas.size(); i++)
                    cout << "    " << (i+1) << ". "
                         << fixed << setprecision(2) << notas[i] << "\n";
            }

            if (e.getCantNotas() >= curso.getMaxNotas()) {
                cout << "\n  [!] Se ingresaron todas las calificaciones posibles ("
                     << curso.getMaxNotas() << "/" << curso.getMaxNotas() << ").\n";
                pausar();
                gestionando = false;
                buscarOtro  = false;
                break;
            }

            cout << "\n  1. Insertar calificacion\n";
            if (e.getCantNotas() > 0)
                cout << "  2. Modificar calificacion\n"
                     << "  3. Eliminar calificacion\n";
            cout << "  0. Volver\n";

            int maxOp = (e.getCantNotas() > 0) ? 3 : 1;
            int op = leerEntero("\n  Opcion: ", 0, maxOp);

            switch (op) {
                case 0:
                    gestionando = false;
                    buscarOtro  = false;
                    break;
                case 1: {
                    double nota = leerDouble("  Calificacion (0.0 - 10.0): ", 0.0, 10.0);
                    curso.agregarNota(idx, nota);
                    cout << "  [OK] Calificacion registrada.\n";
                    pausar();
                    break;
                }
                case 2: {
                    int num = leerEntero("  Numero de nota a modificar: ", 1, e.getCantNotas());
                    double nota = leerDouble("  Nueva calificacion (0.0 - 10.0): ", 0.0, 10.0);
                    curso.modificarNota(idx, num - 1, nota);
                    cout << "  [OK] Calificacion actualizada.\n";
                    pausar();
                    break;
                }
                case 3: {
                    int num = leerEntero("  Numero de nota a eliminar: ", 1, e.getCantNotas());
                    curso.eliminarNota(idx, num - 1);
                    cout << "  [OK] Calificacion eliminada.\n";
                    pausar();
                    break;
                }
            }
        }
    }
}

// ══════════════════════════════════════════════════════════════
//  OPCIÓN 3 — Promedio de un estudiante
// ══════════════════════════════════════════════════════════════
void promedioEstudiante(Curso& curso) {
    if (curso.estaVacio()) {
        cout << "\n[!] No hay estudiantes registrados.\n";
        pausar();
        return;
    }
    limpiarPantalla();
    cout << "\n=== PROMEDIO DE UN ESTUDIANTE ===\n";
    string ced = leerLinea("  Cedula del estudiante: ");
    int idx = curso.buscar(ced);

    if (idx == -1) {
        cout << "  [!] No se encontro un estudiante con cedula: " << ced << "\n";
    } else {
        Estudiante& e = curso.getEstudiante(idx);
        cout << "\n  Nombres  : " << e.getNombres() << " " << e.getApellidos() << "\n";
        cout << "  Edad     : " << e.calcularEdad() << " anios\n";
        if (e.getCantNotas() == 0) {
            cout << "  Promedio : (sin calificaciones registradas)\n";
        } else {
            cout << "  Notas    : ";
            vector<double> notas = e.getNotas();
            for (int i = 0; i < (int)notas.size(); i++) {
                cout << fixed << setprecision(2) << notas[i];
                if (i < (int)notas.size()-1) cout << ", ";
            }
            cout << "\n";
            cout << "  Promedio : " << fixed << setprecision(2)
                 << e.promedioNotas() << "\n";
        }
    }
    pausar();
}

// ══════════════════════════════════════════════════════════════
//  OPCIÓN 4 — Promedio general del curso
// ══════════════════════════════════════════════════════════════
void promedioCurso(Curso& curso) {
    limpiarPantalla();
    cout << "\n=== PROMEDIO GENERAL DEL CURSO ===\n";
    if (!curso.hayCalificaciones()) {
        cout << "  No se han registrado calificaciones de estudiantes.\n";
    } else {
        cout << "  Promedio general: "
             << fixed << setprecision(2) << curso.promedioCurso() << "\n";
    }
    pausar();
}

// ══════════════════════════════════════════════════════════════
//  MAIN
// ══════════════════════════════════════════════════════════════
int main() {
    Curso curso;
    int opcion;

    do {
        limpiarPantalla();
        cout << "\n";

        cout << "       === GESTOR DE PERSONAS ===   \n";

        cout << "    1  Estudiantes                  \n";
        cout << "    2  Registro de calificaciones   \n";
        cout << "    3  Promedio de un estudiante    \n";
        cout << "    4  Promedio del curso           \n";
        cout << "    0  Salir                        \n";

        opcion = leerEntero("\n  Teclee su opcion (0-4): ", 0, 4);

        switch (opcion) {
            case 1: menuEstudiantes(curso);    break;
            case 2: menuCalificaciones(curso); break;
            case 3: promedioEstudiante(curso); break;
            case 4: promedioCurso(curso);      break;
            case 0: cout << "\n  Hasta luego.\n\n"; break;
        }
    } while (opcion != 0);

    return 0;
}

