#pragma once

class Vector;
class Matrix;
class VecFuncObj;

class VecFuncObj {
private:
	double (*d1)(double) = [](double d) -> double { return d; };
	double (*d2)(double, double) = [](double a, double b) -> double { return a; };

	double (*f1)(double) = d1;
	double (*f2)(double, double) = d2;
public:
	VecFuncObj(double (*f)(double)) : f1(f) {}
	VecFuncObj(double (*f)(double,double)) : f2(f) {}
	VecFuncObj(double (*fa)(double), double (*fb)(double, double)) :
		f1(fa), f2(fb) {}
	virtual double operator()(double d) { return f1(d); }
	virtual double operator()(double a, double b) { return f2(a, b); }
};

class Vector {
private:
	int size;
	double *vec;
public:
	Vector();
	Vector(int size);
	Vector(int size, double filld);
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
	Vector operator-(const Vector& vec) const;
	Vector& operator-=(const Vector& vec);
	Vector operator-() const;

	double& operator[](int i);
	const double& operator[](int i) const;

	double sum() const;
	Vector applyFunc(VecFuncObj& elWiseFunc) const;
	Vector applyFunc(const Vector& v, VecFuncObj& elWiseFunc) const;
	Vector applyFunc(double (*f)(double)) const;
	Vector applyFunc(const Vector& v, double (*f)(double, double)) const;

	const int &N = size;
};
Vector operator*(double d, const Vector& v);

class Matrix {
private:
	double *mat;
	int rows;
	int cols;
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
	Matrix operator-(const Matrix& m) const;
	Matrix& operator-=(const Matrix& m);
	Matrix operator-() const;

	double& operator()(int r, int c);
	const double& operator()(int r, int c) const;

	Matrix transpose() const;

	const int &M = rows;
	const int &N = cols;
};
Matrix operator*(double d, const Matrix& m);
