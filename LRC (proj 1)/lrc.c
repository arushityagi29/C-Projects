#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;
const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

int num_players(void) {
    int players = 3;
    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &players);

    if (scanf_result < 1 || players < 3 || players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        players = 3;
    }
    return players;
}

int seed_num(void) {
    unsigned seed = 4823;
    printf("Random-number seed? ");
    int scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    }

    return seed;
}

Position roll(void) {
    int roll_num = random() % 6;
    return die[roll_num];
}

int check_active_players(int player_chip[], int totalPlayers) {
    int active_players = 0;
    for (int i = 0; i < totalPlayers; i++) {
        if (player_chip[i] > 0) {
            active_players += 1;
        }
    }
    return active_players;
}

int main(void) {
    int totalPlayers = num_players();
    int seed = seed_num();

    srandom(seed);

    int active_players = totalPlayers;
    int turn = 0;
    int player_chip[totalPlayers];
    for (int i = 0; i < totalPlayers; i++) {
        player_chip[i] = 3;
    }

    while (active_players > 1) {
        for (int i = 0; i < totalPlayers; i++) {
            if (player_chip[i] == 0) {
                continue;
            } else if (player_chip[i] == 1) {
                turn = 1;
            } else if (player_chip[i] == 2) {
                turn = 2;
            } else {
                turn = 3;
            }

            for (int j = 0; j < turn; j++) {
                Position player_roll = roll(); // player_role is a number between 0 and 3
                if (player_roll == DOT) {
                    continue;
                    //printf("DOT\n");
                } else if (player_roll == LEFT) {
                    player_chip[(i + 1) % totalPlayers] += 1;
                    player_chip[i] -= 1;
                    //printf("RIGHT\n");
                } else if (player_roll == RIGHT) {
                    if (i == 0) {
                        player_chip[totalPlayers - 1] += 1;
                    } else {
                        player_chip[i - 1] += 1;
                    }
                    player_chip[i] -= 1;
                    //printf("LEFT\n");
                    //printf("%d ", i);
                    //printf("%s\n", player_name[i-1]);
                } else if (player_roll == CENTER) {
                    player_chip[i] -= 1;
                    //printf("CENTER\n");
                }

                active_players = check_active_players(player_chip, totalPlayers);
                if (active_players == 1) {
                    break;
                }
                //printf("roll: %u\n", player_roll); //prints the player's roll
                //printf("chip count: %d\n", player_chip[i]); //prints the player's current chip count
            }
            printf("%s: ends her turn with %d\n", player_name[i], player_chip[i]);
            if (active_players == 1) {
                break;
            }
        }
    }

    for (int i = 0; i < totalPlayers; i++) {
        if (player_chip[i] != 0) {
            printf("%s won!\n", player_name[i]);
        }
    }
    return 0;
}
