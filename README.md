# TP-autovectores

Se corre las funciones implementadas en c++ con el comando "make" desde linux

Los algoritmos del 1) estan implementados en include/calculoAutovectores
    - autovectorDominanteIteraciones(m, k, ci) corre el metodo de la potencia version naive para una ci dada. Puede removerse y consigue una ci con eigen

    - autovectorDominanteThreshold(m, threshold) corre el metodo de la potencia mejorado

    - autovectores(m) calcula todos los autovectores y valores de la matriz m, y printea cuando algunas sucesiones no convergieron.


Los codigos para testear el 1) estan implementados en analisis/generacionDatos
    Tests de potencia en expPotencia:

    - correrTestsIteraciones()
    - correrTestsTiempo()

    Tests de autovectores en expAutovectores:

    - testsTiempoComputo(nombreArchivo)
    - testsFiabilidad(nombreArchivo)

El analisis esta hecho en el jupternotebook de analisis_potencia


En 2) se tienen las funciones para construir las matrices de covarianza de pca y 2dpca en fucntions.py, las cuales se les calcula los autovectores que se guardan en archivos en data. No esta en el repo al pesar mas de 1gb, pero se puede descargar de: https://drive.google.com/drive/folders/1Wt7JHbhtO62ZlSM-w5NgBaPkZT-I0GJ5?usp=sharing

Todas las funciones del 2) estan en los jupyter notebook de 2dpca y pca en ./analisis/

Las funciones del 3) estan en analisis_ej3.ipynb y analisis_similaridad_2dpca y analisis_similaridad_pca. 
