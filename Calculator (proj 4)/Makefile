CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm
EXEC = calc
TEST_EXEC = test
GRAPHING_EXEC = graphing
HEADERS = operators.h mathlib.h stack.h

SOURCES = calc.c stack.c mathlib.c operators.c graphing.c
OBJECTS = $(SOURCES:.c=.o)
TEST_SOURCES = tests.c stack.c mathlib.c operators.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)


all: $(EXEC) $(TEST_EXEC) $(GRAPHING_EXEC)

$(EXEC): calc.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

$(TEST_EXEC): tests.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

$(GRAPHING_EXEC): graphing.o mathlib.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) $(TEST_EXEC) $(GRAPHING_EXEC) $(OBJECTS) $(TEST_OBJECTS)

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
