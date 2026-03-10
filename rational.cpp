#include "rational.h"

Rational::Rational() {
    numer = 0, denom = 1;
}

Rational::Rational(int number) {
    numer = number, denom = 1;
    simplify();
}

Rational::Rational(int numerator, int denominator) {
    if (denominator == 0) {
        numer = numerator; denom = 1;
    }
    else {numer = numerator; denom = denominator;}
    simplify();
}

Rational::Rational(double number) {
    numer = round(number * 1000000);
    denom = 1000000;
    simplify();
}

Rational& Rational::operator += (const Rational &other) {
    numer = (numer * other.denom + denom * other.numer);
    denom *= other.denom;
    simplify();
    return *this;
}

Rational &Rational::operator -= (const Rational &other) {
    return (*this += (-other));
}

Rational &Rational::operator *= (const Rational &other) {
    numer = numer * other.numer; denom = denom * other.denom;
    simplify();
    return *this;
}

Rational &Rational::operator /= (const Rational &other) {
    int reverseNumer = other.denom, reverseDenom = other.numer;
    numer = numer * reverseNumer; denom = denom * reverseDenom;
    simplify();
    return *this;
}

Rational Rational::operator + (const Rational &other) const {
    Rational temp(*this);
    return temp += other;
}

Rational Rational::operator - () const {
    Rational temp(-numer, denom);
    temp.simplify();
    return temp;
}

Rational Rational::operator - (const Rational &other) const {
    Rational temp(*this);
    return temp -= other;
}

Rational Rational::operator * (const Rational &other) const {
    Rational temp(*this);
    return temp *= other;
}

Rational Rational::operator / (const Rational &other) const {
    Rational temp(*this);
    return temp /= other;
}

Rational &Rational::operator ++ () {
    numer += denom;
    return *this;
}

Rational Rational::operator ++ (int) {
    Rational temp(*this);
    numer += denom;
    return temp;
}

bool Rational::operator == (const Rational &other) const {
    return (numer == other.numer && denom == other.denom);
}

bool Rational::operator != (const Rational &other) const {
    return !(numer == other.numer && denom == other.denom);
}

Rational::operator double() const {
	return double(numer) / denom;
}

Rational::operator int() const {
	return int(numer) / denom;
}

istream& operator >> (std::istream& is, Rational& r) {
    cout << "Введите число вида A/B или A или A.B" << endl;
    double numer;
    if (!(is >> numer)) return is;
    if (is.peek() == '/') {
        char slash; is >> slash; r.numer = numer;
        double denom; is >> denom; r.denom = denom;
    }
    else r = Rational(numer);
    r.simplify();
    return is;
}

ostream &operator << (ostream &os, const Rational &r) {
	if (r.denom == 1 || r.numer == 0) os << r.numer << endl;
    else os << r.numer << '/' << r.denom << endl;
	return os;
}

int gcd(int a, int b) {
    int a1 = abs(a), b1 = abs(b);
    if (a1 == 0) return b1;
    if (b1 == 0) return a1;
    int max = (a1 > b1) ? a1 : b1, min = (a1 < b1) ? a1 : b1;
    if (max % min == 0) return min;
    for (int i = min; i > 0; i--) {
        if (a1 % i == 0 && b1 % i == 0) return i;
    }
    return 1;
}

void Rational::simplify() {
    if (denom < 0) {
        numer = -numer; denom = -denom;
    }
    int nod = gcd(numer, denom);
    if (nod > 1) {
        numer /= nod; denom /= nod;
    }
}

Rational *getRoots(double a, double b, double c, int &cnt) {
    double disc = b * b - 4 * a * c;
    if (disc < 0) return nullptr;

    Rational *roots = new Rational[2];
    if (disc == 0) {
        cnt = 1;
        roots[0] = Rational(-b / (2 * a));
    }
    else {
        cnt = 2;
        roots[0] = Rational((-b  + sqrt(disc)) / (2 * a));
        roots[1] = Rational((-b  - sqrt(disc)) / (2 * a));
    }
    return roots;
}



