#pragma once

class Vector;
class Matrix;

class Vector {
private:
	int size;
	double *vec;
public:
	Vector();
	Vector(int size);
	Vector(const Vector& vec);
	Vector(Vector&& vec);
	~Vector();

	Vector& operator=(const Vector& v);
	Vector& operator=(Vector&& v);

	double operator*(const Vector& vec) const;
	Vector operator*(double s) const;
	Vector& operator*=(double s);

	Vector operator+(const Vector& vec) const;
	Vector& operator+=(const Vector& vec);

	double& operator[](int i);
	const double& operator[](int i) const;

	const int &N = size;
};
Vector operator*(double d, const Vector& v);

class Matrix {
private:
	Vector *mat;
	int size;
	int vecSize;
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix& m);
	Matrix(Matrix&& m);
	~Matrix();

	Matrix& operator=(const Matrix& m);
	Matrix& operator=(Matrix&& m);

	Vector operator*(const Vector& v) const;
	Matrix operator*(double d) const;
	Matrix& operator*=(double d);

	Matrix operator+(const Matrix& m) const;
	Matrix& operator+=(const Matrix& m);

	Vector& operator[](int i);
	const Vector& operator[](int i) const;

	const int &M = size;
	const int &N = vecSize;
};
Matrix operator*(double d, const Matrix& m);
