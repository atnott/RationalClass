#include"rational.h"
#include<climits>
#include<stdexcept>

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
    long long part1 = safeMultiply(numer, other.denom);
    long long part2 = safeMultiply(denom, other.numer);

    numer = safeAdd(part1, part2);
    denom = safeMultiply(denom, other.denom);

    simplify();
    return *this;
}

Rational &Rational::operator -= (const Rational &other) {
    return (*this += (-other));
}

Rational &Rational::operator *= (const Rational &other) {
    numer = safeMultiply(numer, other.numer);
    denom = safeMultiply(denom, other.denom);
    simplify();
    return *this;
}

Rational &Rational::operator /= (const Rational &other) {

    if (other.numer == 0) {
        throw std::invalid_argument("Деление на 0");
    }

    long long reverseNumer = other.denom;
    long long reverseDenom = other.numer;

    numer = safeMultiply(numer, reverseNumer);
    denom = safeMultiply(denom, reverseDenom);

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

long long Rational::getNumer() const {
    return numer;
}

long long Rational::getDenom() const {
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

long long Rational::safeMultiply(long long a, long long b) {
    if (a == 0 || b == 0) return 0;

    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) throw std::overflow_error("Переполнение long long");
        }
        else {
            if (b < LLONG_MIN / a) throw std::overflow_error("Переполнение long long");
        }
    }
    else {
        if (b > 0) {
            if (a < LLONG_MIN / b) throw std::overflow_error("Переполнение long long при умножении!");
        }
        else {
            if (a < LLONG_MAX / b) throw std::overflow_error("Переполнение long long при умножении!");
        }
    }
    return a * b;
}

long long Rational::safeAdd(long long a, long long b) {
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        throw std::overflow_error("Переполнение long long");
    }
    return a + b;
}
