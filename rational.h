#pragma once
#include<iostream>
using namespace std;

int gcd(int a, int b);

class Rational {
	int numer, denom;
	void simplify();
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

	Rational operator - () const;
	Rational &operator ++();
	Rational operator ++(int);

	bool operator == (const Rational &other) const;
	bool operator != (const Rational &other) const;

	explicit operator int() const;
	explicit operator double() const;

	friend istream &operator >> (istream &is, Rational &r);
	friend ostream &operator << (ostream &os, const Rational &r);
};