#pragma once

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

	double operator*(const Vector& vec) const;
	Vector operator*(double s) const;
	Vector& operator*=(double s);

	Vector operator+(const Vector& vec) const;
	Vector& operator+=(const Vector& vec);

	double& operator[](int i);
	const double& operator[](int i) const;

	const int &N = size;
};
