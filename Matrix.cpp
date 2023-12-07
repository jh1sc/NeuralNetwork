#include "Matrix.h"

Matrix::Matrix() : rows(0), cols(0) {
 
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    // Implementation for the parameterized constructor
    data.resize(rows, std::vector<double>(cols, 0.0));
}


Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) {
    int rows = list.size();
    int cols = (*list.begin()).size();

    // Resize the matrix
    resize(rows, cols);

    // Copy data from the initializer list to the matrix
    int i = 0;
    for (auto& row : list) {
        int j = 0;
        for (auto& val : row) {
            data[i][j] = val;
            ++j;
        }
        ++i;
    }
}