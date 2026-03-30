#include "Curso.h"

//  Constructor
Curso::Curso() {}

//  buscar
int Curso::buscar(const string& cedula) const {
    for (int i = 0; i < (int)estudiantes.size(); i++)
        if (estudiantes[i].getCedula() == cedula)
            return i;
    return -1;
}

//  Getters de estado
int  Curso::getCantEstudiantes() const { return (int)estudiantes.size(); }
bool Curso::estaLleno()          const { return (int)estudiantes.size() >= MAX_ESTUDIANTES; }
bool Curso::estaVacio()          const { return estudiantes.empty(); }
int  Curso::getMaxEstudiantes()  const { return MAX_ESTUDIANTES; }
int  Curso::getMaxNotas()        const { return MAX_NOTAS; }

Estudiante& Curso::getEstudiante(int indice) {
    return estudiantes[indice];
}

//  CRUD estudiantes
bool Curso::insertar(const Estudiante& e) {
    if (estaLleno()) return false;
    if (buscar(e.getCedula()) != -1) return false;  // cedula duplicada
    estudiantes.push_back(e);
    return true;
}

bool Curso::modificar(int indice, const string& cedula, const string& nombres,
                      const string& apellidos, int dia, int mes, int anio) {
    if (indice < 0 || indice >= (int)estudiantes.size()) return false;
    // Verificar cedula duplicada (excluir el propio registro)
    int idx = buscar(cedula);
    if (idx != -1 && idx != indice) return false;

    if (!cedula.empty())    estudiantes[indice].setCedula(cedula);
    if (!nombres.empty())   estudiantes[indice].setNombres(nombres);
    if (!apellidos.empty()) estudiantes[indice].setApellidos(apellidos);
    if (dia  > 0) estudiantes[indice].setDia(dia);
    if (mes  > 0) estudiantes[indice].setMes(mes);
    if (anio > 0) estudiantes[indice].setAnio(anio);
    return true;
}

bool Curso::eliminar(int indice) {
    if (indice < 0 || indice >= (int)estudiantes.size()) return false;
    estudiantes.erase(estudiantes.begin() + indice);
    return true;
}

//  Calificaciones
bool Curso::agregarNota(int indice, double nota) {
    if (indice < 0 || indice >= (int)estudiantes.size()) return false;
    if (estudiantes[indice].getCantNotas() >= MAX_NOTAS)  return false;
    estudiantes[indice].agregarNota(nota);
    return true;
}

bool Curso::modificarNota(int indice, int indNota, double nota) {
    if (indice < 0 || indice >= (int)estudiantes.size()) return false;
    estudiantes[indice].modificarNota(indNota, nota);
    return true;
}

bool Curso::eliminarNota(int indice, int indNota) {
    if (indice < 0 || indice >= (int)estudiantes.size()) return false;
    estudiantes[indice].eliminarNota(indNota);
    return true;
}

// Promedios
bool Curso::hayCalificaciones() const {
    for (const Estudiante& e : estudiantes)
        if (e.getCantNotas() > 0) return true;
    return false;
}

double Curso::promedioCurso() const {
    double suma  = 0.0;
    int    total = 0;
    for (const Estudiante& e : estudiantes) {
        for (double n : e.getNotas()) {
            suma += n;
            total++;
        }
    }
    return total > 0 ? suma / total : 0.0;
}
