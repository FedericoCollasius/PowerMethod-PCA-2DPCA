#include "./expAutovectores.h"

// Genera una matriz simetrica de coordenadas sampleadas de una uniforme (1, 1)
MatrixXd matrizSimetricaRandom(int dimension) {
    srand((unsigned int) time(0));
    Eigen::initParallel();
    MatrixXd m = MatrixXd::Random(dimension, dimension);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < i; j++) {
            m(i, j) = m(j, i);
        }
    }

    return m;
}

void testsTiempoComputo(string nombreArchivo) {
    vector<float> tiempoComputo;

    ofstream archivo(".\\analisis\\datosComportamiento\\autovectores\\" + nombreArchivo + ".csv");

    int cantidadIteraciones = 1;
    for (int i = 0; i < cantidadIteraciones; i++) {

        cout << "consiguiendo autovectores..." << endl;

        MatrixXd matrizTesteo = matrizSimetricaRandom(10000);

        auto start = chrono::high_resolution_clock::now();

        autovectores(matrizTesteo, 10);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << elapsed.count() << endl;

        archivo << elapsed.count();

        if (i != cantidadIteraciones - 1) archivo << ",";
    }
}

void testsFiabilidad(string nombreArchivo) {
    vector<float> error;

    ofstream archivo(".\\analisis\\datosComportamiento\\autovectores\\" + nombreArchivo + ".csv");

    int cantidadIteraciones = 200;
    for (int i = 0; i < cantidadIteraciones; i++) {

        cout << "consiguiendo autovectores..." << endl;

        MatrixXd matrizTesteo = matrizSimetricaRandom(100);

        vector<pair<double, VectorXd>> resultadoNuestro = autovectores(matrizTesteo);
        VectorXd resultadoEigen = matrizTesteo.eigenvalues().real();
        
        VectorXd resNuestroAval(resultadoNuestro.size());

        for (int j = 0; j < resultadoNuestro.size(); j++) {
            resNuestroAval(j) = resultadoNuestro[j].first;
        }

        sort(resNuestroAval.data(), resNuestroAval.data() + resNuestroAval.size(), greater<double>());
        sort(resultadoEigen.data(), resultadoEigen.data() + resultadoEigen.size(), greater<double>());

        double error = (resNuestroAval - resultadoEigen).norm();

        cout << error << endl;

        archivo << error;

        if (i != cantidadIteraciones - 1) archivo << ",";
    }
}
