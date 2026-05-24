#pragma once
#include <iostream>
#include "rational.h"

Rational* getRoots(Rational &a, Rational &b, Rational &c, int &cnt) {
    Rational D = b * b - (a * c * 4);
    if (D.getNumer() < 0) {
        cout << "not roots" << endl;
        return nullptr;
    }
    if (a.getNumer() != 0) {
        Rational *roots = new Rational[2];
        if (D == 0) {
            cnt = 1;
            roots[0] = -b / (a * 2);
        }
        else {
            cnt = 2;
            roots[0] = (-b + Rational::sqrt(D)) / (a * 2);
            roots[1] = (-b - Rational::sqrt(D)) / (a * 2);
        }
        return roots;
    }
    else {
        Rational *roots = new Rational[1];
        cnt = 1;
        roots[0] = -c / b;
        return roots;
    }
}
