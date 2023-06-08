#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;
using namespace Eigen;

/*
autovectorDominanteIteraciones corre la sucesion para n iteraciones fijas con una CI dada.
autovectorDominanteThreshold corre la sucesion para un array de CI en paralelo hasta que alguna llega al threshold.
La idea es compararlas en tiempo e iteraciones para un set fijado de condiciones iniciales (experimentacion),
y quedarnos con una para implementar autovectores().
*/

pair<double, VectorXd> autovectorDominanteIteraciones(MatrixXd& m, int nIter);
pair<double, VectorXd> autovectorDominanteIteraciones(MatrixXd& m, int nIter, VectorXd& ci);  // ci normalizada!
tuple<double, VectorXd, int> autovectorDominanteThreshold(MatrixXd& m, float threshold, int maxIter);
tuple<double, VectorXd, int> autovectorDominanteThreshold(MatrixXd& m, float threshold);

// Version posta de autovectorDominante luego de experimentar

void deflacion(MatrixXd& m, VectorXd& autovectorDominante, double autovalor);
vector<pair<double, VectorXd>> autovectores(MatrixXd m);
vector<pair<double, VectorXd>> autovectores(MatrixXd m, int k);

MatrixXd leerMatriz(string nombreArchivo);

void escribirAutoVectoresValores(MatrixXd m, string nombreArchivo);

