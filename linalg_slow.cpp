#include "linalg.h"


Vector::Vector() {
	size = 0;
	vec = nullptr;
}

Vector::Vector(int size) {
	this->size = size;
	vec = new double[size];
}

Vector::Vector(const Vector& v) {
	size = v.size;
	vec = new double[size];
	for(int i = 0; i < size; i++)
		vec[i] = v.vec[i];
}

Vector::Vector(Vector&& v) {
	size = v.size;
	v.size = 0;
	vec = v.vec;
	v.vec = nullptr;
}

Vector::~Vector() {
	if (vec == nullptr)
		delete[] vec;
}

double Vector::operator*(const Vector& v) const {
	if (v.N != N)
		throw;
	double d = 0;
	for (int i = 0; i < size; i++)
		d += vec[i] * v.vec[i];
	return d;
}

Vector Vector::operator*(double d) const {
	Vector v(N);
	for (int i = 0; i < v.N; i++)
		v.vec[i] = d * vec[i];
	return v;
}

Vector& Vector::operator*=(double d) {
	for (int i = 0; i < N; i++)
		vec[i] *= d;
	return *this;
}

Vector Vector::operator+(const Vector& v) const {
	if (N != v.N)
		throw;
	Vector o(N);
	for (int i = 0; i < N; i++)
		o.vec[i] = vec[i] + v.vec[i];
	return o;
}

Vector& Vector::operator+=(const Vector& v) {
	if (N != v.N)
		throw;
	for (int i = 0; i < N; i++)
		vec[i] += v.vec[i];
	return *this;
}

double& Vector::operator[](int i) {
	if (i < 0 || i >= N)
		throw;
	return vec[i];
}

const double& Vector::operator[](int i) const {
	if (i < 0 || i >= N)
		throw;
	return vec[i];
}

Vector operator*(double d, const Vector& v) {
	return v * d;
}
