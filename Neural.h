#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <cmath>
#include "Matrix.h"



class NeuralNetwork {
public:
    NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes, float learningRate)
        : inputNodes(inputNodes), hiddenNodes(hiddenNodes), outputNodes(outputNodes), learningRate(learningRate) {
        // Initialize matrices and other variables
        Matrix hiddenWeights(hiddenNodes, inputNodes);
        Matrix outputWeights(outputNodes, hiddenNodes);
        Matrix hiddenBias(hiddenNodes, 1);
        Matrix outputBias(outputNodes, 1);

        
    }
    

    double sigmoid(double x) {
        return 1.0 / (1 + std::exp(-x));
    }

    double sigmoidPrime(double x) {
        return sigmoid(x) * (1 - sigmoid(x));
    }

    void train(const Matrix& inputData, const Matrix& targetData, int numEpochs) {
        for (int epoch = 0; epoch < numEpochs; ++epoch) {
            for (int i = 0; i < inputData.getRows(); ++i) {
                hiddenWeights = Matrix::setRandomfloat(-1.0, 1.0);
                outputWeights = Matrix::setRandomfloat(-1.0, 1.0);
                hiddenBias = Matrix::setRandomfloat(-1.0, 1.0);
                outputBias = Matrix::setRandomfloat(-1.0, 1.0);

                // Forward propagation
                Matrix inputVector = Matrix::transpose(Matrix::getRow(inputData, i));
                Matrix targetVector = Matrix::getRow(targetData, i);

                Matrix hiddenWeightedSum = Matrix::add(Matrix::multiply(hiddenWeights, inputVector), hiddenBias);
                Matrix hiddenActivation = Matrix::apply(sigmoid, hiddenWeightedSum);
                Matrix outputWeightedSum = Matrix::add(Matrix::multiply(outputWeights, hiddenActivation), outputBias);
                Matrix outputActivation = Matrix::apply(sigmoid, outputWeightedSum);

                // Calculate error
                Matrix error = Matrix::subtract(targetVector, outputActivation);

                // Backpropagation
                Matrix outputDelta = Matrix::hadamardProduct(error, Matrix::apply(sigmoidPrime, outputWeightedSum));
                Matrix hiddenError = Matrix::multiply(Matrix::transpose(outputWeights), outputDelta);
                Matrix hiddenDelta = Matrix::hadamardProduct(hiddenError, Matrix::apply(sigmoidPrime, hiddenWeightedSum));

                // Update weights
                outputWeights = Matrix::add(outputWeights, Matrix::multiply(Matrix::scale(outputDelta, learningRate), Matrix::transpose(hiddenActivation)));
                hiddenWeights = Matrix::add(hiddenWeights, Matrix::multiply(Matrix::scale(hiddenDelta, learningRate), Matrix::transpose(inputVector)));

                // Update biases
                hiddenBias = Matrix::add(hiddenBias, Matrix::scale(hiddenDelta, learningRate));
                outputBias = Matrix::add(outputBias, Matrix::scale(outputDelta, learningRate));
            }
        }
    }

    void predict(const Matrix& inputData, const Matrix& targetData) {
        for (int i = 0; i < inputData.getRows(); ++i) {
            // Forward propagation to get prediction
            Matrix inputVector = Matrix::transpose(Matrix::getRow(inputData, i));
            Matrix targetVector = Matrix::getRow(targetData, i);

            Matrix hiddenWeightedSum = Matrix::add(Matrix::multiply(hiddenWeights, inputVector), hiddenBias);
            Matrix hiddenActivation = Matrix::apply(sigmoid, hiddenWeightedSum);
            Matrix outputWeightedSum = Matrix::add(Matrix::multiply(outputWeights, hiddenActivation), outputBias);
            Matrix outputActivation = Matrix::apply(sigmoid, outputWeightedSum);

            std::cout << "Input: ";
            Matrix::print(inputVector);
            std::cout << "Actual Output: ";
            Matrix::print(targetVector);
            std::cout << "Predicted Output: ";
            Matrix::print(outputActivation);
            std::cout << "\n";
        }
    }

private:
    int inputNodes;
    int hiddenNodes;
    int outputNodes;
    float learningRate;

    Matrix hiddenWeights;
    Matrix outputWeights;
    Matrix hiddenBias;
    Matrix outputBias;
};
