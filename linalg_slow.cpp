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

Vector::Vector(int size, double filld) {
	if (size < 0)
		throw;
	this->size = size;
	if (size == 0)
		vec = nullptr;
	else {
		vec = new double[size];
		for (int i = 0; i < size; i++)
			vec[i] = filld;
	}
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
	return *this;
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
	return *this;
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

Vector Vector::operator-(const Vector& v) const {
	if (N != v.N)
		throw;
	Vector o(N);
	for (int i = 0; i < N; i++)
		o.vec[i] = vec[i] - v.vec[i];
	return o;
}

Vector& Vector::operator-=(const Vector& v) {
	if (N != v.N)
		throw;
	for (int i = 0; i < N; i++)
		vec[i] -= v.vec[i];
	return *this;
}

Vector Vector::operator-() const {
	Vector v(N);
	for (int i = 0; i < N; i++)
		v.vec[i] = -vec[i];
	return v;
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

double Vector::sum() const {
	double s = 0;
	for (int i = 0; i < N; i++)
		s += vec[i];
	return s;
}

Vector Vector::applyFunc(VecFuncObj& func) const {
	Vector v(N);
	for (int i = 0; i < v.N; i++)
		v.vec[i] = func(vec[i]);
	return v;
}

Vector Vector::applyFunc(VecFuncObj& func, const Vector& v) const {
	if (N != v.N)
		throw;
	Vector o(N);
	for (int i = 0; i < o.N; i++)
		o.vec[i] = func(vec[i], v.vec[i]);
	return o;
}
Vector Vector::applyFunc(double (*f)(double)) const {
	VecFuncObj fo(f);
	return applyFunc(fo);
}
Vector Vector::applyFunc(double (*f)(double, double), const Vector& v) const {
	VecFuncObj fo(f);
	return applyFunc(fo, v);
}


Vector operator*(double d, const Vector& v) {
	return v * d;
}


Matrix::Matrix() {
	rows = cols = 0;
	mat = nullptr;
}

Matrix::Matrix(int rows, int cols) {
	if (rows < 0 || cols < 0)
		throw;

	if (rows > 0 && cols > 0) {
		mat = new double[rows * cols];
		this->rows = rows;
		this->cols = cols;
	} else {
		mat = nullptr;
		rows = cols = 0;
	}
}

Matrix::Matrix(const Matrix& m) {
	rows = m.M;
	cols = m.N;
	if (M > 0 && N > 0) {
		mat = new double[rows * cols];
		for (int i = 0; i < rows * cols; i++)
			mat[i] = m.mat[i];
	} else {
		mat = nullptr;
	}
}

Matrix::Matrix(Matrix&& m) {
	rows = m.rows;
	cols = m.cols;
	mat = m.mat;
	m.rows = m.cols = 0;
	m.mat = nullptr;
}

Matrix::~Matrix() {
	delete[] mat;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (rows != 0) {
		rows = cols = 0;
		delete[] mat;
		mat = nullptr;
	}
	rows = m.M;
	cols = m.N;
	if (M > 0 && N > 0) {
		mat = new double[rows * cols];
		for (int i = 0; i < rows * cols; i++)
			mat[i] = m.mat[i];
	} else {
		mat = nullptr;
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& m) {
	if (rows != 0) {
		rows = cols = 0;
		delete[] mat;
		mat = nullptr;
	}
	rows = m.rows;
	cols = m.cols;
	mat = m.mat;
	m.rows = m.cols = 0;
	m.mat = nullptr;
	return *this;
}

Vector Matrix::operator*(const Vector& v) const {
	if (N != v.N)
		throw;
	Vector o(M);
	for(int i = 0; i < M; i++) {
		o[i] = 0;
		for (int j = 0; j < N; j++)
			o[i] += v[j] * mat[i*N + j];
	}
	return o;
}

Matrix Matrix::operator*(double d) const {
	Matrix a(M, N);
	for (int i = 0; i < M * N; i++)
		a.mat[i] = mat[i] * d;
	return a;
}

Matrix& Matrix::operator*=(double d) {
	for (int i = 0; i < M * N; i++)
		mat[i] *= d;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	if (M != m.M || N != m.N)
		throw;
	Matrix a(M, N);
	for (int i = 0; i < M * N; i++)
		a.mat[i] = mat[i] + m.mat[i];
	return a;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (M != m.M || N != m.N)
		throw;
	for (int i = 0; i < M * N; i++)
		mat[i] += m.mat[i];
	return *this;
}

Matrix Matrix::operator-(const Matrix& m) const {
	if (M != m.M || N != m.N)
		throw;
	Matrix a(M, N);
	for (int i = 0; i < M * N; i++)
		a.mat[i] = mat[i] - m.mat[i];
	return a;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	if (M != m.M || N != m.N)
		throw;
	for (int i = 0; i < M * N; i++)
		mat[i] -= m.mat[i];
	return *this;
}

Matrix Matrix::operator-() const {
	Matrix m(M, N);
	for (int i = 0; i < M * N; i++)
		m.mat[i] = -mat[i];
	return m;
}

double& Matrix::operator()(int r, int c) {
	if (r < 0 || r >= M || c < 0 || c >= N)
		throw;
	return mat[r*N + c];
}

const double& Matrix::operator()(int r, int c) const {
	if (r < 0 || r >= M || c < 0 || c >= N)
		throw;
	return mat[r*N + c];
}

Matrix operator*(double d, const Matrix& m) {
	return m * d;
}
