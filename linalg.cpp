#include "linalg.h"

using uint = unsigned;

extern "C"
double Dot(const double *vec1, const double *vec2, uint len);
extern "C"
void AddTo(double *vec1, const double *vec2, uint len);
extern "C"
void MatrixMul(const double *rowMatrix, const double *invec, double *outvec,
		uint rowlen, uint collen);

Vector::Vector() {
	size = 0;
	vec = nullptr;
}

Vector::Vector(int size) {
	this->size = size;
	vec = new double[size];
}

Vector::Vector(const Vector& vec) {
	size = vec.size;
	this->vec = new double[size];
	for(int i = 0; i < size; i++)
		this->vec[i] = vec.vec[i];
}

Vector::Vector(Vector&& vec) {
	size = vec.size;
	vec.size = 0;
	this->vec = vec.vec;
	vec.vec = nullptr;
}

Vector::~Vector() {
	if (vec == nullptr)
		delete[] vec;
}

double Vector::operator*(const Vector& v) {
	return Dot()
}
