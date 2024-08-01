#include "operators.h"

#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false;
    }
    double lhs;
    double rhs;

    stack_pop(&rhs);
    stack_pop(&lhs);

    double result = op(lhs, rhs);
    stack_push(result);
    stack_print();

    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        return false;
    }
    double x;
    stack_pop(&x);
    double result = op(x);
    stack_push(result);
    return true;
}

double operator_add(double lhs, double rhs) {
    double result = lhs + rhs;
    return result;
}

double operator_sub(double lhs, double rhs) {
    double result = lhs - rhs;
    return result;
}

double operator_mul(double lhs, double rhs) {
    double result = lhs * rhs;
    return result;
}

double operator_div(double lhs, double rhs) {
    double result = lhs / rhs;
    return result;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
