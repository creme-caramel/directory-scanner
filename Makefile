FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRCDIR := $(CURDIR)/src/

CC = clang
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3 -lm

all: muttypehash scan

muttypehash:
	gperf -t $(SRCDIR)hash/muttype.gperf > $(SRCDIR)hash/muttype.h

scan: scan.o
	$(CC) scan.o -o scan $(LDFLAGS)

scan.o: $(SRCDIR)scan.c
	$(CC) $(CFLAGS) $(SRCDIR)scan.c
	
run:
	@chmod +x run
	@./run scan

clean:
	@rm -f scan scan.o *.db *.csv

.PHONY: run clean all
