#include "bitwriter.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    FILE *f = fopen(filename, "wb"); // Open file for writing in binary mode
    if (f == NULL) {
        return NULL; // Error opening file
    }

    BitWriter *writer = (BitWriter *) malloc(sizeof(BitWriter));
    if (writer == NULL) {
        fclose(f); // Close the file
        return NULL; // Memory allocation failed
    }

    writer->underlying_stream = f;
    writer->byte = 0;
    writer->bit_position = 0;

    return writer;
}

void bit_write_close(BitWriter **pbuf) {
    BitWriter *buf = *pbuf;
    if (buf != NULL && buf->bit_position > 0) {
        fputc(buf->byte, buf->underlying_stream);
    }
    if (*pbuf != NULL) {
        fclose(buf->underlying_stream);
        free(buf);
        *pbuf = NULL;
    }
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        fputc(buf->byte, buf->underlying_stream);
        buf->byte = 0x00;
        buf->bit_position = 0;
    }
    buf->byte
        |= (bit & 0x01)
           << buf->bit_position; // set the bit at bit_position of the byte to the value of bit (check this!)
    buf->bit_position += 1;
}

void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        bit_write_bit(buf, (byte >> i) & 1);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        bit_write_bit(buf, x & 0x01);
        x = x >> 1;
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        bit_write_bit(buf, x & 0x01);
        x = x >> 1;
    }
}
