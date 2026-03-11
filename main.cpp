#include "rational.h"
#include <cmath>

int main() {
    // Rational r1(-1, 3), r2(2, 6), r3(-10, 12);
    // cout << "-1/3 + 2/6 = " << r1 + r2 << endl;
    // cout << "-(-10/12) - 2/6 = " << -r3 - r2 << endl;
    // cout << "-1/3 * -10/12 = " << r1 * r3 << endl;
    // cout << "2/6 / -10/12 = " << r2 / r3 << endl;
    // cout << "2/6 == -1/3: " << (r2 == r1) << endl;

    Rational a, b, c;
    int cnt = 0;
    cin >> a >> b >> c;
    Rational *result =  Rational::getRoots(a, b, c, cnt);
    for (int i = 0; i < cnt; i++) {
        cout << "x" << (i+1) << " = " << result[i] << endl;
    }
    if (cnt > 0) delete[] result;
}