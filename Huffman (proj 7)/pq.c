#include "pq.h"

#include "bitwriter.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q == NULL) {
        return NULL;
    }

    q->list = NULL; //initializing empty queue
    return q;
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {
    return q->list != NULL && q->list->next == NULL;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight > e2->tree->weight) {
        return false;
    } else {
        return e1->tree->symbol < e2->tree->symbol;
    }
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = (ListElement *) malloc(sizeof(ListElement));
    if (new_element == NULL) {
        exit(EXIT_FAILURE);
    }

    new_element->tree = tree;

    if (q->list == NULL || pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
        return;
    }

    ListElement *current = q->list;
    while (current->next != NULL && pq_less_than(current->next, new_element)) {
        current = current->next;
    }
    new_element->next = current->next;
    current->next = new_element;
}

Node *dequeue(PriorityQueue *q) {
    if (q->list == NULL) {
        exit(EXIT_FAILURE);
    }
    Node *tree = q->list->tree;
    ListElement *temp = q->list;
    q->list = q->list->next;
    free(temp);
    return tree;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
