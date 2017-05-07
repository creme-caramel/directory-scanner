FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
INC := -I$(CURDIR)/filters/

CC = clang
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3 -lm

all: muttypehash scan

muttypehash:
	gperf -t $(SRC)hash/muttype.gperf > $(SRC)hash/muttype.h

scan: scan.o
	$(CC) scan.o -o scan $(LDFLAGS)

scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) $(SRC)scan.c
	
run:
	@chmod +x run
	@./run scan

clean:
	@rm -f scan scan.o */*.db */*.csv

.PHONY: run clean all
