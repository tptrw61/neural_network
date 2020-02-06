#include "nn.h"
#include <stdarg.h>
#include <random>
#include <math.h>

static double sigmoid(double d) {
	return 1 / (1 + exp(-d));
}
static double sigmoidPrime(double d) {
	return sigmoid(d) * (1 - sigmoid(d));
}

//expected, actual
static double cost(double y, double a) {
	return -((y * log(a)) + ((1 - y) * log(1 - a)));
}

NeuralNetwork::NeuralNetwork(int layers, ...) {
	if (layers <= 3)
		throw;
	va_list args;
	va_start(args, layers);

	for (int i = 0; i < layers; i++) {
		layerSize.push_back(va_arg(args, int));
	}
	va_end(args);

	//boiler plate
	std::random_device rd{};
	std::mt19937 gen{rd()};
	std::normal_distribution<> d{0,1};
	//end of boiler plate
	auto nextd = [&gen, &d]() -> double { return d(gen); };
	//--
	for (int i = 1; i < (int)layerSize.size(); i++) {
		W.emplace_back(layerSize[i], layerSize[i-1]);
		B.emplace_back(layerSize[i]);
		for (int j = 0; j < W.back().M; j++)
			for (int k = 0; k < W.back().N; k++)
				W.back()(j, k) = nextd();
		for (int j = 0; j < B.back().N; j++)
			B.back()[j] = nextd();
	}
	//more...
}
NeuralNetwork::NeuralNetwork(std::vector<int> layers) {
	if (layers.size() <= 3)
		throw;

	layerSize = layers;

	//boiler plate
	std::random_device rd{};
	std::mt19937 gen{rd()};
	std::normal_distribution<> d{0,1};
	//end of boiler plate
	auto nextd = [&gen, &d]() -> double { return d(gen); };
	//--
	for (int i = 1; i < (int)layerSize.size(); i++) {
		W.emplace_back(layerSize[i], layerSize[i-1]);
		B.emplace_back(layerSize[i]);
		for (int j = 0; j < W.back().M; j++)
			for (int k = 0; k < W.back().N; k++)
				W.back()(j, k) = nextd();
		for (int j = 0; j < B.back().N; j++)
			B.back()[j] = nextd();
	}
}

NeuralNetwork::~NeuralNetwork() {

}

int NeuralNetwork::inputSize() {
	return layerSize.front();
}

int NeuralNetwork::outputSize() {
	return layerSize.back();
}

int NeuralNetwork::hiddenLayerCount() {
	return layerSize.size() - 2;
}

int NeuralNetwork::getLayerSize(int l) {
	if (l < 0 || l >= (int)layerSize.size())
		throw;
	return layerSize[l];
}

double NeuralNetwork::learningRate() {
	return alpha;
}

double NeuralNetwork::learningRate(double d) {
	double oldAlpha = alpha;
	alpha = d;
	return oldAlpha;
}

Vector NeuralNetwork::operator()(const Vector& inputVec) {
	if (inputVec.N != layerSize.front())
		return Vector();
	Vector v = inputVec;
	for (int i = 0; i < (int)W.size(); i++) {
		v = (W[i] * v) + B[i];
		v = v.applyFunc(sigmoid);
	}
	return v;
}

static Matrix outerProduct(const Vector& v, const Vector& u) {
	Matrix m(v.N, u.N);
	for (int i = 0; i < m.M; i++)
		for (int j = 0; j < m.N; j++)
			m(i, j) = v[i] * u[j];
	return m;
}

std::tuple<int, int, Vector> NeuralNetwork::trainBatch(const std::vector<std::pair<Vector, Vector>>& batch) {
	int tested = 0;
	int passed = 0;
	Vector costs(layerSize.back(), 0);
	VecFuncObj dzfunc([](double a, double b) -> double {
			return sigmoidPrime(a) * b;
		});
	//creating derivate matrices
	std::vector<Matrix> dW;
	std::vector<Vector> dB;
	std::vector<Vector> dz;
	for (int i = 1; i < (int)layerSize.size(); i++) {
		dW.emplace_back(layerSize[i], layerSize[i-1]);
		dB.emplace_back(layerSize[i]);
		dz.emplace_back(layerSize[i]);
	}
	for (int ix = 0; ix < (int)batch.size(); ix++) {
		//check dimentions of vectors
		Vector v = batch[ix].first;
		Vector expected = batch[ix].second;
		if (v.N != layerSize.front() || expected.N != layerSize.back())
			continue;
		else
			tested++;
		//forward prop saving activaions
		std::vector<Vector> a, z;
		for (int i = 0; i < (int)W.size(); i++) {
			v = (W[i] * v) + B[i];
			z.push_back(v);
			v = v.applyFunc(sigmoid);
			a.push_back(v);
		}
		//compute costs
		costs += expected.applyFunc(a.back(), [](double e, double a) {
				return cost(e, a);
			});
		//derivatives
		dz.back() = a.back() - expected;
		dW.back() = outerProduct(dz.back(), a[a.size()-2]);
		dB.back() = dz.back();
		for (int i = a.size() - 2; i >= 0; i--) {
			dz[i] = z[i].applyFunc(W[i+1].transpose()*dz[i+1], dzfunc);
			dW[i] = outerProduct(dz[i], a[i - 1]);
			dB[i] = dz[i];
		}
		//update network
		for (int i = 0; i < (int)W.size(); i++) {
			W[i] -= alpha * dW[i];
			B[i] -= alpha * dB[i];
		}
		//test sample
		Vector pred = (*this)(batch[ix].first);
		passed++;
		for (int i = 0; i < pred.N; i++)
			if (abs((pred[i] > .5 ? 1.0 : 0.0) - expected[i]) > .01) {
				passed--;
				break;
			}
	}
	std::tuple<int, int, Vector> rv;
	std::get<0>(rv) = passed;
	std::get<1>(rv) = tested;
	std::get<2>(rv) = costs * (1.0 / tested);
	return rv;
}
