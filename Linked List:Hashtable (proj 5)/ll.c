#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL)); // allocates memory for LL structure
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL; // head pointer is NULL (empty list)
    return l; // returns new head pointer
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node)); // allocates memory for new node which holds item i
    if (n == NULL) { // if allocation fails
        return false;
    }
    n->data = *i; // copies item's data into fied of node
    n->next = NULL;
    if (l->head == NULL) { // if empty LL, new node is the head (1st element)
        l->head = n;
        return true;
    } else { // if adding nodes to existing LL (adds to the beginning)
        n->next = l->head; // next node pointer is the head of list
        l->head = n; // head pointer of LL to new added node
        return true;
    }
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head; // starts at head of LL
    while (n != NULL) { // while there is a node in LL
        if (cmp(&n->data, i)) { // compares current node with item
            return &n->data; // if it matches, returns pointer of item
        }
        n = n->next; // goes to next node
    }
    return NULL;
}
void list_remove(
    LL *l, bool (*cmp)(item *, item *), item *i) { // removes item from linked list using cmp
    Node *current = l->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (cmp(&current->data, i)) { // if node and item match
            if (prev == NULL) { // if first node
                l->head = current->next; // updates head pointer to next node
            } else {
                prev->next
                    = current
                          ->next; // updates next pointer of previous node to next pointer of current (skips removed node)
            }
            free(current); // free memory of node
            return;
        }
        prev = current; // increments previous
        current = current->next; // increments current
    }
}
void list_destroy(LL **l) {
    Node *current = (*l)->head; // pointer to head of list
    Node *temp;

    while (current != NULL) { // goes through LL
        temp = current->next;
        free(current); // frees node
        current = temp; // incrememnts current
    }

    free(*l); // frees memory of LL
    *l = NULL; // sets LL pointer to NULL
}
