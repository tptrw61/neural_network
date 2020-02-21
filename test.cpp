#include "nn.h"
#include <iostream>

double collapse(double d) {
	return d > .5 ? 1 : 0;
}

struct BitBlock {
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
};
union BF {
	BitBlock bits;
	unsigned char byte;
};
class Bits {
private:
	BF bf;
public:
	Bits() { bf.byte = 0; }
	Bits(BitBlock b) { bf.bits = b; }
	Bits(unsigned char b) { bf.byte = b; }
	bool getBit(int i) {
		if (i < 0 || i >= 8)
			throw;
		switch (i) {
			case 0: return bf.bits.b0;
			case 1: return bf.bits.b1;
			case 2: return bf.bits.b2;
			case 3: return bf.bits.b3;
			case 4: return bf.bits.b4;
			case 5: return bf.bits.b5;
			case 6: return bf.bits.b6;
			case 7: return bf.bits.b7;
		}
		return -1;
	}
	void setBit(int i, bool v) {
		if (i < 0 || i >= 8)
			throw;
		switch (i) {
			case 0: bf.bits.b0 = v; return;
			case 1: bf.bits.b1 = v; return;
			case 2: bf.bits.b2 = v; return;
			case 3: bf.bits.b3 = v; return;
			case 4: bf.bits.b4 = v; return;
			case 5: bf.bits.b5 = v; return;
			case 6: bf.bits.b6 = v; return;
			case 7: bf.bits.b7 = v; return;
		}
	}
};

void printVec(const Vector& v) {
	std::printf("< ");
	int i;
	for (i = 0; i < v.N - 1; i++)
		std::printf("%.5lf, ", v[i]);
	for (; i < v.N; i++)
		std::printf("%.5lf ", v[i]);
	std::printf(">");
}

int main() {
	std::vector<std::pair<Vector, Vector>> batch;
	for (int i = 0; i < 256; i++) {
		Vector vi(8);
		Vector vo(1);
		Bits b(i);
		bool y = 0;
		for (int j = 0; j < 8; j++) {
			vi[j] = b.getBit(j);
			y ^= b.getBit(j);
		}
		vo[0] = y ? 1.0 : 0.0;
		std::pair<Vector, Vector> p(vi, vo);
		batch.push_back(p);
	}
	NeuralNetwork nn(4, 8, 4, 4, 1);
	auto res = nn.trainBatch(batch);
	int passed = std::get<0>(res);
	int tested = std::get<1>(res);
	Vector cost = std::get<2>(res);

	std::printf("%d/%d\n", passed, tested);
	printVec(cost);
	std::printf("\n");

	Vector vin(8);
	double ds[8];
	Vector vout;
	while (1) {
		std::printf("Enter 8 values:\n");
		std::scanf("%lf %lf %lf %lf %lf %lf %lf %lf", 
				ds, ds+1, ds+2, ds+3, ds+4, ds+5, ds+6, ds+7);
		for (int i = 0; i < vin.N; i++)
			vin[i] = ds[i];
		vout = nn(vin);
		printVec(vin);
		std::printf(" => ");
		printVec(vout);
		std::printf("\n\n");
	}

	return 0;
}
