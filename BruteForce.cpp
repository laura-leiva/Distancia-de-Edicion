#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

vector<vector<int>> costo_sustitucion;
vector<int> costo_insercion;
vector<int> costo_eliminacion;
vector<vector<int>> costo_transposicion;

vector<vector<int>> leer_matriz(const string& filename, int rows, int cols) {
    vector<vector<int>> matriz(rows, vector<int>(cols));
    ifstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return matriz;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matriz[i][j];
            if (file.fail()) {
                cerr << "Error al leer el valor en [" << i << "][" << j << "] del archivo: " << filename << endl;
            }
        }
    }
    file.close();
    return matriz;
}

void cargar_costos() {
    costo_sustitucion = leer_matriz("cost_replace.txt", 26, 26);
    costo_insercion = leer_matriz("cost_insert.txt", 1, 26)[0];
    costo_eliminacion = leer_matriz("cost_delete.txt", 1, 26)[0];
    costo_transposicion = leer_matriz("cost_transpose.txt", 26, 26);
}

int costo_sub(char a, char b) {
    return costo_sustitucion[a - 'a'][b - 'a'];
}
int costo_ins(char b) {
    return costo_insercion[b - 'a'];
}
int costo_del(char a) {
    return costo_eliminacion[a - 'a'];
}
int costo_trans(char a, char b) {
    return costo_transposicion[a - 'a'][b - 'a'];
}

int distancia_edicion(const string& s1, const string& s2, int i, int j) {
    if (i == s1.length() && j == s2.length()) return 0;
    if (i == s1.length()) return costo_ins(s2[j]) + distancia_edicion(s1, s2, i, j + 1);
    if (j == s2.length()) return costo_del(s1[i]) + distancia_edicion(s1, s2, i + 1, j);
    int costo_minimo = INT_MAX;
    int costo_sustitucion = costo_sub(s1[i], s2[j]) + distancia_edicion(s1, s2, i + 1, j + 1);
    costo_minimo = min(costo_minimo, costo_sustitucion);
    int costo_insercion = costo_ins(s2[j]) + distancia_edicion(s1, s2, i, j + 1);
    costo_minimo = min(costo_minimo, costo_insercion);
    int costo_eliminacion = costo_del(s1[i]) + distancia_edicion(s1, s2, i + 1, j);
    costo_minimo = min(costo_minimo, costo_eliminacion);
    if (i + 1 < s1.length() && j + 1 < s2.length() && s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
        int costo_transposicion = costo_trans(s1[i], s1[i + 1]) + distancia_edicion(s1, s2, i + 2, j + 2);
        costo_minimo = min(costo_minimo, costo_transposicion);
    }

    return costo_minimo;
}

void leer_cadenas(const string& filename, string& cadena1, string& cadena2) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }
    getline(file, cadena1);
    getline(file, cadena2);
    file.close();
}

void createFile(const string& cadena1, const string& cadena2, const string& filename, int costo, double tiempo) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error al crear el archivo: " << filename << endl;
        return;
    }
    file << "Distancia entre '" << cadena1 << "' y '" << cadena2 << "': " << costo << endl;
    file << "Tamaño de cadena1: " << cadena1.length() << endl;
    file << "Tamaño de cadena2: " << cadena2.length() << endl;
    file << "Tiempo de ejecución: " << tiempo << " ms" << endl;
    file.close();
}

int main() {
    cargar_costos();
    string cadena1, cadena2;
    string caso;
    cin >> caso;
    string input_filename = caso;
    leer_cadenas(input_filename, cadena1, cadena2);
    
    auto inicio = chrono::high_resolution_clock::now();
    int costo = distancia_edicion(cadena1, cadena2, 0, 0);
    auto fin = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> duracion = fin - inicio;
    string output_filename = "fuerza_bruta.txt";
    createFile(cadena1, cadena2, output_filename, costo, duracion.count());
    
    return 0;
}
