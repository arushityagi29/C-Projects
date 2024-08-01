#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t code;
    uint8_t code_length;
} Code;

void print_help(void) {
    printf("Usage: huff -i infile -o outfile\n"
           "huff -v -i infile -o outfile\n"
           "huff -h\n");
}

uint16_t is_internal(Node *node) { // check if leaf or internal node
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    return is_internal(node->left) + is_internal(node->right);
}

uint32_t fill_histogram(FILE *fin, uint32_t histogram[256]) {
    histogram[0x00]++;
    histogram[0xff]++;

    uint32_t filesize = 0;
    int read;
    while ((read = fgetc(fin)) != EOF) { // add byte into histogram and increment file size
        uint32_t byte = (uint32_t) read;
        histogram[byte]++;
        filesize++;
    }

    rewind(fin);
    return filesize;
}

Node *create_tree(uint32_t histogram[256]) {
    PriorityQueue *pq = pq_create();

    for (int i = 0; i < 256; ++i) { // queue node into pq
        if (histogram[i] > 0) {
            Node *node = node_create((uint8_t) i, histogram[i]);
            enqueue(pq, node);
        }
    }

    while (!pq_size_is_1(pq)) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *parent = node_create(0, left->weight + right->weight);
        parent->left = left;
        parent->right = right;
        enqueue(pq, parent);
    }

    Node *ret = dequeue(pq);
    pq_free(&pq); // free pq
    return ret;
}

void fill_code_table(Code code_table[256], Node *node, uint64_t code, uint8_t code_length) {
    if (!node)
        return;

    if (node->left == NULL && node->right == NULL) { // check if leaf
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    } else {
        fill_code_table(code_table, node->left, code << 1, code_length + 1);
        fill_code_table(code_table, node->right, (code << 1) | 1, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (!node)
        return;

    if (!(node->left || node->right)) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(
    FILE *fin, const char *out_filename, uint32_t filesize, Node *code_tree, Code code_table[256]) {
    BitWriter *bf = bit_write_open(out_filename);
    if (!bf) {
        perror("Error opening output file for writing");
        return;
    }

    bit_write_uint8(bf, 'H');
    bit_write_uint8(bf, 'C');
    bit_write_uint32(bf, filesize);
    uint16_t leaves = is_internal(code_tree);
    bit_write_uint16(bf, leaves);

    huff_write_tree(bf, code_tree);

    int byte;
    while ((byte = fgetc(fin)) != EOF) {
        uint64_t code = code_table[byte].code;
        uint8_t length = code_table[byte].code_length;

        for (int i = length - 1; i >= 0; i--) {
            uint8_t bit = (code >> i) & 1;
            bit_write_bit(bf, bit);
        }
    }

    bit_write_close(&bf);
}

int main(int argc, char *argv[]) {
    bool print_help_bool = false;
    char *input_filename = NULL;
    char *output_filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_filename = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_filename = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0) {
            print_help_bool = true;
            print_help();
            return 0;
        } else {
            fprintf(stderr, "Unknown or incomplete command line option.\n");
            return 1;
        }
    }

    if (input_filename == NULL || output_filename == NULL || print_help_bool) {
        if (input_filename == NULL)
            printf("huff:  -i option is required\n");
        if (output_filename == NULL)
            printf("huff:  -o option is required\n");
        print_help();
        exit(0);
    }

    FILE *fin = fopen(input_filename, "rb");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    uint32_t histogram[256] = { 0 };
    uint32_t filesize = fill_histogram(fin, histogram);

    Node *code_tree = create_tree(histogram);

    Code code_table[256] = { { 0 } };
    fill_code_table(code_table, code_tree, 0, 0);

    huff_compress_file(fin, output_filename, filesize, code_tree, code_table);

    node_free(&code_tree);
    fclose(fin);

    return 0;
}
