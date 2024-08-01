#include "hangman_helpers.h"

#include <stdio.h>

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    char letter;
    //printf("Guess a letter: ");
    scanf("%c", &letter);
    fgetc(stdin);
    return letter;
}

bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool validate_secret(const char *secret) {
    int length = 0;

    while (secret[length] != '\0') {
        if (length >= MAX_LENGTH) {
            printf("the secret phrase is over 256 characters\n");
            return false;
        }
        length++;
    }

    for (int i = 0; i < length; i++) {
        char curr_letter = secret[i];
        if (!is_lowercase_letter(curr_letter) && curr_letter != ' ' && curr_letter != '\''
            && curr_letter != '-') {
            printf("invalid character: '%c'\n", curr_letter);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }

    return true;
}
