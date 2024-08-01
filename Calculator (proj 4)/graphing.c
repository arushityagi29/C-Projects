#include "mathlib.h"

#include <math.h>
#include <stdio.h>

#define PI      3.14159265358979323846
#define EPSILON 1e-14

int main() {

    double start = -2 * PI;
    double end = 2 * PI;
    double increment = 0.1;

    printf("x, sin(x), cos(x), tan(x)\n");

    for (double x = start; x <= end; x += increment) {
        double sin_x = Sin(x);
        double cos_x = Cos(x);
        double tan_x = Tan(x);

        printf("%f,%f,%f,%f\n", x, sin_x, cos_x, tan_x);
    }
    printf("\n");
    printf("math.h values\n");
    for (double x = start; x <= end; x += increment) {
        printf("%f,%f,%f,%f\n", x, sin(x), cos(x), tan(x));
    }

    return 0;
}
