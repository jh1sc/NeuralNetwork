#ifndef MATRIX_H
#define MATRIX_H
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <functional>




class Matrix {
private:
	std::vector<std::vector<double>> data;
	int rows, cols;

public:


	Matrix();  // Declaration for the default constructor
	Matrix(int rows, int cols);
	Matrix(std::initializer_list<std::initializer_list<double>> list);

	void resize(int newRows, int newCols) {
		data.resize(newRows, std::vector<double>(newCols, 0.0));
		rows = newRows;
		cols = newCols;
	}
	static Matrix getRow(const Matrix& matrix, int row) {
		if (row < 0 || row >= matrix.rows) {
			std::cout << "Invalid row index." << std::endl;
			return Matrix();  // Return an empty matrix or handle the error appropriately
		}

		Matrix rowMatrix(1, matrix.cols);  // Assuming your Matrix constructor takes rows and cols
		rowMatrix.data[0] = matrix.data[row];

		return rowMatrix;
	}
	int getRows() const { return rows; }
	int getCols() const { return cols; }

	void setRandomfloat(double min, double max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(min, max);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				data[i][j] = dis(gen);
			}
		}
	}
	static Matrix hadamardProduct(const Matrix& matrixA, const Matrix& matrixB) {
		// Check if the dimensions are compatible
		if (matrixA.rows != matrixB.rows || matrixA.cols != matrixB.cols) {
			std::cout << "Matrix dimensions are not compatible for Hadamard product\n";
		}

		Matrix result(matrixA.rows, matrixA.cols);
		for (int i = 0; i < matrixA.rows; ++i) {
			for (int j = 0; j < matrixA.cols; ++j) {
				result.setValue(i, j, (matrixA.getValue(i, j) * matrixB.getValue(i, j)));
			}
		}

		return result;
	}

	void setRandomint(double min, double max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(min, max);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				data[i][j] = (int)dis(gen);
			}
		}
	}
	void setall(int n) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				data[i][j] = n;
			}
		}
	}
	double getValue(int row, int col) const {
		if (row < 0 || row >= rows || col < 0 || col >= cols) {
			std::cout << "getValue | Index out of bounds :" << row << "," << col << " | Matrix Dimesions: " << rows << "," << cols << std::endl;

			std::cout << "Index out of bounds\n";
		}
		return data[row][col];
	}

	void setValue(int row, int col, double value) {
		if (row >= 0 && row < rows && col >= 0 && col < cols) {
			data[row][col] = value;
		}
		else {
			std::cout << "setValue | Index out of bounds. Value not set." << std::endl;
		}
	}

	static Matrix multiply(const Matrix& m1, const Matrix& m2) {
		int m1Rows = m1.getRows();
		int m1Cols = m1.getCols();
		int m2Rows = m2.getRows();
		int m2Cols = m2.getCols();

		if (m1Cols != m2Rows) {
			std::cout << "Matrix dimensions are not compatible for multiplication\n";
			Matrix::print(m1);
			Matrix::print(m2);

		}

		Matrix result(m1Rows, m2Cols);

		for (int i = 0; i < m1Rows; ++i) {
			for (int j = 0; j < m2Cols; ++j) {
				double sum = 0.0;
				for (int k = 0; k < m1Cols; ++k) {
					sum += m1.getValue(i, k) * m2.getValue(k, j);
				}
				result.setValue(i, j, sum);
			}
		}

		return result;
	}
	static Matrix add(const Matrix& m1, const Matrix& m2) {
		int rows1 = m1.getRows();
		int cols1 = m1.getCols();
		int rows2 = m2.getRows();
		int cols2 = m2.getCols();

		if (rows1 != rows2 || cols1 != cols2) {
			std::cout << "\nError: Incompatible matrices for addition." << std::endl;
			std::cout << "Matrix 1: " << rows1 << "x" << cols1 << std::endl;
			std::cout << "Matrix 2: " << rows2 << "x" << cols2 << std::endl;
			return Matrix(0, 0);
		}

		Matrix result(rows1, cols1);

		for (int i = 0; i < rows1; ++i) {
			for (int j = 0; j < cols1; ++j) {
				result.setValue(i, j, m1.getValue(i, j) + m2.getValue(i, j));
			}
		}

		return result;
	}
	static Matrix subtract(const Matrix& m1, const Matrix& m2) {
		int rows1 = m1.getRows();
		int cols1 = m1.getCols();
		int rows2 = m2.getRows();
		int cols2 = m2.getCols();

		// Check if matrices have the same dimensions
		if (rows1 != rows2 || cols1 != cols2) {
			std::cout << "\nError: Incompatible matrices for subtractions." << std::endl;
			std::cout << "Matrix 1: " << rows1 << "x" << cols1 << std::endl;
			std::cout << "Matrix 2: " << rows2 << "x" << cols2 << std::endl;
			return Matrix(0, 0);
		}

		Matrix result(rows1, cols1);

		for (int i = 0; i < rows1; ++i) {
			for (int j = 0; j < cols1; ++j) {
				result.setValue(i, j, m1.getValue(i, j) - m2.getValue(i, j));
			}
		}

		return result;
	}
	static Matrix apply(std::function<double(double)> func, const Matrix& m) {
		int rows = m.getRows();
		int cols = m.getCols();

		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.setValue(i, j, func(m.getValue(i, j)));
			}
		}

		return result;
	}
	static Matrix scale(const Matrix& m,double n) {
		int rows = m.getRows();
		int cols = m.getCols();

		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.setValue(i, j, n * m.getValue(i, j));
			}
		}

		return result;
	}
	static Matrix addScalar(const Matrix& m, double n) {
		int rows = m.getRows();
		int cols = m.getCols();

		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.setValue(i, j, n + m.getValue(i, j));
			}
		}

		return result;
	}
	static Matrix subScalar(double n, const Matrix& m) {
		int rows = m.getRows();
		int cols = m.getCols();

		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.setValue(i, j, n - m.getValue(i, j));
			}
		}

		return result;
	}

	static Matrix transpose(const Matrix& input) {
		Matrix result(input.getCols(), input.getRows());
		for (int i = 0; i < input.getRows(); ++i) {
			for (int j = 0; j < input.getCols(); ++j) {
				result.setValue(j, i, input.getValue(i, j));
			}
		}

		return result;
	}
	static Matrix softmax(const Matrix& m) {
		int rows = m.getRows();
		int cols = m.getCols();

		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			double total = 0.0;
			for (int j = 0; j < cols; ++j) {
				total += std::exp(m.getValue(i, j));
			}
			for (int j = 0; j < cols; ++j) {
				result.setValue(i, j, std::exp(m.getValue(i, j)) / total);
			}
		}

		return result;
	}
	static Matrix softmaxPrime(const Matrix& input) {
		int rows = input.getRows();
		int cols = input.getCols();
		Matrix result(rows, cols);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				double s = std::exp(input.getValue(i, j));
				result.setValue(i, j, s / (std::pow(s + 1.0, 2)));
			}
		}

		return result;
	}
	static Matrix flatten(const Matrix& input, int axis) {
		int rows = input.getRows();
		int cols = input.getCols();

		if (axis == 0) { // Flatten along rows
			Matrix flattened(1, rows * cols);

			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					flattened.setValue(0, i * cols + j, input.getValue(i, j));
				}
			}

			return flattened;
		}
		else if (axis == 1) { // Flatten along columns
			Matrix flattened(rows * cols, 1);

			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					flattened.setValue(i * cols + j, 0, input.getValue(i, j));
				}
			}

			return flattened;
		}
		else {
			std::cout << "Invalid axis. Please use 0 for flattening along rows or 1 for flattening along columns." << std::endl;
			return Matrix(0, 0);
		}
	}
	static void print(const Matrix& matrix) {
		std::cout << "Dimensions: " << matrix.getRows() << "x" << matrix.getCols() << std::endl;
		for (int i = 0; i < matrix.rows; ++i) {
			for (int j = 0; j < matrix.cols; ++j) {
				std::cout << matrix.data[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}
	static void printb(const Matrix& matrix) {
		std::cout << '\n';
		for (int i = 0; i < matrix.rows; ++i) {
			for (int j = 0; j < matrix.cols; ++j) {
				std::cout << matrix.data[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}
	int matrix_argmax() const {
		if (rows == 0 || cols == 0) {
			std::cout << "Empty matrix. Cannot find argmax." << std::endl;
			return -1; // or some default value indicating an error
		}

		double maxVal = std::numeric_limits<double>::lowest();
		int argmaxRow = -1, argmaxCol = -1;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (data[i][j] > maxVal) {
					maxVal = data[i][j];
					argmaxRow = i;
					argmaxCol = j;
				}
			}
		}

		std::cout << "Argmax value: " << maxVal << " at position (" << argmaxRow << ", " << argmaxCol << ")" << std::endl;

		return argmaxCol; // Assuming you want to return the column index of the argmax value
	}


};
#endif // MATRIX_H