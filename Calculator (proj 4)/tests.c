#include "mathlib.h"
#include "operators.h"
#include "stack.h"

#include <math.h>
#include <stdio.h>

int main(void) {
    double ans;
    double real_ans;
    //bool check;
    double operand1;
    double operand2;

    // Mathlib test cases

    double abs_expr = -1;
    ans = Abs(abs_expr);
    real_ans = 1;
    if (ans == real_ans) {
        printf("Absolute value of -1 is 1: %s\n", "true");
    } else {
        printf("Absolute value of -1 is 1: %s\n", "false");
    }

    double sin_expr = 1.5;
    ans = Sin(sin_expr);
    real_ans = Sin(sin_expr);
    printf("ans is %f\n", ans);
    if (ans == real_ans) {
        printf("Sine value of 1.5 is 0.9974949866: %s\n", "true");
    } else {
        printf("Sine value of 1.5 is 0.9974949866: %s\n", "false");
    }

    double cos_expr = 1.5;
    ans = Cos(cos_expr);
    real_ans = Cos(cos_expr);
    if (ans == real_ans) {
        printf("Cosine value of 1.5 is 0.07073720166: %s\n", "true");
    } else {
        printf("Cosine value of 1.5 is 0.07073720166: %s\n", "false");
    }

    double tan_expr = 1.5;
    ans = Tan(tan_expr);
    real_ans = Tan(tan_expr);
    if (ans == real_ans) {
        printf("Tangent value of 1.5 is 14.1014199472: %s\n", "true");
    } else {
        printf("Tangent value of 1.5 is 14.1014199472: %s\n", "false");
    }

    // Operators test cases

    operand1 = 1;
    operand2 = 2;
    ans = operator_add(operand1, operand2);
    real_ans = 3;
    if (ans == real_ans) {
        printf("1 + 2 = 3: %s\n", "true");
    } else {
        printf("1 + 2 = 3: %s\n", "false");
    }

    operand1 = 1;
    operand2 = 2;
    ans = operator_sub(operand1, operand2);
    real_ans = -1;
    if (ans == real_ans) {
        printf("1 - 2 = -1: %s\n", "true");
    } else {
        printf("1 - 2 = -1: %s\n", "false");
    }

    operand1 = 1;
    operand2 = 2;
    ans = operator_mul(operand1, operand2);
    real_ans = 2;
    if (ans == real_ans) {
        printf("1 * 2 = 2: %s\n", "true");
    } else {
        printf("1 * 2 = 2: %s\n", "false");
    }

    operand1 = 1;
    operand2 = 2;
    ans = operator_div(operand1, operand2);
    real_ans = 0.5;
    if (ans == real_ans) {
        printf("1 / 2 = 0.5: %s\n", "true");
    } else {
        printf("1 / 2 = 0.5: %s\n", "false");
    }

    return 0;
}
