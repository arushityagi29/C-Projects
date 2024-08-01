#include "hash.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int buff_size = 16;

int main() {
    char buffer[buff_size];

    Hashtable *ht = hash_create();
    int lineNum = 0;

    while (fgets(buffer, buff_size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (hash_get(ht, buffer) == NULL) {
            lineNum++;
            hash_put(ht, buffer, lineNum);
        }
    }

    printf("%d\n", lineNum);

    hash_destroy(&ht);

    return 0;
}
