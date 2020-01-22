#pragma once
#include "linalg.h"
#include <vector>

class NeuralNetwork {
private:
	std::vector<Matrix> weights;
	std::vector<Matrix> dw;
	std::vector<Vector> biases;
	std::vector<Vector> db;
	int layers;
	std::vector<int> layerSize;
public:
	NeuralNetwork();
	~NeuralNetwork();

	//setup
	//testing
	//serialization
};
