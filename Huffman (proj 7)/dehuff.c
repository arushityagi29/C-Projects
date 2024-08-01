#include "bitreader.h"
#include "node.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 64

void print_help_message(void) {
    printf("Usage: dehuff -i infile -o outfile\n"
           "dehuff -h\n");
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);

    if (type1 != 'H' || type2 != 'C') {
        printf("Invalid compressed file format\n");
        return;
    }

    int num_nodes = 2 * num_leaves - 1;

    Node *stack[STACK_SIZE] = { NULL };
    int top = 0;

    for (int i = 0; i < num_nodes; i++) {
        int bit = bit_read_bit(inbuf);
        Node *node;
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            if (top >= 1) {
                node = node_create(0, 0);
                node->right = stack[--top];
                node->left = stack[--top];
            } else {
                printf("Invalid compressed file format: Stack underflow\n");
                return;
            }
            //node_free(&node);
        }

        stack[top++] = node;
    }

    Node *code_tree = stack[--top];
    for (int i = 0; i < (int) filesize; i++) {
        Node *node = code_tree;
        while (1) {
            int bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            if (node->left == NULL && node->right == NULL) {
                fprintf(fout, "%c", node->symbol);
                break;
            }
        }
    }

    for (int i = 0; i < top; i++) {
        free(stack[i]);
    }

    node_free(&code_tree);
}

int main(int argc, char *argv[]) {
    int opt;
    char *input_file = NULL;
    char *output_file = NULL;
    bool print_help = false;
    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
        case 'i': input_file = optarg; break;
        case 'o': output_file = optarg; break;
        case 'h': print_help = true; break;
        }
    }

    if ((input_file == NULL) || (output_file == NULL) || print_help) {
        if (input_file == NULL)
            printf("dehuff: -i option is required\n");
        if (output_file == NULL)
            printf("dehuff: -o option is required\n");
        print_help_message();
        exit(0);
    }

    FILE *fin = fopen(input_file, "rb");
    if (fin == NULL) {
        printf("Error opening input file\n");
        exit(EXIT_FAILURE);
    }

    FILE *fout = fopen(output_file, "wb");
    if (fout == NULL) {
        printf("Error opening output file\n");
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    BitReader *inbuf = bit_read_open(input_file);
    if (inbuf == NULL) {
        printf("Error opening input buffer\n");
        fclose(fin);
        fclose(fout);
        exit(EXIT_FAILURE);
    }

    dehuff_decompress_file(fout, inbuf);

    bit_read_close(&inbuf);
    fclose(fin);
    fclose(fout);

    return 0;
}
