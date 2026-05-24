#include"rational.h"

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
    numer = round(number * 10000);
    denom = 10000;
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
    if (other.numer != 0) {
        int reverseNumer = other.denom;
        int reverseDenom = other.numer;

        numer = numer * reverseNumer;
        denom = denom * reverseDenom;

        simplify();
        return *this;
    }
    else {
        std::cerr << "деление на 0!" << std::endl;
        return *this;
    }
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

Rational Rational::operator * (double other) const {
    Rational temp(*this);
    return temp *= Rational(other);
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

bool Rational::operator > (const Rational &other) const {
    return (long long)numer * other.denom > (long long)denom * other.numer;
}

bool Rational::operator < (const Rational &other) const {
    return !((long long)numer * other.denom > (long long)denom * other.numer);
};

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
	if (r.denom == 1 || r.numer == 0) os << r.numer;
    else os << r.numer << '/' << r.denom;
	return os;
}

long long gcd(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int Rational::getNumer() const {
    return numer;
}

int Rational::getDenom() const {
    return denom;
}

void Rational::simplify() {
    if (denom < 0) {
        numer = -numer; denom = -denom;
    }
    long nod = gcd(numer, denom);
    if (nod > 1) {
        numer /= nod; denom /= nod;
    }
}

Rational abs(const Rational& r) {
    return Rational(abs(r.getNumer()), r.getDenom());
}

Rational Rational::sqrt(const Rational &S) {
    if (S.getNumer() < 0) return -1;
    if (S.getNumer() == 0) return 0;

    if ((std::sqrt(S.getNumer()) * std::sqrt(S.getNumer()) == S.getNumer()) && (std::sqrt(S.getDenom()) * std::sqrt(S.getDenom()) == S.getDenom())) {
        int num = std::sqrt(S.getNumer()), den = std::sqrt(S.getDenom());
        return Rational(num, den);
    }

    Rational x = S, temp;
    do {
        temp = x;
        x = (x + S / x) / 2;
        x.simplify();
    } while (abs(temp - x) > 0.001);
    return x;
}
