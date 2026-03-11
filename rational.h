#pragma once
#include<iostream>
using namespace std;

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

	int getNumer() const;
	int getDenom() const;

	static Rational sqrt(Rational& S);
	static Rational *getRoots(Rational &a, Rational &b, Rational &c, int &cnt);
};

int gcd(int a, int b);
Rational abs(const Rational& r);