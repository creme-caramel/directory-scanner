FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
DB := $(SRC)db/
INC := -I$(CURDIR)/include/

CC = gcc
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3 -lm

all: muttypehash scan

muttypehash:
	gperf -t $(SRC)hash/muttype.gperf > $(SRC)hash/muttype.h

scan: scan.o $(DB)/db.o
	$(CC) scan.o $(DB)/db.o -o scan $(LDFLAGS)

scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) $(SRC)scan.c

$(DB)/db.o: $(DB)/db.c
	$(CXX) $(CFLAGS) -c -o $@ $<
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan scan.o $(DB)/db.o

.PHONY: test clean all
