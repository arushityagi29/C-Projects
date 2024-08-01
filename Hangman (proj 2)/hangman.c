#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdlib.h>

void alphabetize(char eliminated[], int eliminated_len) {
    for (int i = 0; i < eliminated_len - 1; i++) {
        for (int j = 0; j < eliminated_len - i - 1; j++) {
            if (eliminated[j] > eliminated[j + 1]) {
                char temp = eliminated[j];
                eliminated[j] = eliminated[j + 1];
                eliminated[j + 1] = temp;
            }
        }
    }
}

bool only_special_chars(const char *secret) {
    while (*secret != '\0') {
        if (*secret != ' ' && *secret != '\'' && *secret != '-') {
            return false;
        }
        secret++;
    }
    return true;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Usage: ./hangman <secret word or phrase>\n");
        printf("If the secret is multiple words, you must quote it\n");
        return 1;
    }

    const char *secret = argv[1];

    if (!validate_secret(secret)) {
        return 1;
    }

    int total_length = 0;
    int length = 0;
    while (secret[total_length] != '\0') {
        total_length++;
    }

    for (int i = 0; i < total_length; i++) {
        if (secret[i] != ' ' && secret[i] != '\'' && secret[i] != '-') {
            length++;
        }
    }

    int gallow_index = 0;

    // Initial clear screen
    //printf("\033[1;1H\033[2J");

    // Game loop
    int correct_guess_count = 0;
    char correct_guessed[26];

    int wrong_guess_count = 0;
    char eliminated[26];

    while (wrong_guess_count < LOSING_MISTAKE) {
        // Clear screen before each turn
        printf("\033[1;1H\033[2J");

        // Checks if there are only special characters (player wins automatically)
        if (only_special_chars(secret)) {
            printf("\033[1;1H\033[2J");
            printf("\nYou win! The secret phrase was: %s\n", secret);
            break;
        }

        // Print gallows
        printf("%s\n", arts[gallow_index]);
        printf("\n");

        // Print the phrase
        printf("    Phrase: ");
        for (int i = 0; secret[i] != '\0'; i++) {
            if (is_lowercase_letter(secret[i])) {
                if (string_contains_character(correct_guessed, secret[i])) {
                    printf("%c", secret[i]);
                } else {
                    printf("_");
                }
            } else if (secret[i] == '-') {
                printf("-");
            } else if (secret[i] == '\'') {
                printf("'");
            } else if (secret[i] == ' ') {
                printf(" ");
            }
        }
        printf("\n");

        // Print eliminated letters
        printf("Eliminated: ");
        alphabetize(eliminated, wrong_guess_count);
        for (int i = 0; i < wrong_guess_count; i++) {
            printf("%c", eliminated[i]);
        }
        printf("\n\n");

        // Ask for a letter
        char guess;
        do {
            printf("Guess a letter: ");

            guess = read_letter();

        } while (string_contains_character(correct_guessed, guess)
                 || string_contains_character(eliminated, guess) || !is_lowercase_letter(guess));

        // Check if guess is already guessed
        //if (string_contains_character(correct_guessed, guess) || string_contains_character(eliminated, guess)) {
        //    printf("You guessed %c already. Guess again.\n", guess);
        //    continue;
        //}

        // Check if the guess is in the secret phrase
        if (string_contains_character(secret, guess)) {
            for (int i = 0; secret[i] != '\0'; i++) {
                if (is_lowercase_letter(secret[i]) && secret[i] == guess) {
                    correct_guessed[correct_guess_count] = guess;
                    correct_guess_count += 1;
                }
            }
        } else {
            // Incorrect guess
            eliminated[wrong_guess_count] = guess;
            wrong_guess_count += 1;
            gallow_index += 1;
        }

        // Check for a win

        bool letters_guessed = true;

        for (int i = 0; secret[i] != '\0'; i++) {
            if (is_lowercase_letter(secret[i])
                && !string_contains_character(correct_guessed, secret[i])) {
                letters_guessed = false;
                break;
            }
        }

        if (letters_guessed) {

            printf("\033[1;1H\033[2J");
            printf("%s\n\n", arts[gallow_index]);
            //print final phrase
            printf("    Phrase: ");
            for (int i = 0; secret[i] != '\0'; i++) {
                if (is_lowercase_letter(secret[i])) {
                    if (string_contains_character(correct_guessed, secret[i])) {
                        printf("%c", secret[i]);
                    } else {
                        printf("_");
                    }
                } else if (secret[i] == '-') {
                    printf("-");
                } else if (secret[i] == '\'') {
                    printf("'");
                } else if (secret[i] == ' ') {
                    printf(" ");
                }
            }
            printf("\n");
            //print final eliminated
            printf("Eliminated: ");
            alphabetize(eliminated, wrong_guess_count);
            for (int i = 0; i < wrong_guess_count; i++) {
                printf("%c", eliminated[i]);
            }
            printf("\n");
            printf("\nYou win! The secret phrase was: %s\n", secret);
            break;
        }
    }

    // Check for a loss
    if (wrong_guess_count == LOSING_MISTAKE) {
        printf("\033[1;1H\033[2J");
        printf("%s\n\n", arts[gallow_index]);
        //print final phrase
        printf("    Phrase: ");
        for (int i = 0; secret[i] != '\0'; i++) {
            if (is_lowercase_letter(secret[i])) {
                if (string_contains_character(correct_guessed, secret[i])) {
                    printf("%c", secret[i]);
                } else {
                    printf("_");
                }
            } else if (secret[i] == '-') {
                printf("-");
            } else if (secret[i] == '\'') {
                printf("'");
            } else if (secret[i] == ' ') {
                printf(" ");
            }
        }
        printf("\n");
        //print final eliminated
        printf("Eliminated: ");
        alphabetize(eliminated, wrong_guess_count);
        for (int i = 0; i < wrong_guess_count; i++) {
            printf("%c", eliminated[i]);
        }
        printf("\n");
        printf("\nYou lose! The secret phrase was: %s\n", secret);
    }

    return 0;
}
