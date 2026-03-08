#include "rational.h"
#include <cmath>

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

template <class t>
double cinArgument(t &number) {
    cin >> number;
    return double(number);
}

int main() {
    // Rational r1(-1, 3), r2(2, 6), r3(-10, 12);
    // cout << "-1/3 + 2/6 = " << r1 + r2 << endl;
    // cout << "-(-10/12) - 2/6 = " << -r3 - r2 << endl;
    // cout << "-1/3 * -10/12 = " << r1 * r3 << endl;
    // cout << "2/6 / -10/12 = " << r2 / r3 << endl;
    // cout << "2/6 == -1/3: " << (r2 == r1) << endl;

    Rational r1, r2, r3;
    double a = cinArgument(r1), b = cinArgument(r2), c = cinArgument(r3);
    int cnt = 0;
    Rational *result = getRoots(a, b, c,cnt);
    for (int i = 0; i < cnt; i++) {
        cout << "x" << (i+1) << " = " << result[i] << endl;
    }
    delete[] result;
}