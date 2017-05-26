FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
DB := $(SRC)db/
INC := -I$(CURDIR)/include/

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lsqlite3 -lm
BIN = $(SRC)scan

all: muttypehash $(BIN)

muttypehash:
	gperf -t $(SRC)hash/muttype.gperf > $(SRC)hash/muttype.h

$(BIN): $(SRC)scan.o $(DB)/db.o
	$(CC) $(SRC)scan.o $(DB)/db.o -o $(SRC)scan $(LDFLAGS)
	@ln -s $(SRC)scan $(CURDIR)/scan

$(SRC)scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(DB)/db.o: $(DB)/db.c
	$(CXX) $(CFLAGS) -c -o $@ $<
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan $(SRC)scan.o $(DB)/db.o $(BIN)

.PHONY: test clean all
