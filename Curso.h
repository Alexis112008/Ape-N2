#ifndef CURSO_H
#define CURSO_H

#include "Estudiante.h"
#include <vector>

using namespace std;

class Curso {
private:
    vector<Estudiante> estudiantes;
    static const int MAX_ESTUDIANTES = 20;
    static const int MAX_NOTAS       = 7;

public:
    Curso();

    // Buscar estudiante por cedula, retorna indice o -1
    int buscar(const string& cedula) const;

    // Getters de estado
    int  getCantEstudiantes() const;
    bool estaLleno()          const;
    bool estaVacio()          const;
    Estudiante& getEstudiante(int indice);

    // CRUD estudiantes
    bool insertar(const Estudiante& e);
    bool modificar(int indice, const string& cedula, const string& nombres,
                   const string& apellidos, int dia, int mes, int anio);
    bool eliminar(int indice);

    // Calificaciones
    bool agregarNota(int indice, double nota);
    bool modificarNota(int indice, int indNota, double nota);
    bool eliminarNota(int indice, int indNota);

    // Promedios
    double promedioCurso() const;
    bool   hayCalificaciones() const;

    // Constantes accesibles
    int getMaxEstudiantes() const;
    int getMaxNotas()       const;
};

#endif
