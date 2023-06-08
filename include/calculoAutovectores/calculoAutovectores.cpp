#include "./calculoAutovectores.h"

pair<double, VectorXd> autovectorDominanteIteraciones(MatrixXd& m, int nIter) {
    //cout << "Corriendo calculo de autovector y autovalor dominante" << endl;

    pair<double, VectorXd> res;  // <autovalor, autovector>

    VectorXd ci = VectorXd::Random(m.rows());
    ci.normalize();

    VectorXd valorSucesion = m * ci;  // S_0

    // Ejecuta nIter - 1 iteraciones
    for (int i = 1; i < nIter; i++) {
        valorSucesion = m * valorSucesion;
        valorSucesion.normalize();  // S_i = A^i x_0 / ||A^i x_0||
    }

    // v^t A v = lambda al estar v normalizado
    double autoValor = valorSucesion.transpose() * m * valorSucesion;

    return {autoValor, valorSucesion};
}

pair<double, VectorXd> autovectorDominanteIteraciones(MatrixXd& m, int nIter, VectorXd& ci) {
    pair<double, VectorXd> res;  // <autovalor, autovector>

    VectorXd valorSucesion = m * ci;  // S_0

    // Ejecuta nIter - 1 iteraciones
    for (int i = 1; i < nIter; i++) {
        valorSucesion = m * valorSucesion;
        valorSucesion.normalize();  // S_i = A^i x_0 / ||A^i x_0|| 
    }

    // v^t A v = lambda al estar v normalizado
    double autoValor = valorSucesion.transpose() * m * valorSucesion;

    return {autoValor, valorSucesion};
}

tuple<double, VectorXd, int> autovectorDominanteThreshold(MatrixXd& m, float threshold, int maxIter) {
    int intentos = 0;
    
    double ultAval;
    VectorXd valorSucesion;
    int iteraciones;

    while (intentos < 3) {
        VectorXd ci = VectorXd::Random(m.rows());
        ci.normalize();

        valorSucesion = m * ci;  // S_0

        iteraciones = 0;
        int cantElemsEnThreshold = 0;
        
        ultAval = valorSucesion.transpose() * m * valorSucesion;

        while(cantElemsEnThreshold < 40 && iteraciones < maxIter) {
            VectorXd producto = m * valorSucesion;  
            valorSucesion = producto / producto.norm();  // S_i = A^i x_0 / ||A^i x_0|| 
        
            double avalActual = valorSucesion.transpose() * m * valorSucesion;

            if (fabs(avalActual - ultAval) < threshold) {
                cantElemsEnThreshold++;
            }
            else {
                cantElemsEnThreshold = 0;
            }

            iteraciones++;
            ultAval = avalActual;
        }

        if (iteraciones == maxIter) {
            intentos++;
            cout << "Superado max iter, reintentando" << endl;
        }
        else {
            break;
        }
    }

    return {ultAval, valorSucesion, iteraciones};
}

tuple<double, VectorXd, int> autovectorDominanteThreshold(MatrixXd& m, float threshold) {
    int intentos = 0;
    
    float maxIter = m.rows() * m.rows() * m.rows() * 1000;
 
    double ultAval;
    VectorXd valorSucesion;
    int iteraciones;

    while (intentos < 5) {
        VectorXd ci = VectorXd::Random(m.rows());
        ci.normalize();

        valorSucesion = m * ci;  // S_0

        iteraciones = 0;
        int cantElemsEnThreshold = 0;
        
        ultAval = valorSucesion.transpose() * m * valorSucesion;

        while(cantElemsEnThreshold < 40 && iteraciones < maxIter) {
            VectorXd producto = m * valorSucesion;  
            valorSucesion = producto / producto.norm();  // S_i = A^i x_0 / ||A^i x_0|| 
        
            double avalActual = valorSucesion.transpose() * m * valorSucesion;

            if (fabs(avalActual - ultAval) < threshold) {
                cantElemsEnThreshold++;
            }
            else {
                cantElemsEnThreshold = 0;
            }

            iteraciones++;
            ultAval = avalActual;
        }

        if (iteraciones == maxIter) {
            intentos++;
            cout << "Superado max iter, reintentando" << endl;
        }
        else {
            break;
        }
    }

    return {ultAval, valorSucesion, iteraciones};
}

void deflacion(MatrixXd& m, VectorXd& autovectorDominante, double autovalor) {
    m -= autovalor * autovectorDominante * autovectorDominante.transpose();
}

vector<pair<double, VectorXd>> autovectores(MatrixXd m) {
    vector<pair<double, VectorXd>> res;

    for (int i = 0; i < m.rows(); i++) {
        cout << "Calculando el autovector " << i << endl;
        tuple<double, VectorXd, int> resIter = autovectorDominanteThreshold(m, 0.000000001);

        deflacion(m, get<1>(resIter), get<0>(resIter));
        res.push_back({get<0>(resIter), get<1>(resIter)});
    }

    return res;
}

vector<pair<double, VectorXd>> autovectores(MatrixXd m, int k) {
    vector<pair<double, VectorXd>> res;

    for (int i = 0; i < k; i++) {        
        tuple<double, VectorXd, int> resIter = autovectorDominanteThreshold(m, 0.000001);

        deflacion(m, get<1>(resIter), get<0>(resIter));
        res.push_back({get<0>(resIter), get<1>(resIter)});
    }

    return res;
}

MatrixXd leerMatriz(string pathArchivo){
    std::ifstream inFile;
    inFile.open(pathArchivo);
    
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo " << pathArchivo << std::endl;
        return Eigen::MatrixXd();
    }

    std::string line;
    std::vector<double> values;
    int rows = 0;
    int cols = 0;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        double value;
        int lineCols = 0;

        while (ss >> value) {
            values.push_back(value);
            lineCols++;
        }

        if (rows == 0) {
            cols = lineCols;
        }

        rows++;
    }

    return Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(values.data(), rows, cols);
}

void escribirAutoVectoresValores(MatrixXd m, string nombreArchivo) {
    vector<pair<double, VectorXd>> resultado = autovectores(m);

    ofstream file(nombreArchivo);

    for (int i = 0; i < resultado.size(); i++) {
        file << resultado[i].first << " ";
    }

    file << endl;
    for (int i = 0; i < resultado.size(); i++) {
        for (int j = 0; j < resultado[i].second.size(); j++) {
            file << resultado[i].second[j] << " ";
        }

        file << endl;
    }

    file.close();
}
