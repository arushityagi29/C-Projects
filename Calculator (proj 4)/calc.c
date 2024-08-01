#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // include this for getopt

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    bool use_libm = false;
    int opt;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'm': use_libm = true; break;
        case 'h': printf(USAGE, argv[0]); return 0;
        default: fprintf(stderr, "Usage: %s [-mh]\n", argv[0]); return 1;
        }
    }

    char expr[BUFFER_SIZE];
    char *saveptr;
    bool error = false;
    double result = 0.0;
    bool eof = 0;

    while (!eof) {
        fprintf(stderr, "> ");
        if (fgets(expr, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        if (strlen(expr) > 0 && expr[strlen(expr) - 1] == '\n') {
            expr[strlen(expr) - 1] = '\0';
        }
        const char *token = strtok_r(expr, " ", &saveptr);
        while (token != NULL && !error) {
            if (stack_size <= STACK_CAPACITY) { //check if stack is not full
                double num;
                if (parse_double(token, &num)) {
                    if (!stack_push(num)) {
                        fprintf(stderr, ERROR_NO_SPACE, num);
                        error = true;
                        break;
                    }
                } else if (strlen(token) >= 1) {
                    char op = *token;
                    if (op == '+' || op == '-' || op == '*' || op == '/'
                        || op == '%') { // binary operator
                        if (stack_size >= 2) {
                            double rhs;
                            double lhs;
                            if (stack_pop(&rhs) && stack_pop(&lhs)) {
                                if (op == '+') {
                                    result = operator_add(lhs, rhs);
                                } else if (op == '-') {
                                    result = operator_sub(lhs, rhs);
                                } else if (op == '*') {
                                    result = operator_mul(lhs, rhs);
                                } else if (op == '/') {
                                    result = operator_div(lhs, rhs);
                                } else if (op == '%') {
                                    result = fmod(lhs, rhs);
                                }
                                stack_push(result);
                            } else {
                                fprintf(stderr, ERROR_BINARY_OPERATOR);
                                error = true;
                                break;
                            }
                        } else {
                            fprintf(stderr, ERROR_BINARY_OPERATOR);
                            error = true;
                            break;
                        }
                    } else if (op == 's' || op == 'c' || op == 't' || op == 'a'
                               || op == 'r') { // unary operator
                        if (stack_size >= 1) {
                            double x;
                            if (stack_pop(&x)) {
                                if (op == 's') {
                                    result = use_libm ? sin(x) : Sin(x);
                                } else if (op == 'c') {
                                    result = use_libm ? cos(x) : Cos(x);
                                } else if (op == 't') {
                                    result = use_libm ? tan(x) : Tan(x);
                                } else if (op == 'a') {
                                    result = use_libm ? fabs(x) : Abs(x);
                                } else if (op == 'r') {
                                    result = use_libm ? sqrt(x) : Sqrt(x);
                                }
                                stack_push(result);
                            } else {
                                fprintf(stderr, ERROR_UNARY_OPERATOR);
                                error = true;
                                break;
                            }
                        } else {
                            fprintf(stderr, ERROR_UNARY_OPERATOR);
                            error = true;
                        }
                    } else {
                        fprintf(stderr, ERROR_BAD_CHAR, *token);
                        error = true;
                        break;
                    }
                }
            } else {
                fprintf(stderr, ERROR_NO_SPACE, stack[STACK_CAPACITY - 1]);
                error = true;
                break;
            }
            token = strtok_r(NULL, " ", &saveptr);
        }

        if (!error) {
            stack_print();
            printf("\n");
            stack_clear();
        } else {
            stack_clear();
        }
        error = false;
    }
    return 0;
}
