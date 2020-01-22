#include "linalg.h"


Vector::Vector() {
	size = 0;
	vec = nullptr;
}

Vector::Vector(int size) {
	if (size < 0)
		throw;
	this->size = size;
	if (size == 0)
		vec = nullptr;
	else
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

Vector& Vector::operator=(const Vector& v) {
	if (size != 0) {
		size = 0;
		delete[] vec;
		vec = nullptr;
	}
	if (v.N != 0) {
		size = v.N;
		vec = new double[size];
		for (int i = 0; i < N; i++)
			vec[i] = v.vec[i];
	}
}

Vector& Vector::operator=(Vector&& v) {
	if (size != 0) {
		size = 0;
		delete[] vec;
	}
	size = v.size;
	vec = v.vec;
	v.size = 0;
	v.vec = nullptr;
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


Matrix::Matrix() {
	size = vecSize = 0;
	mat = nullptr;
}

Matrix::Matrix(int rows, int cols) {
	if (rows < 0 || cols < 0)
		throw;

	if (rows > 0 && cols > 0) {
		mat = new Vector[rows];
		size = rows;
		vecSize = cols;
		for(int i = 0; i < size; i++)
			mat[i] = Vector(vecSize);
	} else {
		mat = nullptr;
		size = vecSize = 0;
	}
}

Matrix::Matrix(const Matrix& m) {
	size = m.M;
	vecSize = m.N;
	if (M > 0 && N > 0) {
		mat = new Vector[M];
		for (int i = 0; i < M; i++)
			mat[i] = m.mat[i];
	} else {
		mat = nullptr;
	}
}

Matrix::Matrix(Matrix&& m) {
	size = m.size;
	vecSize = m.vecSize;
	mat = m.mat;
	m.size = m.vecSize = 0;
	m.mat = nullptr;
}

Matrix::~Matrix() {
	delete[] mat;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (size != 0) {
		size = vecSize = 0;
		delete[] mat;
		mat = nullptr;
	}
	size = m.M;
	vecSize = m.N;
	if (M > 0 && N > 0) {
		mat = new Vector[M];
		for (int i = 0; i < M; i++)
			mat[i] = m.mat[i];
	} else {
		mat = nullptr;
	}
}

Matrix& Matrix::operator=(Matrix&& m) {
	if (size != 0) {
		size = vecSize = 0;
		delete[] mat;
		mat = nullptr;
	}
	size = m.size;
	vecSize = m.vecSize;
	mat = m.mat;
	m.size = m.vecSize = 0;
	m.mat = nullptr;
}

Vector Matrix::operator*(const Vector& v) const {
	if (N != v.N)
		throw;
	Vector o(M);
	for(int i = 0; i < N; i++)
		o[i] = v * mat[i];
	return o;
}

Matrix Matrix::operator*(double d) const {
	Matrix a(M, N);
	for (int i = 0; i < M; i++)
		a.mat[i] = mat[i] * d;
	return a;
}

Matrix& Matrix::operator*=(double d) {
	for (int i = 0; i < M; i++)
		mat[i] *= d;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	if (M != m.M || N != m.N)
		throw;
	Matrix a(M, N);
	for (int i = 0; i < M; i++)
		a.mat[i] = mat[i] + m.mat[i];
	return a;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (M != m.M || N != m.N)
		throw;
	for (int i = 0; i < M; i++)
		mat[i] += m.mat[i];
	return *this;
}

Vector& Matrix::operator[](int i) {
	if (i < 0 || i >= M)
		throw;
	return mat[i];
}

const Vector& Matrix::operator[](int i) const {
	if (i < 0 || i >= M)
		throw;
	return mat[i];
}

Matrix operator*(double d, const Matrix& m) {
	return m * d;
}
