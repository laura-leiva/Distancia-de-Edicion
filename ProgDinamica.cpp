#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <chrono> 

using namespace std;

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

vector<vector<int>> costo_sustitucion;  
vector<int> costo_insercion; 
vector<int> costo_eliminacion; 
vector<vector<int>> costo_transposicion;

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

int distancia_edicion(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int substitution_cost = dp[i-1][j-1] + costo_sub(s1[i-1], s2[j-1]);
            int insertion_cost = dp[i][j-1] + costo_ins(s2[j-1]);
            int deletion_cost = dp[i-1][j] + costo_del(s1[i-1]);
            dp[i][j] = min({substitution_cost, insertion_cost, deletion_cost});
        if (i > 1 && j > 1 && s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1]) {
            int transposition_cost = dp[i-2][j-2] + costo_trans(s1[i-1], s2[j-1]);
            dp[i][j] = min(dp[i][j], transposition_cost);
        }
        }
    }
    return dp[m][n];
}

void leer_cadenas(const string& filename, string& cadena1, string& cadena2) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    std::getline(file, cadena1); 
    std::getline(file, cadena2);  
    file.close();
}

void createFile(const string& cadena1, const string& cadena2, const string& filename, int costo, double tiempo) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al crear el archivo: " << filename << std::endl;
        return;
    }
    file << "Distancia entre '" << cadena1 << "' y '" << cadena2 << "': " << costo << std::endl;
    file << "Tamaño de cadena1: " << cadena1.length() << std::endl;
    file << "Tamaño de cadena2: " << cadena2.length() << std::endl;
    file << "Tiempo de ejecución: " << tiempo << " ms" << std::endl;
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
    int costo = distancia_edicion(cadena1, cadena2);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;
    string output_filename = "programacion_dinamica.txt"; 
    createFile(cadena1, cadena2, output_filename, costo, duracion.count());
    
    return 0;
}
