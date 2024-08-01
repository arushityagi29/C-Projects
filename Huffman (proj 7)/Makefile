CC=clang
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
OBJS = bitreader.o bitwriter.o node.o pq.o
HEAD = bitreader.h bitwriter.h node.h pq.h
EXEC = brtest bwtest nodetest pqtest huff dehuff

all: $(EXEC)

huff: huff.o $(OBJS)
	$(CC) -o huff huff.o $(OBJS)

dehuff: dehuff.o $(OBJS)
	$(CC) -o dehuff dehuff.o $(OBJS)

brtest: brtest.o bitreader.o
	$(CC) -o brtest brtest.o bitreader.o

bwtest: bwtest.o bitwriter.o
	$(CC) -o bwtest bwtest.o bitwriter.o

nodetest: nodetest.o node.o
	$(CC) -o nodetest nodetest.o node.o

pqtest: pqtest.o pq.o
	$(CC) -o pqtest pqtest.o pq.o node.o

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) dehuff-arm dehuff-x86 huff-arm huff-x86 *.o

scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]
