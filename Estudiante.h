#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>

using namespace std;

class Estudiante {
private:
    string cedula;
    string nombres;
    string apellidos;
    int    dia_nac;
    int    mes_nac;
    int    anio_nac;
    vector<double> notas;  // maximo 7 notas

public:
    // Constructores
    Estudiante();
    Estudiante(const string& cedula, const string& nombres,
               const string& apellidos, int dia, int mes, int anio);

    // Getters
    string getCedula()    const;
    string getNombres()   const;
    string getApellidos() const;
    int    getDia()       const;
    int    getMes()       const;
    int    getAnio()      const;
    vector<double> getNotas() const;
    int    getCantNotas() const;

    // Setters
    void setCedula(const string& cedula);
    void setNombres(const string& nombres);
    void setApellidos(const string& apellidos);
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    // Metodos de notas
    void   agregarNota(double nota);
    void   modificarNota(int indice, double nota);
    void   eliminarNota(int indice);

    // Metodos de calculo
    int    calcularEdad()    const;
    double promedioNotas()   const;
};

#endif
