#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return NULL; // Error opening file
    }

    BitReader *reader = (BitReader *) malloc(sizeof(BitReader));
    if (reader == NULL) {
        fclose(f); // Close the file
        return NULL; // Memory allocation failed
    }

    reader->underlying_stream = f;
    reader->byte = 0;
    reader->bit_position = 8;

    return reader;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        if (fclose((*pbuf)->underlying_stream) != 0) {
            exit(EXIT_FAILURE);
        }
        free(*pbuf);
        *pbuf = NULL;
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int c = fgetc(buf->underlying_stream);
        buf->byte = (uint8_t) c;
        buf->bit_position = 0;
    }
    // get the bit numbered bit_position from byte
    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position += 1;

    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; i++) {
        uint8_t b = bit_read_bit(buf);
        byte |= (b << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (int i = 0; i < 16; i++) {
        uint8_t b = bit_read_bit(buf);
        word |= (b << i);
    }
    return word;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (int i = 0; i < 32; i++) {
        uint8_t b = bit_read_bit(buf);
        word |= ((uint32_t) b << i);
    }
    return word;
}
