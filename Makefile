FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
INC := -I$(CURDIR)/include/

CC = gcc
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3 -lm

all: muttypehash scan

muttypehash:
	gperf -t $(SRC)hash/muttype.gperf > $(SRC)hash/muttype.h

scan: scan.o
	$(CC) scan.o -o scan $(LDFLAGS)

scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) $(SRC)scan.c
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan scan.o

.PHONY: test clean all
