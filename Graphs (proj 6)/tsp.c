#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:dh"
Path *smallest_path = NULL;

Graph *read_file(FILE *infile, bool directed) {
    if (infile == NULL) {
        printf("Could not open file.");
    }
    uint32_t node = 0;

    int MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    sscanf(fgets(buffer, MAX_LENGTH, infile), "%d", &node);

    Graph *g = graph_create(node, directed);

    for (uint32_t i = 0; i < node; i++) {
        fgets(buffer, MAX_LENGTH, infile);
        buffer[strcspn(buffer, "\n")] = 0;
        graph_add_vertex(g, buffer, i);
    }

    uint32_t edge = 0;
    uint32_t start = 0, end = 0, weight = 0;

    fgets(buffer, MAX_LENGTH, infile);
    sscanf(buffer, "%d", &edge);
    for (uint32_t i = 0; i < edge; i++) {
        fscanf(infile, "%d %d %d", &start, &end, &weight);
        graph_add_edge(g, start, end, weight);
        if (!directed) {
            graph_add_edge(g, end, start, weight);
        }
    }
    fclose(infile);
    return g;
}

void dfs(Graph *g, Path *p, uint32_t current_vertex, uint32_t vertices_in_path) {
    graph_visit_vertex(g, current_vertex);
    path_add(p, current_vertex, g);
    if (vertices_in_path == graph_vertices(g)) {
        if (graph_get_weight(g, current_vertex, START_VERTEX) != 0) {
            path_add(p, START_VERTEX, g);
            if (path_distance(p) < path_distance(smallest_path)
                || path_distance(smallest_path) == 0) {
                path_copy(smallest_path, p);
            }
            path_remove(p, g);
        }
    } else {
        for (uint32_t i = 0; i < graph_vertices(g); i++) {
            if (graph_visited(g, i) == false) {
                if (graph_get_weight(g, current_vertex, i) != 0) {
                    dfs(g, p, i, vertices_in_path + 1);
                }
            }
        }
    }
    path_remove(p, g);
    graph_unvisit_vertex(g, current_vertex);
}

int main(int argc, char *argv[]) {
    int opt;
    FILE *input_file = stdin;
    bool directed = false;
    FILE *output_file = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            input_file = fopen(optarg, "r");
            if (input_file == NULL) {
                fprintf(stderr, "Invalid input file!\n");
            }
            break;
        case 'o':
            output_file = fopen(optarg, "w");
            if (output_file == NULL) {
                fprintf(stderr, "Invalid output file!");
            }
            break;
        case 'd': directed = true; break;
        case 'h':
            printf("Usage: tsp [options]\n"
                   "-i infile    Specify the input file path containing the cities and edges\n"
                   "             of a graph. If not specified, the default input should be\n"
                   "             set as stdin.\n"
                   "\n"
                   "-o outfile   Specify the output file path to print to. If not specified,\n"
                   "             the default output should be set as stdout.\n"
                   "\n"
                   "-d           Specifies the graph to be directed.\n"
                   "\n"
                   "-h           Prints out a help message describing the purpose of the\n"
                   "             graph and the command-line options it accepts, exiting the\n"
                   "             program afterwards.\n");
            exit(0);
            break;
        }
    }

    Graph *g = read_file(input_file, directed);
    Path *p = path_create(graph_vertices(g) + 1);
    smallest_path = path_create(graph_vertices(g) + 1);
    dfs(g, p, START_VERTEX, 1);

    if (path_distance(smallest_path) == 0) {
        fprintf(output_file, "No path found! Alissa is lost!\n");
    } else {
        fprintf(output_file, "Alissa starts at:\n");
        path_print(smallest_path, output_file, g);
        fprintf(output_file, "Total Distance: %d\n", path_distance(smallest_path));
    }

    fclose(output_file);
    path_free(&smallest_path);
    path_free(&p);
    graph_free(&g);
    return 0;
}
