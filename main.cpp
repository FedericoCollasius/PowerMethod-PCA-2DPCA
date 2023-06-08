#include <iostream>
#include <Eigen/Dense>
#include "include/calculoAutovectores/calculoAutovectores.h"
#include "analisis/generacionDatos/expPotencia.h"
#include "analisis/generacionDatos/expAutovectores.h"
using namespace std;
using namespace Eigen;

// Experimentacion:

// - Para una matriz que cumpla podemos hacer un grafico de Error vs cant iteraciones con boxplots (siempre corre con distintas CI) y
//   ver como varia para distintas matrices en los distintos casos que converja y no, lo que motiva usar threshold.

// - A partir del resultado anterior graficamos boxplots del tiempo en funcion del taman(i)o y hacemos tiempo medio vs taman(i)o en escala logaritmica.
//   podemos plotear una recta en escala log y ver si el tiempo es cuadratico o como es.

// - Cuando hay threshold hacer Tiempo computo en funcion de la cantidad de condiciones iniciales. Concluir sobre una mejor forma.
//   Preguntar si hace falta esto a un profe.
//   Decidir en base al resultado de los boxplots.


void printAutovectores(vector<pair<double, VectorXd>> arrayAPrintear) {
    for (int i = 0; i < arrayAPrintear.size(); i++) {
        cout << "Autovalor: " << arrayAPrintear[i].first << ", Autovector: " << arrayAPrintear[i].second.transpose() << endl;
    }
}

int main() {   
    //testsTiempoComputo("tiempoAutovectores");
    //testsFiabilidad("errorAutovectores");

    //cout << matrizzSimetricaRandom(10).eigenvalues() << endl;

    //correrTestsIteraciones();
    //correrTestsTiempo();
    //testsTiempoComputo("archivoTest");

    //errorPorIteraciones(m, 2, "ArchivoTest");

    //vector<pair<double, VectorXd>> a = autovectores(m);
    //printAutovectores(a);

    cout << "leyendo matriz" << endl;
    //MatrixXd m = leerMatriz(".\\data\\matrices_cov\\cov_matrix_G.txt");
  
    MatrixXd A = leerMatriz("data/matrices_cov/cov_matrix.txt");
    MatrixXd m = leerMatriz("data/matrices_cov/cov_matrix_G.txt");  


    cout << "calculando autovectores" << endl;
    escribirAutoVectoresValores(m, "data/componentes/autovectores_2dpca.csv");
    escribirAutoVectoresValores(A, "data/componentes/autovalores_autovectores.txt");
    
    return 0;
}
