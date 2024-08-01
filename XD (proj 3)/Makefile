# Makefile for CSE 13S, Winter 2024, Assignment 3

CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LFLAGES =
EXEC = xd

all: $(EXEC)

$(EXEC): $(EXEC).o xd.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

test: tests
	# bash runner.sh