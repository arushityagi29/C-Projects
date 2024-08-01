#include "path.h"

#include "graph.h"
#include "stack.h"

#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p == NULL) {
        return NULL;
    }
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    if (p->vertices == NULL) {
        free(p);
        return NULL;
    }
    return p;
}

void path_free(Path **pp) {
    if (pp == NULL || *pp == NULL) {
        return;
    }
    stack_free(&((*pp)->vertices));
    free(*pp);
    *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    //printf("total weight: %u\n", p->total_weight);
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_size(p->vertices) > 0) {
        uint32_t stack_top_value = 0;
        if (stack_peek(p->vertices, &stack_top_value)) {
            p->total_weight += (graph_get_weight(g, stack_top_value, val));
        }
    }
    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    uint32_t new_top;
    // if (stack_size(p->vertices) == 0) {
    //     return -1;
    // }
    if (stack_pop(p->vertices, &removed_vertex)) {
        if (stack_peek(p->vertices, &new_top)) {
            p->total_weight -= (graph_get_weight(g, new_top, removed_vertex));
        }
    }
    return removed_vertex;
}

void path_copy(Path *dst, const Path *src) {
    dst->total_weight = src->total_weight;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    stack_print(p->vertices, outfile, graph_get_names(g));
}
