#pragma once
#include<iostream>
using namespace std;

class Rational {
	long long numer;
	long long denom;

	void simplify();

	long long safeMultiply(long long a, long long b);
	long long safeAdd(long long a, long long b);

public:
    Rational();
    Rational(int number);
    Rational(int numerator, int denominator);
	Rational(double number);

	Rational &operator += (const Rational &other);
	Rational &operator -= (const Rational &other);
	Rational &operator *= (const Rational &other);
	Rational &operator /= (const Rational &other);

	Rational operator + (const Rational &other) const;
	Rational operator - (const Rational &other) const;
	Rational operator * (const Rational &other) const;
	Rational operator / (const Rational &other) const;

	Rational operator * (double other) const;

	Rational operator - () const;
	Rational &operator ++();
	Rational operator ++(int);

	bool operator == (const Rational &other) const;
	bool operator != (const Rational &other) const;
	bool operator > (const Rational &other) const;
	bool operator < (const Rational &other) const;

	explicit operator int() const;
	explicit operator double() const;

	friend istream &operator >> (istream &is, Rational &r);
	friend ostream &operator << (ostream &os, const Rational &r);

	long long getNumer() const;
	long long getDenom() const;

	static Rational sqrt(const Rational& S);
};

int gcd(long long a, long long b);
Rational abs(const Rational& r);