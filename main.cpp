// LLM.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <list>
#include "Tokenizer.h"
#include "Neural.h"
#include "Matrix.h"
#include <cmath>


double sigmoid(double x) { return 1.0 / (1 + std::exp(-x)); }
double sigmoidPrime(double x) { return sigmoid(x) * (1 - sigmoid(x)); }

int hiddennodes = 3;
int inputnodes = 2;
int outputnodes = 1;
int numEpochs = 10000;
float lr = 0.2;

Matrix hidden_weights(hiddennodes, inputnodes);
Matrix output_weights(outputnodes, hiddennodes);

Matrix hidden_bias(hiddennodes,1);
Matrix output_bias(outputnodes,1); 


Matrix input_data = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};

Matrix target_data = {
    {0},
    {1},
    {1},
    {0}
};

int main() {
    hidden_weights.setRandomfloat(-1.0, 1.0);
    output_weights.setRandomfloat(-1.0, 1.0);

    hidden_bias.setRandomfloat(-1.0, 1.0);
    output_bias.setRandomfloat(-1.0, 1.0);
    //Train(inputnodes, hiddennodes, outputnodes, lr, hidden_weights, output_weights, input_data, target_data, 10);


    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        for (int i = 0; i < input_data.getRows(); ++i) {

            Matrix inputVector = Matrix::transpose(Matrix::getRow(input_data, i));
            Matrix targetVector = Matrix::getRow(target_data, i);



            Matrix hiddenWeightedSum = Matrix::add(Matrix::multiply(hidden_weights, inputVector), hidden_bias);
            Matrix hiddenActivation = Matrix::apply(sigmoid, hiddenWeightedSum);
            Matrix outputWeightedSum = Matrix::add(Matrix::multiply(output_weights, hiddenActivation), output_bias);
            Matrix outputActivation = Matrix::apply(sigmoid, outputWeightedSum);

            // Calculate error
            Matrix error = Matrix::subtract(targetVector, outputActivation);

            // Backpropagation
            Matrix outputDelta = Matrix::hadamardProduct(error, Matrix::apply(sigmoidPrime, outputWeightedSum));
            Matrix hiddenError = Matrix::multiply(Matrix::transpose(output_weights), outputDelta);
            Matrix hiddenDelta = Matrix::hadamardProduct(hiddenError, Matrix::apply(sigmoidPrime, hiddenWeightedSum));

            // Update weights
            output_weights = Matrix::add(output_weights, Matrix::multiply(Matrix::scale(outputDelta, lr), Matrix::transpose(hiddenActivation)));
            hidden_weights = Matrix::add(hidden_weights, Matrix::multiply(Matrix::scale(hiddenDelta, lr), Matrix::transpose(inputVector)));

            // Update biases
            hidden_bias = Matrix::add(hidden_bias, Matrix::scale(hiddenDelta, lr));
            output_bias = Matrix::add(output_bias, Matrix::scale(outputDelta, lr));

        }
    }
    

    

    for (int i = 0; i < input_data.getRows(); ++i) {
        Matrix inputVector = Matrix::transpose(Matrix::getRow(input_data, i));
        Matrix targetVector = Matrix::getRow(target_data, i);

        // Forward propagation to get prediction
        Matrix hiddenWeightedSum = Matrix::add(Matrix::multiply(hidden_weights, inputVector), hidden_bias);
        Matrix hiddenActivation = Matrix::apply(sigmoid, hiddenWeightedSum);
        Matrix outputWeightedSum = Matrix::add(Matrix::multiply(output_weights, hiddenActivation), output_bias);
        Matrix outputActivation = Matrix::apply(sigmoid, outputWeightedSum);

        std::cout << "Input: ";
        Matrix::printb(inputVector);
        std::cout << "Actual Output: ";
        Matrix::printb(targetVector);
        std::cout << "Predicted Output: ";
        Matrix::printb(outputActivation);
        std::cout << "\n";
    }

    

    return 0;
}


