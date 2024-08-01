#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int buff_size = 16;

int conversion(unsigned char *buff, int size, int index) {
    printf("%08x: ", index);

    int count = 0;
    int spaces = 0;

    for (int i = 0; i < size; i++) {
        printf("%02x", buff[i]);
        count += 2;
        if (i % 2 == 1) {
            printf(" ");
            count++;
            spaces++;
        }
    }

    for (int j = count; j < buff_size * 2 + 9; j++) {
        printf(" ");
    }

    for (int i = 0; i < size; i++) {
        if (buff[i] >= 32 && buff[i] <= 126) {
            printf("%c", buff[i]);
        } else {
            printf(".");
        }
    }

    printf("\n");
    return 0;
}

int read_file(char *fileName) {
    int fd = open(fileName, O_RDONLY);

    if (fd == -1) {
        return -1;
    }

    unsigned char *buff = malloc(buff_size);
    int res;
    int index = 0;

    while ((res = read(fd, buff, buff_size)) > 0) {
        conversion(buff, res, index);
        index += res;
    }

    close(fd);
    free(buff);
    return 0;
}

int main(int argc, char **argv) {
    unsigned char *buff = malloc(buff_size);
    int total_count = 0;
    int index = 0;
    int eof = 0;

    if (argc == 1) {
        while (!eof) {
            while (total_count < buff_size) {
                int count = read(STDIN_FILENO, &buff[total_count], buff_size - total_count);
                if (count <= 0) {
                    break;
                }
                total_count += count;
            }
            if (total_count == 0) {
                break;
            }
            if (total_count == 16) {
                conversion(buff, total_count, index);
                index += buff_size;
                total_count = 0;
            } else if (total_count < 16) {
                conversion(buff, total_count, index);
                index += buff_size;
                total_count = 0;
                break;
            }
        }
    } else if (argc == 2) {
        if (read_file(argv[1]) == -1) {
            return -1;
        }
    } else {
        return -1;
    }

    free(buff);
    return 0;
}
