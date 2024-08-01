#include "hash.h"

#include "ll.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define BUCKET_COUNT 10000;

Hashtable *hash_create(void) { // creating the hash table
    Hashtable *ht
        = (Hashtable *) malloc(sizeof(Hashtable)); // allocates memory and pointer for hash table
    if (ht == NULL) { // checks for allocation failure
        return NULL;
    }
    ht->size = BUCKET_COUNT; // creates size for number of buckets
    ht->buckets = (LL **) calloc((unsigned long) ht->size,
        sizeof(
            LL *)); // allocates memory for array of LL* pointers (size = BUCKET_COUNT -> one for each bucket)
    return ht; // returns new hash table pointer
}

bool hash_put(Hashtable *ht, char *key, int val) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) { // calulates ASCII value of each character and sum them
        sum += key[i];
    }
    int index
        = sum
          % BUCKET_COUNT; // mod with bucket count to get bucket index for key -> distribute keys based on char values
    if (ht->buckets[index] == NULL) { // if bucket index doesn't exist
        ht->buckets[index] = list_create(); // create new linked list and store in buckets array
        if (ht->buckets[index] == NULL) { // if list creation fails return NULL
            return false;
        }
    }

    // creating item:
    item finalitem; // final item item structure
    strcpy(finalitem.key, key); // copies key string into finalitem.key
    finalitem.id = val; // id of finalitem = val

    if (list_find(ht->buckets[index], cmp, &finalitem)
        != NULL) { // check if item with same key exists in linked list in bucket
        list_remove(ht->buckets[index], cmp, &finalitem); // if yes, remove item with same key
        return list_add(ht->buckets[index], &finalitem); // add finalitem with new value
    } else {
        return list_add(ht->buckets[index], &finalitem); // if new key, add finalitem into buckets
    }
}

int *hash_get(Hashtable *ht, char *key) { // gets value associated with key
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) { // gets the sum of the characters in the key
        sum += key[i];
    }
    int index = sum % BUCKET_COUNT; // calculates bucket index
    if (ht->buckets[index] == NULL) { // if linked list at bucket index doesn't exist return NULL
        return NULL;
    }

    item finalitem;
    strcpy(finalitem.key, key);

    item *found_item
        = list_find(ht->buckets[index], cmp, &finalitem); // looks for item at bucket index

    if (found_item == NULL)
        return NULL;
    return &found_item->id; // returns id of found item which holds its value
}

void hash_destroy(Hashtable **ht) { // destroys hash table
    for (int i = 0; i < (*ht)->size; i++) { // iterates through hash table buckets
        if ((*ht)->buckets[i] != NULL) { // if there is a linked list in the current bucket
            list_destroy(&(*ht)->buckets[i]); // destroy the list
        }
    }
    free((*ht)->buckets); // free the memory for array of pointers
    free(*ht); // free memory for hash table structure
    *ht = NULL; // set pointer to NULL
}
