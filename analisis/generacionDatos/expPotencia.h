#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include "../../include/calculoAutovectores/calculoAutovectores.h"

using namespace std;
using namespace Eigen;

// Toma una matriz y su autovalor dominante y corre el algoritmo 30 veces por cada cantidad de iteracion fija
// Guarda todo en un csv con la cantidad de iteraciones en el header y el error al finalizar en la columna correspondiente

void errorPorIteraciones(MatrixXd& m, double autovalorDominante, string nombreArchivo, int cantIter);
void correrTestsIteraciones();
void correrTestsTiempo();