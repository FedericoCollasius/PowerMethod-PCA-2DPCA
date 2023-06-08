#include "./expPotencia.h"

vector<int> crearVector(int start, int end, int step=1) {
    vector<int> res;
    for (int i = start; i < end; i += step) {
        res.push_back(i);
    }

    return res;
}

void errorPorIteraciones(MatrixXd& m, double autovalorDominante, string nombreArchivo, int cantIter) {
    vector<int> cantidadIteraciones = crearVector(1, cantIter, 1);
    int cantidadRepeticiones = 100;

    ofstream archivoResultados(".\\analisis\\datosComportamiento\\potencia\\" + nombreArchivo + ".csv");

    cout << "Corriendo el test: " << nombreArchivo << endl;
    
    if (!archivoResultados.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    vector<VectorXd> cis;
    for (int i = 0; i < cantidadRepeticiones; i++) {
        cis.push_back(VectorXd::Random(m.rows()));
    }

    for (const int &cantidad: cantidadIteraciones) {
        archivoResultados << cantidad << "," ;

        for (int i = 0; i < cantidadRepeticiones; i++) {
            double autovalor = autovectorDominanteIteraciones(m, cantidad, cis[i]).first;
            double error = abs(autovalor - autovalorDominante);
            
            archivoResultados << error;

            if (i != cantidadRepeticiones - 1) archivoResultados << ",";
        }

        archivoResultados << "\n";
    }
}

void correrTestsIteraciones() {
    // Tiene un 5 y un 1 en el resto de la diagonal
    MatrixXd mEficiente = MatrixXd::Identity(10, 10);
    mEficiente(0, 0) = 5;

    errorPorIteraciones(mEficiente, 5, "DominanteMuyDistintoIteraciones", 50);

    // Tiene un 1.1 y un 1 en el resto de la diagonal
    MatrixXd mPeor = MatrixXd::Identity(10, 10);
    mPeor(0, 0) = 1.01;

    errorPorIteraciones(mPeor, 1.01, "TodosParecidosIteraciones", 1000);

    // Solo los primeros dos son parecidos
    MatrixXd mMala = MatrixXd::Identity(10, 10);
    mMala(0, 0) = 2;
    mMala(0, 0) = 2.01;

    errorPorIteraciones(mMala, 2.01, "DosParecidosIteraciones", 700);

    // No converge seguramente pero es diagonalizable
    MatrixXd mNoConverge = MatrixXd::Zero(10, 10);
    mNoConverge(0, 0) = 2;
    mNoConverge(1, 1) = 2;
    mNoConverge(2, 2) = 2;

    errorPorIteraciones(mNoConverge, 2, "NoConvergeIteraciones", 200);
}

void correrTestsTiempo() {
    // Estudia el tiempo en funcion del tamanio de la matriz
    vector<int> tamanios = {5, 50, 500, 2000, 5000};

    int cantidadIteraciones = 100;

    ofstream archivoTiempoTamanio(".\\analisis\\datosComportamiento\\potencia\\TiempoTamanio100Tam.csv");

    cout << "Corriendo tests de tiempo en funcion del tamanio!" << endl;

    for (const int& n: tamanios) {
        cout << n << endl;

        archivoTiempoTamanio << n << ",";

        // Creo una matriz generica que se que converge
        MatrixXd m = MatrixXd::Identity(n, n);
        m(0, 0) = 2;

        // Calcula el tiempo 20 veces
        for (int i = 0; i < 20; i++) {
            auto start = chrono::high_resolution_clock::now();

            autovectorDominanteIteraciones(m, 100);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            archivoTiempoTamanio << elapsed.count();
            
            if (i != 19) archivoTiempoTamanio << ",";
        }

        archivoTiempoTamanio << "\n";
    }

    // Estudia el tiempo en funcion de la cantidad de iteraciones
    vector<int> iteracoines = {5, 50, 500, 2000, 5000};

    ofstream archivoTiempoIteraciones(".\\analisis\\datosComportamiento\\potencia\\TiempoTamanio100iter.csv");

    MatrixXd m = MatrixXd::Identity(100, 100);
    m(0, 0) = 2;

    cout << "Corriendo tests de tiempo en funcion de las iteraciones!" << endl;

    for (const int& n: iteracoines) {
        cout << n << endl;

        archivoTiempoIteraciones << n << ",";

        // Calcula el tiempo 20 veces
        for (int i = 0; i < 20; i++) {
            auto start = chrono::high_resolution_clock::now();

            autovectorDominanteIteraciones(m, n);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            archivoTiempoIteraciones << elapsed.count();

            if (i != 19) archivoTiempoIteraciones << ",";
        }

        archivoTiempoIteraciones << "\n";
    }
}