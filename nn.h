#pragma once
#include "linalg.h"
#include <vector>
#include <tuple>

class NeuralNetwork {
private:
	std::vector<Matrix> W;
	std::vector<Vector> B;
	std::vector<int> layerSize;
	double alpha; //learing rate
public:
	NeuralNetwork(int layers, ...);
	NeuralNetwork(std::vector<int> layers);
	~NeuralNetwork();

	int inputSize();
	int outputSize();
	int hiddenLayerCount();
	int getLayerSize(int l);
	double learningRate();
	double learningRate(double d);
	

	//returns the average cost for this batch
	//passed, tested, cost
	std::tuple<int, int, Vector> trainBatch(const std::vector<std::pair<Vector, Vector>>& batch);

	//runs the argument through the network
	Vector operator()(const Vector& inputVector);

	//serialization

};
