CC=gcc
LD=gcc

CCFLAGS= -c -O2
LDFLAGS= -O2

BIN=
OBJECTS:=$(patsubst %.c, %.o, $(wildcard src/*.c))
HEADERS:=$(wildcard hdr/*.h)


.PHONY: all clean run


all: $(BIN)

$(BIN): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJECTS): %.o : %.c $(HEADERS)
	$(CC) $(CCFLAGS) -o $@ $<
	

clean:
	rm -rf $(BIN) $(OBJECTS)
