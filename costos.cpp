#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

void createCostFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al crear el archivo: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        file << "1 "; 
    }
    file << std::endl;
    file.close();
}

void createReplaceCostFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al crear el archivo: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i == j) {
                file << "0 ";
            } else {
                file << "2 ";
            }
        }
        file << std::endl;
    }
    file.close();
}

void createTransposeCostFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al crear el archivo: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i == j) {
                file << "0 ";
            } else {
                file << "1 ";
            }
        }
        file << std::endl; 
    }
    file.close();
}

int main() {
    createCostFile("cost_insert.txt");
    createCostFile("cost_delete.txt");
    createReplaceCostFile("cost_replace.txt");
    createTransposeCostFile("cost_transpose.txt");
    return 0;
}
