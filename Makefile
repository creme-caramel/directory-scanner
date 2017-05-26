FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
DB := $(SRC)db/
INC := -I$(CURDIR)/include/

CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lsqlite3 -lm
BIN = $(SRC)scan

RPATH = -Wl,-rpath=$(DB) -L$(DB) 
LIBS = -ldb

all: $(BIN)

$(BIN): $(SRC)scan.o
	$(CC) $(SRC)scan.o -o $(SRC)scan $(RPATH) $(LIBS) $(LDFLAGS)
	@ln -s $(SRC)scan $(CURDIR)/scan

$(SRC)scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan $(SRC)scan.o $(DB)/db.o $(BIN)

.PHONY: test clean all
