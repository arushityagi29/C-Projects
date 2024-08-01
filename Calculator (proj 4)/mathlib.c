#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

const double PI = 3.14159265358979323846;

double Abs(double x) {
    if (x < 0) {
        return (-1) * (x);
    }
    return x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }

    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    x = fmod(x, 2 * PI);
    double ans = 0.0;
    double term = x;
    int n = 1;

    while (term > EPSILON || term < -EPSILON) {
        ans += term;
        term = -term * x * x / ((2 * n) * (2 * n + 1));
        n++;
    }

    return ans;
}

double Cos(double x) {
    x = fmod(x, 2 * PI);
    double ans = 1.0;
    double term = 1.0;
    int n = 1;

    while (term > EPSILON || term < -EPSILON) {
        term = -term * x * x / ((2 * n - 1) * (2 * n));
        ans += term;
        n++;
    }

    return ans;
}

double Tan(double x) {
    double sin_ans = Sin(x);
    double cos_ans = Cos(x);
    double ans = sin_ans / cos_ans;
    //if (cos_ans < EPSILON || cos_ans > -EPSILON){
    //    printf("hi!\n");
    //}
    return ans;
}
