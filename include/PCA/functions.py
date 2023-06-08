import numpy as np
from pathlib import Path
import matplotlib.pyplot as plt

def covariance_matrix(X):
    #X = X - np.mean(X, axis=0)
    n = X.shape[0]
    return (X.T @ X) / (n - 1)

def correlation_matrix(C):
    # Return Cij = Cij / sqrt(Cii*Cjj)
    D = np.zeros(C.shape)
    for i in range(C.shape[0]):
        for j in range(C.shape[1]):
            D[i,j] += C[i,j] / np.sqrt(C[i,i] * C[j,j])
    return D

def write_matrix_to_file(matrix, filename):
    with open(filename, 'w') as f:
        for row in matrix:
            for value in row:
                f.write(f'{value} ')
            f.write('\n')

def read_eigenvalues_vectors_from_file(filename):
    #file contains in first line the eigenvalues and in the next lines the eigenvectors
    #one eigenvector per line, after second line onwards
    with open(filename, 'r') as f:
        lines = f.readlines()
        #print line 0
        print(lines[0])
        eigenvalues = np.array([float(value) for value in lines[0].split(' ')])
        eigenvectors = np.array([[float(value) for value in line.split(' ')] for line in lines[1:]])
    return eigenvalues, eigenvectors

def PCA(X, k):
    X = X - np.mean(X, axis=0)
    cov = covariance_matrix(X)
    
    #load eigenvalues and eigenvectors from file
    eigenvalues, eigenvectors = read_eigenvalues_vectors_from_file('data/componentes/autovectores_pca.csv')
    
    # Ordenar los autovectores en función de los autovalores
    eigenvectors = eigenvectors.T
    idxs = np.argsort(eigenvalues)[::-1]
    eigenvalues = eigenvalues[idxs]
    eigenvectors = eigenvectors[idxs]

    components = eigenvectors[0:k]
    return np.dot(X, components.T), eigenvalues, components

def crearG(X):
    mean = np.mean(X, axis=0)
    G = np.zeros((X.shape[2], X.shape[2]))
    for i in range(X.shape[0]):
        G += np.dot((X[i] - mean).T, (X[i] - mean))
        G /= X.shape[0]

    np.savetxt('data/matrices_cov/cov_matrix_G.txt', G, delimiter=' ')
    return G

def TwoDPCA(X, k):
    G = crearG(X)

    #eigenvalues, eigenvectors = np.linalg.eig(G)
    #Obtengo los autovalores y autovectores de G con Eigen, preocomputados    
    eigenvalues, eigenvectors = read_eigenvalues_vectors_from_file('data/componentes/autovectores_2dpca.csv')

    # Ordenar los autovectores en función de los autovalores
    eigenvectors = eigenvectors.T
    idxs = np.argsort(eigenvalues)[::-1]
    eigenvalues = eigenvalues[idxs]
    eigenvectors = eigenvectors[idxs]

    components = eigenvectors[0:k]
    return np.dot(X, components.T), eigenvalues, components

def return_dataset():
    paths = []
    imgs = []
    for path in sorted(list(Path('data/caras').rglob('/.pgm'))):
        print(path)
        paths.append(path)
        imgs.append(plt.imread(path) / 255)    #flatten images
    #imgs = [img.flatten() for img in imgs]
    imgs = np.array(imgs)
    #imgs es un array de 400 imagenes de 56*46
    return imgs

def construir_Matrices_Covarianza():
    imgs = return_dataset()
    X = np.stack(imgs)
    
    muestras = [img.flatten() for img in X]
    muestras = np.array(muestras)
    
    muestras = muestras - np.mean(muestras, axis=0)
    cov_matrix = covariance_matrix(muestras)     
    np.savetxt('data/matrices_cov/cov_matrix.txt', cov_matrix, delimiter=' ')
    
    #G = 1/n * sumatoria(Xi - Xmean)(Xi - Xmean).T 
    #Donde Xi es una imagen, Xmean es el promedio de todas las imagenes y n es la cantidad de imagenes 
    G = crearG(X)
    np.savetxt('data/matrices_cov/cov_matrix_G.txt', G, delimiter=' ')    
    return G, cov_matrix

if __name__ == "__main__":
    construir_Matrices_Covarianza()
    imgs = return_dataset()
    X = np.stack(imgs)
    #print current path
    
    muestras = [img.flatten() for img in X]
    muestras = np.array(muestras)

    #x_pca_low_k = PCA(muestras, 10)
    #x_2dpca_low_k = TwoDPCA(muestras, 10)
    