#include "Estudiante.h"
#include <ctime>

// Constructores
Estudiante::Estudiante()
    : cedula(""), nombres(""), apellidos(""),
      dia_nac(1), mes_nac(1), anio_nac(2000) {}

Estudiante::Estudiante(const string& cedula, const string& nombres,
                       const string& apellidos, int dia, int mes, int anio)
    : cedula(cedula), nombres(nombres), apellidos(apellidos),
      dia_nac(dia), mes_nac(mes), anio_nac(anio) {}

//  Getters
string Estudiante::getCedula()    const { return cedula; }
string Estudiante::getNombres()   const { return nombres; }
string Estudiante::getApellidos() const { return apellidos; }
int    Estudiante::getDia()       const { return dia_nac; }
int    Estudiante::getMes()       const { return mes_nac; }
int    Estudiante::getAnio()      const { return anio_nac; }
int    Estudiante::getCantNotas() const { return (int)notas.size(); }

vector<double> Estudiante::getNotas() const { return notas; }

//  Setters
void Estudiante::setCedula(const string& c)    { cedula    = c; }
void Estudiante::setNombres(const string& n)   { nombres   = n; }
void Estudiante::setApellidos(const string& a) { apellidos = a; }
void Estudiante::setDia(int d)  { dia_nac  = d; }
void Estudiante::setMes(int m)  { mes_nac  = m; }
void Estudiante::setAnio(int a) { anio_nac = a; }

//  Métodos de notas
void Estudiante::agregarNota(double nota) {
    notas.push_back(nota);
}

void Estudiante::modificarNota(int indice, double nota) {
    if (indice >= 0 && indice < (int)notas.size())
        notas[indice] = nota;
}

void Estudiante::eliminarNota(int indice) {
    if (indice >= 0 && indice < (int)notas.size())
        notas.erase(notas.begin() + indice);
}

// Métodos de cálculo
int Estudiante::calcularEdad() const {
    time_t t   = time(nullptr);
    tm*    hoy = localtime(&t);
    int anio_h = hoy->tm_year + 1900;
    int mes_h  = hoy->tm_mon  + 1;
    int dia_h  = hoy->tm_mday;

    int edad = anio_h - anio_nac;
    if (mes_h < mes_nac || (mes_h == mes_nac && dia_h < dia_nac))
        edad--;
    return edad;
}

double Estudiante::promedioNotas() const {
    if (notas.empty()) return 0.0;
    double suma = 0.0;
    for (double n : notas) suma += n;
    return suma / notas.size();
}
