import matplotlib.pyplot as plt
import numpy as np

casos = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
m = [0, 8, 2, 3, 16, 8, 3, 32, 22, 12]  # Longitudes de s1
n = [0, 4, 10, 50, 10, 7, 3, 0, 8, 12]  # Longitudes de s2
TFuerzaBruta = [0.0009, 0.2948, 0.0387, 54.3038, 37692.0667, 0.3102, 0.0112, 0.0032, None, 17540.3667]
TProgDinamica = [0.0072, 0.0273, 0.0489, 0.0293, 0.0528, 0.0932, 0.0101, 0.0239, 0.0634, 0.0448]

fuerza_bruta = [133301, 133301, 133301, 133352, 133332, 133301, 133301, 133334, None, 133301]
prog_dinamica = [133342, 133726, 133558, 134477, 134541, 133846, 133486, 134271, 135748, 134350]


plt.figure(figsize=(10, 6))
plt.plot(casos, TFuerzaBruta, color='red', marker='o', label='Fuerza Bruta', linestyle='-', markersize=6)
plt.title('Costo de Transformación usando Fuerza Bruta')
plt.xlabel('Casos')
plt.ylabel('Costo de Transformación (Tiempo en segundos)')
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(casos, TProgDinamica, color='blue', marker='x', label='Programación Dinámica', linestyle='-', markersize=6)
plt.title('Costo de Transformación usando Programación Dinámica')
plt.xlabel('Casos')
plt.ylabel('Costo de Transformación (Tiempo en segundos)')
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(casos, TFuerzaBruta, color='red', marker='o', label='Fuerza Bruta', linestyle='-', markersize=6)
plt.plot(casos, TProgDinamica, color='blue', marker='x', label='Programación Dinámica', linestyle='-', markersize=6)
plt.title('Costo de Transformación para Fuerza Bruta vs Programación Dinámica')
plt.xlabel('Casos')
plt.ylabel('Costo de Transformación (Tiempo en segundos)')
plt.legend()
plt.grid(True)
plt.show()

casos_filtrados = [caso for caso, fb in zip(casos, TFuerzaBruta) if fb is not None]
TFuerzaBruta_filtrados = [fb for fb in TFuerzaBruta if fb is not None]
TProgDinamica_filtrados = [td for td, fb in zip(TProgDinamica, TFuerzaBruta) if fb is not None]
plt.figure(figsize=(10, 6))
plt.scatter(casos_filtrados, TFuerzaBruta_filtrados, color='red', label='Fuerza Bruta', marker='o', s=100)
plt.scatter(casos_filtrados, TProgDinamica_filtrados, color='blue', label='Programación Dinámica', marker='x', s=100)
plt.title('Gráfico de Dispersión: Comparación de Tiempos de Transformación')
plt.xlabel('Casos')
plt.ylabel('Tiempo de Transformación (segundos)')
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(casos, fuerza_bruta, label="Fuerza Bruta", marker='o', color='b')
plt.plot(casos, prog_dinamica, label="ProgDinamica", marker='s', color='r')
plt.title("Comparación de Asignación de Memoria entre Fuerza Bruta y ProgDinamica")
plt.xlabel("Casos")
plt.ylabel("Bytes")
plt.legend()
plt.grid(True)
plt.show()
