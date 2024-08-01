#include "hangman_helpers.h"

#include <stdio.h>

int main(void) {

    char secret[] = "abc";
    char test_char1 = 'c';
    bool check = string_contains_character(secret, test_char1);
    printf("%s contains %c: %s\n", secret, test_char1, check ? "true" : "false");

    char test_char2 = 'a';
    bool check2 = string_contains_character(secret, test_char2);
    printf("%s contains %c: %s\n", secret, test_char2, check2 ? "true" : "false");

    char test_char3 = 'd';
    bool check3 = string_contains_character(secret, test_char3);
    printf("%s contains %c: %s\n", secret, test_char3, check3 ? "true" : "false");

    char secret2[] = "aabc";
    char test_char4 = 'a';
    bool check4 = string_contains_character(secret2, test_char4);
    printf("%s contains %c: %s\n", secret2, test_char4, check4 ? "true" : "false");

    char test_char5 = '1';
    bool check5 = is_lowercase_letter(test_char5);
    printf("%c is valid input: %s\n", test_char5, check5 ? "true" : "false");

    char test_char6 = 'A';
    bool check6 = is_lowercase_letter(test_char6);
    printf("%c is valid input: %s\n", test_char6, check6 ? "true" : "false");

    char test_char7 = 'e';
    bool check7 = is_lowercase_letter(test_char7);
    printf("%c is valid input: %s\n", test_char7, check7 ? "true" : "false");

    char test_secret1[]
        = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    bool check8 = validate_secret(test_secret1);
    printf("%s is a valid input: %s\n", test_secret1, check8 ? "true" : "false");

    char test_secret2[]
        = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    bool check9 = validate_secret(test_secret2);
    printf("%s is a valid input: %s\n", test_secret2, check9 ? "true" : "false");

    char test_secret3[] = "hello!";
    bool check10 = validate_secret(test_secret3);
    printf("%s is a valid input: %s\n", test_secret3, check10 ? "true" : "false");

    char test_secret4[] = "Hi";
    bool check11 = validate_secret(test_secret4);
    printf("%s is a valid input: %s\n", test_secret4, check11 ? "true" : "false");

    char test_secret5[] = "hi";
    bool check12 = validate_secret(test_secret5);
    printf("%s is a valid input: %s\n", test_secret5, check12 ? "true" : "false");

    return 0;
}