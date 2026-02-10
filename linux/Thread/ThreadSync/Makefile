SOURCES := $(wildcard *.c)
EXECUTABLES := $(SOURCES:.c=.o)
CC := gcc

all: $(EXECUTABLES)

%.o: %.c
	$(CC) -o $@ $<

clean:
	rm -f *.o

.PHONY: all clean
