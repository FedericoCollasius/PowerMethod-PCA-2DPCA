import cv2
import numpy as np
import os


#ruta = "Desktop\Facultad\TPs\PCA\ImagenesCaras"
ruta = ""

S = []

for personas in os.listdir(ruta):
    ruta_carpeta_persona = os.path.join(ruta, personas)

    persona = []

    for nombre_imagen in os.listdir(ruta_carpeta_persona):
        ruta_imagen = os.path.join(ruta_carpeta_persona, nombre_imagen)

        imagen = cv2.imread(ruta_imagen, cv2.IMREAD_GRAYSCALE)

        persona.append(imagen) 

    matriz_persona = np.array(persona)

    S.append(matriz_persona)

