CFLAGS=-m64 -O3 -Wno-attributes
CC=gcc

#BINARIES=test kaslr physical_reader

SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

.PHONY: lib

all: $(BINARIES) lib

lib:
	$(MAKE) -C libkdump

libkdump/libkdump.a: 
	make -C libkdump

%: %.c libkdump/libkdump.a
	$(CC) $< -o $@ -Llibkdump -Ilibkdump -lkdump $(CFLAGS)
	
	
clean:
	rm -f *.o $(BINARIES)
	make clean -C libkdump
