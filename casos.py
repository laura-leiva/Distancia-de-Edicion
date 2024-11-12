import random
from datetime import datetime

def guardar_cadenas_en_txt(nombre_archivo, cadena1, cadena2):
    with open(nombre_archivo, "w") as archivo:
        archivo.write(f"{cadena1}\n")
        archivo.write(f"{cadena2}\n")

def generar_cadenas_aleatorias():
    longitud_cadena1 = random.randint(1, 250) 
    longitud_cadena2 = random.randint(1, 250) 
    
    cadena1 = ''.join(random.choices("abcdefghijklmnopqrstuvwxyz", k=longitud_cadena1))
    cadena2 = ''.join(random.choices("abcdefghijklmnopqrstuvwxyz", k=longitud_cadena2))
    
    return cadena1, cadena2

cadena1, cadena2 = generar_cadenas_aleatorias()
nombre_archivo = f"caso.txt"

guardar_cadenas_en_txt(nombre_archivo, cadena1, cadena2)
