CC := gcc
CFLAGS := -Wall -g
LDFLAGS :=
LIBS := -lmysqlclient

TARGET := testmysql.out
SRC := testmysql.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGET)
